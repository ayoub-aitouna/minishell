/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:23:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/03/01 11:54:56 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
}

void	clear_node(void *conetent)
{
	m_node	*node;

	node = (m_node *)conetent;
	if (node == NULL)
		return ;
	if (node->input_file > 2)
		close(node->input_file);
	if (node->output_file > 2)
		close(node->output_file);
	if (node->arguments != NULL)
		free_list(node->arguments);
	ft_free(node->command);
	free(node);
}

void	clear_tree(t_tree *node)
{
	if (node == NULL)
		return ;
	ft_free(node->content);
	clear_node(node->node);
	clear_tree(node->left);
	clear_tree(node->right);
	free(node);
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
