/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 05:13:18 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/07 05:47:54 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

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
			else if (!ft_strncmp(*env, argument[i], len)
				&& is_value(argument[i]))
				remove_env(env);
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
			if (ft_strncmp(export[i], export[j], len) == 0)
				remove_env(export + i);
			else
				j++;
		}
		i++;
	}
	return (new_export);
}
