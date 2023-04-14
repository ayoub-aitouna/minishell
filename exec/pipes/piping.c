/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:49:05 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/14 10:07:28 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

int	is_builtins(char *s)
{
	if (is_equal(s, "exit") || is_equal(s, "cd") || is_equal(s, "echo")
		|| is_equal(s, "pwd") || is_equal(s, "export") || is_equal(s, "unset")
		|| is_equal(s, "env"))
		return (1);
	return (0);
}


void	child_proccess(t_node *node, char **env)
{
	char	*path;

	if (!node->command)
	{
		ft_putstr_fd(node->command, 2);
		write(2, "minishell: :command not found \n", 32);
		exit (127);
	}
	if (node->output_file != NONE && node->output_file != NO_FILE)
	{
		if (dup2(node->output_file, 1) < 0)
			exit_msg("DUP", 1);
	}
	if (node->input_file != NONE && node->input_file != NO_FILE)
	{
		if (dup2(node->input_file, 0) < 0)
			exit_msg("DUP", 1);
	}
	path = get_paths(env, node->arguments[0]);
	printf("%s\n", path);
	if (is_child_builtins(node->command, node->arguments[1]))
	{
		child_builtins(node);
		exit (0);
	}
	else
	{
		if (path == NULL || is_builtins(node->command))
		{
			ft_putstr_fd(node->command, 2);
			write(2, "minishell: :command not found \n", 32);
			exit (127);
		}
		else
		{
			execve(path, node->arguments, env);
			perror("execve");
		}
		exit(1);
	}
}

void	parent_proccess(int num_commands, int pipes[2], int in)
{
	int	status;

	status = 0;
	while (num_commands--)
		wait(&status);
	close(pipes[0]);
	close(in);
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		set_exit_status(128 + WTERMSIG(status));
	signal(SIGINT, handle_sigint);
}

void	multiple_pipes(t_node *node, t_list *list, int num_commands)
{
	int		pipes[2];
	int		i;
	int		in;

	in = 0;
	i = 0;
	while (list)
	{
		node = (t_node *) list->content;
		pipe(pipes);
		if (node->command && is_builtin(node->command, node->arguments[1]))
			builtins(node);
		else
		{
			if (fork() == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				signal(SIGINT, SIG_DFL);
				close(pipes[0]);
				dup2(in, 0);
				if (i < num_commands - 1)
					dup2(pipes[1], 1);
				child_proccess(node, get_env(NULL));
			}
			else
			{
				signal(SIGINT, handle_sigint_n_chld);
				signal(SIGQUIT, child_quit);
			}
		}
		close(pipes[1]);
		in = pipes[0];
		list = list->next;
		i++;
	}
	parent_proccess(num_commands, pipes, in);
}
