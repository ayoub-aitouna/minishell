/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:39:40 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/05 09:27:31 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec.h"

void	underscore_export(char **export)
{
	while(export && *export)
	{
		if(!ft_strncmp(*export, "_=", 2))
		{
			printf("removing %s\n", *export);
			remove_env(export);	
		}
		else
			export++;
	}
}

char **export_underscore(char **export, m_node *node)
{
	char **tmp = export;
	static int		var_export = 0;
	
	if (!ft_strcmp(node->command, "export"))
		var_export++;
	if(var_export > 1)
		underscore_export(export);
	return (tmp);
	
}
char *get_underscore(char **export, m_node *node)
{
	char *new_under;
	char *path;
	int len = size(node->arguments);
	
	path = get_paths(export, node->arguments[len - 1]);
	new_under = NULL;
	underscore_export(export);
	if (path)
		new_under = ft_strjoin("_=",path);
	else
		new_under = ft_strjoin("_=",node->arguments[len - 1]);
	return (new_under);
	
}
