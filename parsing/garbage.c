/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:23:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/25 11:31:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_node(void *content)
{
	m_node	*node;

	node = content;
	if (node->input_file > 2)
		close(node->input_file);
	if (node->output_file > 2)
		close(node->output_file);
	if (node->arguments != NULL)
		free_list(node->arguments);
	if (node->command != NULL)
		free(node->command);
	free(content);
}

void	free_list(char **list)
{
	int	i;

	if (list == NULL)
		return ;
	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
}
