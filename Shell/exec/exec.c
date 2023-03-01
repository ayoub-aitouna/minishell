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

int	wait_all_proccess(int *procces, int len)
{
	int	i;
	int	status;

	i = 0;
	while (i < len)
	{
		waitpid(procces[i++], &status, 0);
		set_exit_status(WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}

int	shell_proccess(m_node *node)
{
	signal(SIGINT, exit);
	if (node->input_file == ERROR || node->output_file == ERROR
		|| node->output_file == NO_FILE || node->input_file == NO_FILE)
		return (1);
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

int	recursive_exec(t_tree *tree, int **procces_id, int *len, int w)
{
	int	pid;
	int	status;

	if (tree == NULL)
		return (-1);
	if (tree->op == 2 || tree->op == 3)
	{
		status = recursive_exec(tree->left, procces_id, len, 1);
		status = wait_all_proccess(*procces_id, *len);
		if (tree->op == 2 && status != 0)
			status = recursive_exec(tree->right, procces_id, len, 1);
		else if (tree->op == 3 && status == 0)
			status = recursive_exec(tree->right, procces_id, len, 1);
		return (status);
	}
	recursive_exec(tree->left, procces_id, len, 0);
	recursive_exec(tree->right, procces_id, len, 0);
	if (tree->node == NULL)
		return (0);
	pid = fork();
	if (pid == 0)
		exit(shell_proccess(tree->node));
	if (w)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	*len = list_append(procces_id, pid, *len);
	return (0);
}

void	shell_exec(t_tree *tree)
{
	int *proccess_id = NULL;
	int len = 0;
	int status = recursive_exec(tree, &proccess_id, &len, 0);
	status = wait_all_proccess(proccess_id, len);
}