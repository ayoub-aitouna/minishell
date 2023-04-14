/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 05:13:18 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/14 13:48:03 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	string_exists(char **export, int n, char *argument, int len)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (strncmp(export[i], argument, len) == 0
			&& is_equal_plus_str(argument) != 2)
			return (1);
		i++;
	}
	return (0);
}

char	**reset_forbidden_env(char **name)
{
	char	**env;

	env = name;
	while (name && *name)
	{
		if ((!ft_isalpha(*name[0]) || is_forbidden_char(*name)
				|| !is_equal_plus(*name)))
		{
			printf("export: '%s': not a valid identifier\n", *name);
			remove_env(name);
		}
		else
			name++;
	}
	return (env);
}

int comparison(char *s1, char *s2)

{
	int index1 = get_name_index(s1);
	int index2 = get_name_index (s2);
	if (index1 == -1)
		index1 = ft_strlen(s1);
	if (index2 == -1)
		index2 = ft_strlen(s2);
	if ((index2 - index1) == 0 && !ft_strncmp(s1, s2, index2))
		return (1);
	return (0);
}

char	**reset(char **env, char **argument)
{
	int		len;
	int		i;
	char	**temp;

	temp = env;
	while (env && *env)
	{
		i = 0;
		while (argument && argument[i])
		{
			if (argument[i] && argument[i][0] == '#')
				break ;
			len = is_value(argument[i]);
			if (!ft_strncmp(argument[i], "_=", 2))
				i++;
			else if (comparison(argument[i], *env) && is_equal_plus_str(argument[i]) == 1)
			{
				printf("%s\n", *env);
				remove_env(env);
			}
			else
				i++;
		}
		env++;
	}
	return (temp);
}

char	**remove_duplicate(char **export)
{
	char	**new_export;
	int		len;
	int		j;
	int		i;

	i = 0;
	new_export = export;
	while (export && export[i])
	{
		j = i + 1;
		len = get_start(export[i]);
		while (export && export[j])
		{
			if (comparison(export[i], export[j]))
				remove_env(export + i);
			else
				j++;
		}
		i++;
	}
	return (new_export);
}
