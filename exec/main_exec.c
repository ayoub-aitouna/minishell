/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:09 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/22 09:37:44 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void run_built_in(m_node *node)
{
	char *dir;

	if (is_equal(node->command, "exit"))
		return (exit(0));
	if (is_equal(node->command, "cd"))
	{
		dir = NULL;
		if (size(node->arguments) >= 1)
			dir = node->arguments[1];
		return (change_directory(dir));
	}
	if (is_equal(node->command, "echo"))
	{
		if (!node->arguments[1])
			return (echo(NULL));
		return (echo(&node->arguments[1]));
	}
	if (is_equal(node->command, "pwd"))
		print_working_directory();
	// exit(0);
}

// if (is_equal(node->command, "export"))
// {
// }
// if (is_equal(node->command, "unset"))
// {
// }
// if (is_equal(node->command, "env"))
// {
// }

void manage_input_output(m_node *node, int index, int len, int fd[])
{
	if (index == 0)
	{
		close(fd[0]);
		if (node->input_file != -1)
			dup2(node->input_file, 0);
		if (node->output_file != -1)
			dup2(node->output_file, 1);
		else if (len != 1)
			dup2(fd[1], 1);
	}
	else if (index < len - 1)
	{
		// milde children
		if (node->input_file != -1)
			dup2(node->input_file, 0);
		else
			dup2(fd[0], 0);
		if (node->output_file != -1)
			dup2(node->output_file, 1);
		else
			dup2(fd[1], 1);
	}
	else
	{
		close(fd[1]);
		if (node->input_file != -1)
			dup2(node->input_file, 0);
		else
			dup2(fd[0], 0);
		if (node->output_file != -1)
			dup2(node->output_file, 1);
	}
}

int procces_list(int **list, int new_pid, int size)
{
	int i;
	int *new_list;
	int *tab = *list;
	i = 0;
	new_list = malloc(sizeof(int) * (size + 1));
	if (!new_list)
		return 0;

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

void exec(t_list *list)
{
	m_node *node;
	int pid;
	int index;
	int len;
	int proccess_len;
	int *procces;
	int fd[2];

	index = 0;
	proccess_len = 0;
	procces = NULL;
	len = ft_lstsize(list);
	pipe(fd);
	while (list)
	{
		node = (m_node *)list->content;
		pid = fork();
		if (pid == 0)
		{
			manage_input_output(node, index, len, fd);
			if (is_builtin(node->command))
				run_built_in(node);
			else
				execve(node->command, node->arguments, get_env(NULL));
			exit(0);
		}
		else
		{
			proccess_len = procces_list(&procces, pid, proccess_len);
			index++;
			list = list->next;
		}
	}
	close(fd[0]);
	close(fd[1]);
	int i = 0;
	while (i < proccess_len)
		waitpid(procces[i++], NULL, 0);
}
