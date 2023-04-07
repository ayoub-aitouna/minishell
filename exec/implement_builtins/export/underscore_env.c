/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:39:40 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/07 08:46:36 by kmahdi           ###   ########.fr       */
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

char	**export_underscore(char **export, m_node *node)
{
	char		**tmp;
	static int	var_export = 0;

	tmp = export;
	if (!ft_strcmp(node->command, "export"))
		var_export++;
	if (var_export > 1)
		underscore_export(export);
	return (tmp);
}

char	*get_underscore(char **export, m_node *node)
{
	char	*new_under;
	char	*path;
	int		len;

	len = size(node->arguments);
	path = get_paths(export, node->arguments[len - 1]);
	new_under = NULL;
	underscore_export(export);
	if (path)
		new_under = ft_strjoin("_=", path);
	else
		new_under = ft_strjoin("_=", node->arguments[len - 1]);
	return (new_under);
}

char	*change_env(char **env)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = NULL;
	pwd = getcwd(NULL, 0);
	while (env && *env)
	{
		if (!ft_strncmp(*env, "OLDPWD", 6))
			remove_env(env);
		else
			env++;
	}
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	return (old_pwd);
}
