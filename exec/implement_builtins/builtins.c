/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:53:24 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/08 09:12:11 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

char **under_value(char **env, m_node *node)
{
	char	**new_env;
	int		i;

	new_env = malloc(size(env) + 2 * sizeof(char *));
	i = -1;
	while (env[++i])
		new_env[i] = env[i];
	new_env[i] = get_underscore(env, node->arguments);
	printf ("%s\n", new_env[i]);
	new_env[i] = NULL;
	return (env);
}

void	builtins(m_node *node)
{
	char	**env;
	char	**export;

	env = get_env(NULL);
	env = under_value(env, node);
	get_env(env);
	export = get_export(NULL);
	underscore_export(export);
	if (!strcmp(node->command, "exit"))
		exit_command(node);
	if (!ft_strcmp(node->command, "pwd"))
		pwd_command();
	if (!ft_strcmp(node->command, "cd"))
		cd_command(node, env, export);
	if (!ft_strcmp(node->command, "echo"))
		echo_command(node);
	if (!ft_strcmp(node->command, "export"))
		export_command(node, export, env);
	if (!ft_strcmp(node->command, "unset"))
		unset_command(node, env);
	if (!ft_strcmp(node->command, "env"))
		env_command(node);
}
