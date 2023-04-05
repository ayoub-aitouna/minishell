/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:53:24 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/05 09:58:19 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	builtins(m_node *node)
{
	char	**env;
	char	**export;

	env = get_env(NULL);
	export = get_export(NULL);
	if (!strcmp(node->command, "exit"))
		exit_command(node);
	if (!ft_strcmp(node->command, "pwd"))
		pwd_command(node);
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
