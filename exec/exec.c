/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:53:28 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/11 13:43:46 by kmahdi           ###   ########.fr       */
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

char	*shell_level(char **env)
{
	char		*lvl_sh;
	int			shell_lvl;

	shell_lvl = is_high_shlvl(env);
	shell_lvl++;
	lvl_sh = NULL;
	remove_ptr(env, "SHLVL");
	if (shell_lvl >= 1000)
		shell_lvl = 1;
	lvl_sh = ft_strjoin("SHLVL=", ft_itoa(shell_lvl));
	return (lvl_sh);
}

char	**necessary_values(char **env)
{
	char		**export;
	char		*pwd;
	char		*n_pwd;
	char		*shell;
	int			i;

	i = 0;
	shell = shell_level(env);
	n_pwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", n_pwd);
	underscore_export(env);
	export = malloc(((size(env) + 4) * sizeof(char *)));
	if (!export)
		exit(1);
	while (env[i])
	{
		export[i] = ft_strdup(env[i]);
		i++;
	}
	export[i++] = ft_strdup(shell);
	export[i++] = ft_strdup(pwd);
	export[i++] = ft_strdup("_=");
	export[i] = NULL;
	free (n_pwd);
	free (pwd);
	free (shell);
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
		if (!export)
			exit(1);
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
