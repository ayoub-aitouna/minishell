/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:25:53 by aaitouna          #+#    #+#             */
/*   Updated: 2023/03/01 17:50:00 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
int handle_fd(int *fd);
int reset(int len, int **proccess, int pid);
void manage_input_output(m_node *node, int out_fd, int in_fd, int index,
						 int len);
int wait_all_proccess(int *procces, int len)
{
	int i;
	int status;

	i = 0;
	while (i < len)
	{
		waitpid(procces[i++], &status, 0);
		set_exit_status(WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}

int shell_proccess(m_node *node, int in_fd, int out_fd, int len, int ends_count)
{
	signal(SIGINT, exit);
	if (node->input_file == ERROR || node->output_file == ERROR || node->output_file == NO_FILE || node->input_file == NO_FILE)
		return (1);
	manage_input_output(node, out_fd, in_fd, ends_count, len);
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

int recursive_exec(t_tree *tree, int in_fd, int **procces_id, int *len, int ends_count, int *index, int w)
{
	int pid;
	int status;
	int fd[2];
	if (tree == NULL)
		return (-1);
	if (tree->op == 2 || tree->op == 3)
	{
		status = recursive_exec(tree->left, in_fd, procces_id, len, ends_count, index, 1);
		status = wait_all_proccess(*procces_id, *len);
		if (tree->op == 2 && status != 0)
			status = recursive_exec(tree->right, in_fd, procces_id, len, ends_count, index, 1);
		else if (tree->op == 3 && status == 0)
			status = recursive_exec(tree->right,  in_fd, procces_id, len, ends_count, index, 1);
		return (status);
	}
	recursive_exec(tree->left, in_fd, procces_id, len, ends_count, index, 0);
	if (tree->node == NULL)
		return (0);
	(*index)++;
	pid = fork();
	pipe(fd);
	if (pid == 0)
		exit(shell_proccess(tree->node, in_fd, fd[1], ends_count, *index));
	else
	{
		in_fd = handle_fd(fd);
		*len = reset(*len, procces_id, pid);
	}
	if (w)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	recursive_exec(tree->right, in_fd, procces_id, len, ends_count, index, 0);
	return (0);
}

void calculate_tree_ends(t_tree *tree, int *len)
{
	if (tree == NULL)
		return;
	if (tree->left == NULL && tree->right == NULL)
		(*len)++;
	calculate_tree_ends(tree->left, len);
	calculate_tree_ends(tree->right, len);
}

void shell_exec(t_tree *tree)
{
	int *proccess_id = NULL;
	int len = 0;
	int ends_count = 0;
	int index = 0;
	calculate_tree_ends(tree, &ends_count);
	int status = recursive_exec(tree, STDIN_FILENO, &proccess_id, &len, ends_count, &index, 0);
	status = wait_all_proccess(proccess_id, len);
}