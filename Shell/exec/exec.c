/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:25:53 by aaitouna          #+#    #+#             */
/*   Updated: 2023/03/02 02:13:29 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void dup_input_output(int in, int out)
{
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
}

int wait_all_proccess(t_proccess proccess)
{
	int i;
	int status;

	i = 0;
	if (proccess.lenght == 0)
		return -1;
	while (i < proccess.lenght)
	{
		waitpid(proccess.proccess[i++], &status, 0);
		set_exit_status(WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}

int shell_proccess(m_node *node, int in_fd, int out_fd, int is_last)
{
	signal(SIGINT, exit);
	if (node->input_file == ERROR || node->output_file == ERROR || node->output_file == NO_FILE || node->input_file == NO_FILE)
		return (1);
	dup_input_output(in_fd, is_last ? 1 : out_fd);
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

int run_proccess(m_node *node, int in_fd, int out_fd, int w, int *index, int ends_count, t_proccess *proccess)
{
	int status;
	int pid;
	if (node == NULL)
		return 0;
	pid = fork();
	if (pid == 0)
		exit(shell_proccess(node, in_fd, out_fd, ends_count == *index));
	else if (w)
	{
		(*index)++;
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	(*index)++;
	proccess->lenght = reset(&(proccess->proccess), proccess->lenght, pid);
	return (0);
}

int recursive_exec(t_tree *tree, int in_fd, int out_fd, t_proccess *proccess, int ends_count, int *index, int w)
{
	int status;
	int fd[2];
	int s;

	status = 0;
	if (tree == NULL)
		return (-1);
	if (tree->op == 2 || tree->op == 3)
	{
		status = recursive_exec(tree->left, in_fd, out_fd, proccess, ends_count, index, 1);
		s = wait_all_proccess(*proccess);
		status = s != -1 ? s : status;
		if (tree->op == 2 && status != 0)
			status = recursive_exec(tree->right, in_fd, out_fd, proccess, ends_count, index, 1);
		else if (tree->op == 3 && status == 0)
			status = recursive_exec(tree->right, in_fd, out_fd, proccess, ends_count, index, 1);

		return (status);
	}
	else if (tree->op == 1)
	{
		pipe(fd);
		status = recursive_exec(tree->left, in_fd, out_fd, proccess, ends_count, index, 0);
		in_fd = handle_fd(fd);
		status = recursive_exec(tree->right, in_fd, out_fd, proccess, ends_count, index, 0);
	}
	return (run_proccess(tree->node, in_fd, out_fd, w, index, ends_count, proccess));
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
	t_proccess *proccess = malloc(sizeof(t_proccess));
	proccess->proccess = NULL;
	proccess->lenght = 0;
	int ends_count = 0;
	int index = 0;
	calculate_tree_ends(tree, &ends_count);
	int status = recursive_exec(tree, STDIN_FILENO, STDOUT_FILENO, proccess, ends_count, &index, 0);
	status = wait_all_proccess(*proccess);
}