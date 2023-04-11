/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:39:40 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/11 11:55:44 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void	underscore_export(char **export)
{
	while (export && *export)
	{
		if (!ft_strncmp(*export, "_=", 2))
			remove_env(export);
		else
			export++;
	}
}

char	*get_underscore(char **export, char **arguments)
{
	char	*new_under;
	char	*path;
	int		len;

	len = size(arguments);
	path = get_paths(export, arguments[len - 1]);
	new_under = NULL;
	underscore_export(export);
	if (path)
		new_under = ft_strjoin("_=", path);
	else
		new_under = ft_strjoin("_=", arguments[len - 1]);
	return (new_under);
}

char	*change_env(char **env)
{
	char	*pwd;
	char	*old_pwd;
	int		is_exist;

	old_pwd = NULL;
	is_exist = -1;
	while (env && *env)
	{
		if (!ft_strncmp(*env, "PWD", 3))
		{
			pwd = *env;
			is_exist = 0;
		}
		if (!ft_strncmp(*env, "OLDPWD", 6))
			remove_env(env);
		else
			env++;
	}
	if (!is_exist)
		old_pwd = ft_strjoin("OLD", pwd);
	else
		old_pwd = ft_strdup("OLDPWD=");
	return (old_pwd);
}

int	is_underscore(char **export)
{
	while (export && *export)
	{
		if (!ft_strncmp(*export, "_=", 2))
			return (1);
		else
			export++;
	}
	return (0);
}
