/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:21:01 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/13 15:26:31 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(void)
{
	char	**env;
	int		i;

	i = 0;
	env = get_env(NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (NULL);
}

char	*get_fullpath(char *s)
{
	int		i;
	char	**paths;
	char	*cmd;
	char	*cmd_dir;
	char	*paths_list;

	i = 0;
	if (!access(s, X_OK) || ft_strncmp(s, "exit", 4) == 0)
		return (s);
	paths_list = get_path();
	paths = ft_split(paths_list, ':');
	free(paths_list);
	while (paths[i])
	{
		cmd_dir = ft_strjoin("/", s);
		cmd = ft_strjoin(paths[i], cmd_dir);
		free(cmd_dir);
		if (!access(cmd, X_OK))
			break ;
		free(cmd);
		cmd = NULL;
		i++;
	}
	i = 0;
	free_list(paths);
	return (cmd);
}

void	update_command(m_node *node)
{
	char *command_path;
	command_path = get_fullpath(node->command);
	if (command_path == NULL)
		ft_printf(RED "%s: command not found \n" RESET, node->command);
	node->command = command_path;
}