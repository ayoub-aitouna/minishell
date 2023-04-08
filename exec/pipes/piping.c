/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:49:05 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/08 06:06:10 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	child_proccess(m_node *node, char **env)
{
	char	*path;

	if (node->arguments[0] == 0)
		exit_msg("command not found \n", 127);
	path = get_paths(env, node->arguments[0]);
	if (path == NULL && !is_builtins(node))
	{
		printf("%s :", node->arguments[0]);
		exit_msg("command not found \n", 127);
	}
	if (is_builtins(node))
	{
		builtins(node);
		exit(0);
	}
	if (node->output_file != NONE && node->output_file != NO_FILE)
		dup2(node->output_file, 1);
	if (node->input_file != NONE && node->input_file != NO_FILE)
		dup2(node->input_file, 0);
	execve(path, node->arguments, env);
	perror("execve");
	exit(1);
}

void	parent_proccess(int num_commands, int pipes[2], int in)
{
	while (num_commands--)
		wait(NULL);
	close(pipes[0]);
	close (in);
}

void	multiple_pipes(m_node *node, t_list *list, int num_commands)
{
	int		pipes[2];
	int		i;
	int		in;

	in = 0;
	i = 0;
	while (list)
	{
		node = (m_node *) list->content;
		pipe(pipes);
		if (fork() == 0)
		{
			close(pipes[0]);
			dup2(in, 0);
			if (i < num_commands - 1)
				dup2(pipes[1], 1);
			child_proccess(node, get_env(NULL));
		}
		close(pipes[1]);
		in = pipes[0];
		list = list->next;
		i++;
	}
	parent_proccess(num_commands, pipes, in);
}
