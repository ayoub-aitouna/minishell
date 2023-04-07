/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:43:41 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/07 11:43:31 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

char	**update_env(char **env)
{
	char	*old_pwd;
	int		i;
	char	**new_env;

	new_env = NULL;
	old_pwd = change_env(env);
	if (old_pwd != NULL)
	{
		new_env = malloc((size(env) + 2) * sizeof(char *));
		i = 0;
		while (env[i])
		{
			new_env[i] = ft_strdup(env[i]);
			i++;
		}
		new_env[i] = ft_strdup(old_pwd);
		new_env[++i] = NULL;
		free(old_pwd);
	}
	return (new_env);
}

void	update(char **env)
{
	char	**new_env;

	new_env = update_env(env);
	get_env(new_env);
	get_export(new_env);
	free_list(new_env);
}

char	*shell_level(m_node *node, char **env)
{
	char		*lvl_sh;
	int static	shell_lvl = 1;

	lvl_sh = NULL;
	while (env && *env)
	{
		if (!ft_strncmp(*env, "SHLVL", 5))
			remove_env(env);
		else
			env++;
	}
	if (!ft_strcmp(node->command, "./minishell") \
		|| !ft_strcmp(node->command, "minishell"))
		shell_lvl++;
	lvl_sh = ft_strjoin("SHLVL=", ft_itoa(shell_lvl));
	return (lvl_sh);
}

char	*pwd_env(char **env)
{
	char	*pwd;
	char	*new_pwd;

	pwd = getcwd(NULL, 0);
	while (pwd && env && *env)
	{
		if (!ft_strncmp(*env, "PWD", 3))
			remove_env(env);
		else
			env++;
	}
	new_pwd = ft_strjoin("PWD=", pwd);
	return (new_pwd);
	free (pwd);
}

void	env_command(m_node *node)
{
	char	**env;
	int		i;

	i = 0;
	env = get_env(NULL);
	env = the_new_env(env, node);
	if (env == NULL)
		perror("env");
	if (!node->arguments[1])
	{
		while (env && env[i] && is_value(env[i]))
			printf("%s\n", env[i++]);
	}	
	else
		printf("env: %s: No such file or directory\n", node->arguments[1]);
}
