/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:53:28 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/08 08:29:33 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*shell_level(char **env)
{
	char		*lvl_sh;
	int			shell_lvl;

	shell_lvl = is_high_shlvl(env);
	shell_lvl++;
	lvl_sh = NULL;
	while (env && *env)
	{
		if (!ft_strncmp(*env, "SHLVL", 5))
			remove_env(env);
		else
			env++;
	}
	if (shell_lvl >= 1000)
		shell_lvl = 1;
	lvl_sh = ft_strjoin("SHLVL=", ft_itoa(shell_lvl));
	return (lvl_sh);
}

char	**necessary_values(char **env)
{
	char		**export;
	char		*pwd;
	int			i;


	i = 0;
	pwd = pwd_env(env);
	underscore_export(env);
	export = malloc(((size(env) + 4 )* sizeof(char *)));
	while (env[i])
	{
		export[i] = env[i];
		i++;
	}
	export[i++] = ft_strdup(shell_level(env));
	export[i++] = ft_strdup(pwd);
	export[i++] = ft_strdup("_=");
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
		export = malloc((size(p) + 3) * sizeof(char *));
		while (p && p[i])
		{
			export[i] = ft_strdup(p[i]);
			i++;
		}
		export[i++] = ft_strdup("OLDPWD");
		export[i] = NULL;
	}
	return (export);
}

void	exec(t_list *list)
{
	m_node	*node;
	int		num_commands;

	if (list == NULL)
		return ;
	node = (m_node *)list->content;
	if (!node)
		return ;
	if (!node->command || !node->arguments[0])
		return ;
	num_commands = ft_lstsize(list);
	if (num_commands >= 709)
	{
		printf("fork: Resource temporarily unavailable\n");
		return ;
	}
	if (num_commands == 1 && is_builtin(node->command))
		builtins(node);
	else
		multiple_pipes(node, list, num_commands);
}
