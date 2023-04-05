/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:31:49 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/05 10:54:26 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec.h"

int	string_exists(char **export, int n, char *argument, int len)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (strncmp(export[i], argument, len) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	add_new_export(char **export, char **old_export, char **arguments)
{
	int	i;
	int	j;
	int k;

	i = 0;
	while (old_export && old_export[i])
	{
		export[i] = ft_strdup(old_export[i]);
		i++;
	}
	sorted_list(export, size(old_export));
	j = 1;
	while (arguments&& arguments[j] && !string_exists(old_export, size(old_export), arguments[j], ft_strlen(arguments[j])))
	{
		if (arguments[j] && arguments[j][0] == '#')
				break ;
		if (arguments && arguments[j])
		{
			k = 0;
			while (arguments && arguments[j] && arguments[j][k])
			{
				if (arguments[j][k] == '=' && arguments[j][k - 1] == '+')
				{
					export[i++] = ft_strdup(add_plus_string(old_export, arguments[j++]));
					break ;
				}
				k++;
			}
			export[i++] = ft_strdup(arguments[j]);
		}
		j++;
	}
	export[i] = NULL;
	// free_list (old_export);
}

char	**get_new_export(char **old_export, char **str)
{
	char	**export;
	
	export = NULL;
	if (old_export != NULL && !str[1])
	{
		export = get_export(NULL);
		sorted_list(export, size(old_export));
	}
	else if (old_export)
	{
		export = malloc((size(old_export) + size(str)) * sizeof(char *));
		add_new_export(export, old_export, str);
	}
	export = reset_forbidden_env(export);
	export = remove_duplicate(export);
	return (export);
}
