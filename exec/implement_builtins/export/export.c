/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:31:49 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/07 07:50:08 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	is_add_plus_str(char *argument)
{
	int	i;

	i = 0;
	while (argument && argument[i])
	{
		if (argument[i] == '=' && argument[i - 1] == '+')
			return (1);
		i++;
	}
	return (0);
}

void	add_new_export(char **export, char **old_export, char **arguments)
{
	int	i;
	int	j;
	int	is_valid;

	i = -1;
	while (old_export && old_export[++i])
		export[i] = ft_strdup(old_export[i]);
	j = 1;
	while (arguments && arguments[j] && !string_exists(old_export, \
		size(old_export), arguments[j], ft_strlen(arguments[j])))
	{
		is_valid = 0;
		if (arguments[j] && arguments[j][0] == '#')
			break ;
		if (is_add_plus_str(arguments[j]))
			export[i++] = ft_strdup(add_plus_string(old_export, \
					arguments[j]));
		else
			export[i++] = ft_strdup(arguments[j]);
		j++;
	}
	export[i] = NULL;
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
