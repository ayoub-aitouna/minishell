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

void exec(void *content)
{
	m_node *node;
	int id;

	node = (m_node *)content;
	if (ft_strncmp(node->command, "exit", 4) == 0)
		exit(0);
	if ((id = fork()) == 0)
	{
		if (node->input_file != -1)
			dup2(node->input_file, 0);
		if (node->output_file != -1)
			dup2(node->output_file, 1);
		execve(node->command, node->arguments, get_env(NULL));
	}
	waitpid(id, NULL, 0);
}
