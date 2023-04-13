/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:53:24 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/13 14:43:05 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

char	**underscore_value(char **env, t_node *node)
{
	char	**new_env;
	int		i;

	new_env = malloc((size(env) + 2) * sizeof(char *));
	if (!new_env)
		exit(1);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = get_underscore(env, node->arguments);
	new_env[++i] = NULL;
	return (new_env);
}

void	builtins(t_node *node)
{
	char	**env;
	char	**export;

	export = get_export(NULL);
	env = get_env(NULL);
	if (!strcmp(node->command, "exit"))
		exit_command(node);
	if (!ft_strcmp(node->command, "cd"))
		cd_command(node, env, export);
	if (!ft_strcmp(node->command, "export"))
		export_command(node, export, env);
	if (!ft_strcmp(node->command, "unset"))
		unset_command(node, env);
}

void	child_builtins(t_node *node)
{
	char	**export;
	char	**new_args;
	char	**env;

	new_args = get_new_arguments(node->arguments);
	export = get_export(NULL);
	env = get_env(NULL);
	if (!ft_strcmp(node->command, "export"))
		print_export(export, new_args);
	if (!ft_strcmp(node->command, "echo"))
		echo_command(node);
	if (!ft_strcmp(node->command, "env"))
		env_command(node, env);
	if (!ft_strcmp(node->command, "pwd"))
		pwd_command();
}
