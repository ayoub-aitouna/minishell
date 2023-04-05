/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:21:01 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/04 05:09:38 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	is_builtin(char *s)
{
	if (is_equal(s, "exit") || is_equal(s, "cd") || is_equal(s, "echo")
		|| is_equal(s, "pwd") || is_equal(s, "export") || is_equal(s, "unset")
		|| is_equal(s, "env"))
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
	if (!s)
		return (NULL);
	if (!access(s, X_OK) || is_builtin(s) == 1)
		return (s);
	paths_list = get_path();
	if (paths_list == NULL)
		return (NULL);
	paths = ft_split(paths_list, ':');
	free(paths_list);
	while (paths[i])
	{
		cmd_dir = ft_strjoin("/", s);
		cmd = ft_strjoin(paths[i++], cmd_dir);
		free(cmd_dir);
		if (!access(cmd, X_OK))
			break ;
		free(cmd);
		cmd = NULL;
	}
	free_list(paths);
	free(s);
	return (cmd);
}

char	*update_command(char *command)
{
	char	*command_path;

	command_path = get_fullpath(command);
	return (command_path);
}
