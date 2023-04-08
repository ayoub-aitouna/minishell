/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:43:41 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/08 08:49:01 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

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

char	**update_env(char **env)
{
	char	*old_pwd;
	int		i;
	char    *pwd;
	char	**new_env;

	new_env = NULL;
	old_pwd = change_env(env);
	pwd = pwd_env(env);
	printf("%s\n", pwd);
	if (old_pwd != NULL)
	{
		new_env = malloc((size(env) + 3) * sizeof(char *));
		i = 0;
		while (env[i])
		{
			new_env[i] = ft_strdup(env[i]);
			i++;
		}
		new_env[i] = ft_strdup(pwd);
		new_env[++i] = ft_strdup(old_pwd);
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

void	env_command(m_node *node)
{
	char	**env;
	int		i;

	i = 0;
	env = get_env(NULL);
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
