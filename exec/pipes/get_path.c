/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:42:19 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/14 09:15:38 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

t_helper	g__helper;

void	path(char *paths, char **full_path, char *command)
{
	char	**my_paths;
	char	*program;
	int		j;

	j = 0;
	if (paths)
	{
		my_paths = ft_split(paths + 5, ':');
		while (my_paths && my_paths[j])
		{
			program = ft_strjoin("/", command);
			*full_path = ft_strjoin(my_paths[j++], program);
			free(program);
			if (access(*full_path, F_OK) == 0)
				break ;
			free(*full_path);
			*full_path = NULL;
		}
		free_list(my_paths);
	}
}

char	*get_command_path(char *command, char **env)
{
	int		i;
	char	*full_path;
	char	*paths;

	i = 0;
	full_path = NULL;
	if (access(command, X_OK) == 0)
		return (command);
	if ((!g__helper.checker) && access(ft_strjoin("/bin/", command), X_OK) == 0)
		return (ft_strjoin("/bin/", command));
	while (env && env[i])
	{
		paths = (ft_strnstr(env[i++], "PATH=", 5));
		path(paths, &full_path, command);
	}
	return (full_path);
}

char	*get_paths(char **env, char *command)
{
	char	*program_path;

	program_path = get_command_path(command, env);
	return (program_path);
}
