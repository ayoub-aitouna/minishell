/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:41:31 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/04 05:09:38 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printf_arg(char **str)
{
	int	i;

	i = 0;
	ft_printf("arguments  		< ");
	if (str == NULL)
	{
		ft_printf("(null) >\n");
		return ;
	}
	while (str[i])
		printf("%s ,", str[i++]);
	printf(" >\n");
}

void	print_table(t_node *node)
{
	ft_printf("input file 		<%d> \n", node->input_file);
	ft_printf("command    		<%s> \n", node->command);
	printf_arg(node->arguments);
	ft_printf("output_file file 	<%d> \n", node->output_file);
}

void	printf_list(t_list *list)
{
	int		i;
	t_node	*node;

	i = 0;
	if (list == NULL)
		return ;
	while (list)
	{
		node = (t_node *)list->content;
		if (!node)
		{
			printf("node null");
			return ;
		}
		printf("\n---------------\tnode_%d\t--------------\n", i);
		print_table(node);
		printf("\n--------------------------------------\n");
		i++;
		list = list->next;
	}
}
