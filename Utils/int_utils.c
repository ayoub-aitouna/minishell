/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 07:31:03 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/28 12:55:32 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

int	list_append(int **list, int new_pid, int size)
{
	int	i;
	int	*new_list;
	int	*tab;

	tab = *list;
	i = 0;
	new_list = malloc(sizeof(int) * (size + 1));
	if (!new_list)
		return (0);
	while (i < size + 1)
	{
		if (i == 0)
			new_list[i] = new_pid;
		else
			new_list[i] = tab[i - 1];
		i++;
	}
	if (*list != NULL)
		free(*list);
	*list = new_list;
	return (size + 1);
}
