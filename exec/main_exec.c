/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:09 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/14 18:47:09 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_built_in(m_node *node)
{
	char	*dir;

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
	if (is_equal(node->command, "export"))
	{
	}
	if (is_equal(node->command, "unset"))
	{
	}
	if (is_equal(node->command, "env"))
	{
	}
}

void	exec(t_list *list)
{
	m_node	*node;
	int		pid;
	int		index;
	int		l_index;
	int		fd[2];

	index = 0;
	l_index = ft_lstsize(list) - 1;
	pipe(fd);
	while (list)
	{
		node = (m_node *)list->content;
		if ((pid = fork()) != 0)
		{
			index++;
			list = list->next;
			waitpid(pid, NULL, 0);
			continue ;
		}
		if (l_index == 0)
		{
			if (node->input_file != -1)
				dup2(node->input_file, 0);
			if (node->output_file != -1)
				dup2(node->output_file, 1);
		}
		else if (index == 0)
		{
			if (node->input_file != -1)
				dup2(node->input_file, 0);
			dup2(fd[1], 1);
		}
		else if (index == l_index)
		{
			dup2(fd[0], 0);
			if (node->output_file != -1)
				dup2(node->output_file, 1);
		}
		else
		{
			dup2(fd[1], 1);
			dup2(fd[0], 0);
		}
		if (is_builtin(node->command))
			run_built_in(node);
		else
			execve(node->command, node->arguments, get_env(NULL));
	}
}
