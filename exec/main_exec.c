/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:09 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/24 03:03:29 by aaitouna         ###   ########.fr       */
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

void	manage_input_output(m_node *node, int index, int len, int fd[])
{
	if (index == 0)
	{
		close(fd[0]);
		if (node->input_file != NONE)
			dup2(node->input_file, 0);
		if (node->output_file != NONE)
			dup2(node->output_file, 1);
		else if (len != 1)
			dup2(fd[1], 1);
	}
	else if (index < len - 1)
	{
		// milde children
		if (node->input_file != NONE)
			dup2(node->input_file, 0);
		else
			dup2(fd[0], 0);
		if (node->output_file != NONE)
			dup2(node->output_file, 1);
		else
			dup2(fd[1], 1);
	}
	else
	{
		close(fd[1]);
		if (node->input_file != NONE)
			dup2(node->input_file, 0);
		else
			dup2(fd[0], 0);
		if (node->output_file != NONE)
			dup2(node->output_file, 1);
	}
}

int	procces_list(int **list, int new_pid, int size)
{
	int	i;
	int	*new_list;
	int	*tab;

	tab = *list;
	i = 0;
	new_list = malloc(sizeof(int) * (size + 1));
	if (!new_list)
		return (0);
	while (i < size + 1)
	{
		if (i == 0)
			new_list[i] = new_pid;
		else
			new_list[i] = tab[i - 1];
		i++;
	}
	if (*list != NULL)
		free(*list);
	*list = new_list;
	return (size + 1);
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

	index = 0;
	proccess_len = 0;
	procces = NULL;
	len = ft_lstsize(list);
	pipe(fd);
	while (index < len)
	{
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
		{
			signal(SIGINT, exit);
			if (node->input_file == ERROR || node->output_file == ERROR
				|| node->output_file == NO_FILE || node->input_file == NO_FILE)
				exit(1);
			manage_input_output(node, index, len, fd);
			if (is_builtin(node->command))
				run_built_in(node);
			else
			{
				if (node->command == NULL)
				{
					ft_printf(RED "%s: command not found \n" RESET,
								size(node->arguments) > 0 ? node->arguments[0] : NULL);
					exit(127);
				}
				execve(node->command, node->arguments, get_env(NULL));
			}
			exit(1);
		}
		else
		{
			signal(SIGINT, handle_sigint_n_chld);
			proccess_len = procces_list(&procces, pid, proccess_len);
		}
		index++;
		list = list->next;
	}
	close(fd[0]);
	close(fd[1]);
	i = 0;
	while (i < proccess_len)
		waitpid(procces[i++], NULL, 0);
	signal(SIGINT, handle_sigint);
}
