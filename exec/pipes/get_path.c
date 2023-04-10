/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:42:19 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/10 01:42:19 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

t_helper	g__helper;

int	is_builtins(t_node *node)
{
	if (ft_strcmp(node->command, "cd") == 0)
		return (1);
	else if (ft_strcmp(node->command, "echo") == 0)
		return (1);
	else if (ft_strcmp(node->command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(node->command, "export") == 0)
		return (1);
	else if (ft_strcmp(node->command, "unset") == 0)
		return (1);
	else if (ft_strcmp(node->command, "exit") == 0)
		return (1);
	else if (ft_strcmp(node->command, "env") == 0)
		return (1);
	else
		return (0);
}

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
	if (access(command, F_OK) == 0)
		return (command);
	if ((!g__helper.checker) && access(ft_strjoin("/bin/", command), F_OK) == 0)
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
	char	**list ;

	list = ft_split(command, ' ');
	program_path = get_command_path(list[0], env);
	return (program_path);
}
