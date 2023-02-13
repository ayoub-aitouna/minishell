/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:44:21 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/13 15:32:27 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	size(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

char	**append(char **Strings, char *String)
{
	int		i;
	int		len;
	char	**new_Strings;

	i = 0;
	if (Strings == NULL)
		len = 0;
	else
		len = size(Strings);
	new_Strings = malloc((len + 2) * sizeof(char *));
	while (i < len)
	{
		new_Strings[i] = Strings[i];
		i++;
	}
	new_Strings[i++] = String;
	new_Strings[i] = NULL;
	if (Strings != NULL)
		free_list(Strings);
	return (new_Strings);
}

size_t	string_list_len(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}
