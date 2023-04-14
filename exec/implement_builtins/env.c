/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:43:41 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/13 16:15:31 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

int	is_high_shlvl(char **env)
{
	char		*shell_lvl;
	char		*shlvl_value;
	static int	len = 1;
	int			i;

	i = 0;
	shell_lvl = NULL;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL", 5))
		{
			shell_lvl = ft_strdup(env[i]);
			break ;
		}
		i++;
	}
	if (shell_lvl)
		i = get_start(shell_lvl);
	shlvl_value = ft_substr(shell_lvl, i, ft_strlen(shell_lvl));
	len = ft_atoi(shlvl_value);
	printf("len %d %s \n ", len, shell_lvl);
	free (shell_lvl);
	free (shlvl_value);
	return (len);
}

char	**update_env(char **env)
{
	char	*old_pwd;
	int		i;
	char	*pwd;
	char	*n_pwd;
	char	**new_env;

	new_env = NULL;
	old_pwd = change_env(env);
	n_pwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", n_pwd);
	if (old_pwd || pwd)
	{
		new_env = malloc((size(env) + 2) * sizeof(char *));
		if (!new_env)
			exit(1);
		i = 0;
		while (env[i])
		{
			if (!ft_strncmp(env[i], "PWD", 2))
			{
				new_env[i] = ft_strdup(pwd);
				if (pwd)
					free(pwd);
			}
			else
				new_env[i] = ft_strdup(env[i]);
			i++;
		}
		new_env[i] = ft_strdup(old_pwd);
		new_env[++i] = NULL;
		free(old_pwd);
	}
	free(n_pwd);
	// free(pwd);
	return (new_env);
}

void	update(char **env)
{
	char	**new_env;

	new_env = update_env(env);
	free_list(get_env(NULL));
	free_list(get_export(NULL));
	get_env(new_env);
	get_export(new_env);
	free_list(new_env);
}

void	env_command(t_node *node, char **env)
{
	int		i;

	i = 0;
	env = underscore_value(env, node);
	env = remove_duplicate(env);
	get_env (env);
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
