/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:21:01 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/13 17:06:01 by aaitouna         ###   ########.fr       */
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

int is_builtin(char *s)
{
	if (ft_strncmp(s, "exit", 4) == 0 || ft_strncmp(s, "cd", 2) == 0)
		return (1);
	return (0);
}

char	*get_fullpath(char *s)
{
	int		i;
	char	**paths;
	char	*cmd;
	char	*cmd_dir;
	char	*paths_list;

	i = 0;
	if (!access(s, X_OK) || is_builtin(s) == 1)
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

char *update_command(char *command)
{
	char *command_path;
	command_path = get_fullpath(command);
	if (command_path == NULL)
		ft_printf(RED "%s: command not found \n" RESET, command);
	return (command_path);
}