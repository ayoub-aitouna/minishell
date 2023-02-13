/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:09 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/12 14:33:30 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void run_built_in(m_node *node)
{
	if (ft_strncmp(node->command, "exit", 4) == 0)
		exit(0);
	if (ft_strncmp(node->command, "cd", 2) == 0)
	{
		char *dir = NULL;
		if (size(node->arguments) >= 1)
			dir = node->arguments[1];
		change_directory(dir);
	}
}

void exec(void *content)
{
	m_node *node;
	int id;

	node = (m_node *)content;
	if (is_builtin(node->command))
		run_built_in(node);
	else if ((id = fork()) == 0)
	{
		if (node->input_file != -1)
			dup2(node->input_file, 0);
		if (node->output_file != -1)
			dup2(node->output_file, 1);
		execve(node->command, node->arguments, get_env(NULL));
	}
	waitpid(id, NULL, 0);
}
