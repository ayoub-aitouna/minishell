/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:53:28 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/14 07:51:03 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	remove_ptr(char **env, char *ptr)
{
	while (env && *env)
	{
		if (!ft_strncmp(*env, ptr, ft_strlen(ptr)))
			remove_env(env);
		else
			env++;
	}
}

void	remove_env(char **env)
{
	char	**va_unset;

	va_unset = env + 1;
	while (va_unset && *va_unset)
	{
		*(va_unset - 1) = *va_unset;
		va_unset++;
	}
	*(va_unset - 1) = NULL;
	free(*(va_unset));
}

char	**necessary_values(char **env, int is_env)
{
	char		**export;
	char		*n_pwd;
	int			i;

	n_pwd = getcwd(NULL, 0);
	remove_ptr(env, "OLDPWD");
	remove_ptr(env, "_=");
	remove_ptr(env, "PWD");
	remove_ptr(env, "SHLVL");
	export = malloc(((size(env) + 3) * sizeof(char *)));
	if (!export)
		exit(1);
	i = -1;
	while (env[++i])
		export[i] = ft_strdup(env[i]);
	export[i++] = shell_level(env);
	export[i++] = m_safe_strjoin("PWD=", n_pwd, 2);
	if (is_env == 0)
		export[i++] = ft_strdup("OLDPWD");
	export[i] = NULL;
	return (export);
}

char	**get_export(char **p)
{
	static char	**export;
	int			i;

	i = 0;
	if (p != NULL)
	{
		export = malloc((size(p) + 1) * sizeof(char *));
		if (!export)
			exit(1);
		while (p && p[i])
		{
			export[i] = ft_strdup(p[i]);
			i++;
		}
		export[i] = NULL;
	}
	return (export);
}

void	exec(t_list *list)
{
	char	**env;
	t_node	*node;
	int		num_commands;

	if (list == NULL)
		return ;
	node = (t_node *)list->content;
	if (!node)
		return ;
	if (!node->command || !node->arguments[0])
		return ;
	env = get_env(NULL);
	num_commands = ft_lstsize(list);
	if (num_commands >= 709)
	{
		printf("fork: Resource temporarily unavailable\n");
		return ;
	}
	multiple_pipes(node, list, num_commands);
}
