/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:09 by aaitouna          #+#    #+#             */
/*   Updated: 2023/03/02 02:13:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_built_in(m_node *node)
{
	if (is_equal(node->command, "echo"))
	{
		if (node->arguments == NULL || size(node->arguments) <= 1)
			return (echo(NULL));
		return (echo(&node->arguments[1]));
	}
	if (is_equal(node->command, "pwd"))
		print_working_directory();
}

int	run_built_in_on_main(m_node *node, int len)
{
	if (is_equal(node->command, "exit"))
		exit(0);
	if (is_equal(node->command, "cd") && len == 1)
	{
		if (size(node->arguments) >= 1)
			change_directory(node->arguments[1]);
		else
			change_directory(NULL);
		return (1);
	}
	if (is_equal(node->command, "unset"))
	{
		if (node->arguments != NULL && size(node->arguments) > 1)
			unset(node->arguments[1]);
		unset(NULL);
		return (1);
	}
	if (is_equal(node->command, "env"))
	{
		env();
		return (1);
	}
	if (is_equal(node->command, "export"))
	{
		if (node->arguments != NULL && size(node->arguments) > 1)
			export(node->arguments[1]);
		export(NULL);
		return (1);
	}
	return (0);
}

void	manage_input_output(m_node *node, int out_fd, int in_fd, int index,
		int len)
{
	if (len == 1)
	{
		if (node->input_file != NONE)
			dup2(node->input_file, STDIN_FILENO);
		if (node->output_file != NONE)
			dup2(node->output_file, STDOUT_FILENO);
		return ;
	}
	if (index == 0)
	{
		if (node->input_file != NONE)
			dup2(node->input_file, STDIN_FILENO);
		if (node->output_file != NONE)
			dup2(node->output_file, STDOUT_FILENO);
		else
			dup2(out_fd, STDOUT_FILENO);
	}
	else if (index == len - 1)
	{
		if (node->input_file != NONE)
			dup2(node->input_file, STDIN_FILENO);
		if (node->output_file != NONE)
			dup2(node->output_file, STDOUT_FILENO);
		else
			dup2(in_fd, STDIN_FILENO);
	}
	else
	{
		if (node->input_file != NONE)
			dup2(node->input_file, STDIN_FILENO);
		else
			dup2(in_fd, STDIN_FILENO);
		if (node->output_file != NONE)
			dup2(node->output_file, STDOUT_FILENO);
		else
			dup2(out_fd, STDOUT_FILENO);
	}
}

int	proccess(m_node *node, int in_fd, int out_fd, int len, int index)
{
	signal(SIGINT, exit);
	if (node->input_file == ERROR || node->output_file == ERROR
		|| node->output_file == NO_FILE || node->input_file == NO_FILE)
		return (1);
	manage_input_output(node, out_fd, in_fd, index, len);
	if (is_builtin(node->command))
		run_built_in(node);
	else
	{
		if (node->command == NULL)
		{
			ft_printf(RED "%s: command not found \n" RESET,
						size(node->arguments) > 0 ? node->arguments[0] : NULL);
			return (127);
		}
		execve(node->command, node->arguments, get_env(NULL));
	}
	return (1);
}

int	reset(int len, int **proccess, int pid)
{
	signal(SIGINT, handle_sigint_n_chld);
	return (list_append(proccess, pid, len));
}

int	handle_fd(int *fd)
{
	close(fd[1]);
	return (fd[0]);
}

void	exec(t_list *list)
{
	m_node	*node;
	int		pid;
	int		index;
	int		len;
	int		proccess_len;
	int		*procces;
	int		fd[2];
	int		i;
	int		i_fd;
	int		status;

	index = 0;
	i_fd = 1;
	proccess_len = 0;
	procces = NULL;
	len = ft_lstsize(list);
	while (index < len)
	{
		pipe(fd);
		node = (m_node *)list->content;
		if (run_built_in_on_main(node, len) || (is_equal(node->command, "cd")
				&& len > 1))
		{
			list = list->next;
			len--;
			continue ;
		}
		pid = fork();
		if (pid == 0)
			exit(proccess(node, i_fd, fd[1], len, index));
		else
		{
			i_fd = handle_fd(fd);
			proccess_len = reset(proccess_len, &procces, pid);
		}
		index++;
		list = list->next;
	}
	i = 0;
	while (i < proccess_len)
	{
		waitpid(procces[i++], &status, 0);
		set_exit_status(WEXITSTATUS(status));
	}
	free(procces);
	signal(SIGINT, handle_sigint);
}
