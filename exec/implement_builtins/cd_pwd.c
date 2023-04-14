/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:45:41 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/14 15:27:37 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	pwd_command(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		printf("minishell :No such file or directory\n");
	else
		printf("%s\n", pwd);
	free (pwd);
}

char	**cd_tilde(t_node *node)
{
	char	**dir;
	int		i;

	dir = NULL;
	if (node->arguments[1][1] == '/')
	{
		i = 0;
		while (node->arguments[1][i])
		{
			if (node->arguments[1][i] == '~')
				i++;
			dir = ft_split(node->arguments[1], '/');
			i++;
		}
	}
	return (dir);
}

void	cd(t_node *node)
{			
	char		**dir;
	struct stat	sb;
	char		*pwd;

	pwd = getcwd(NULL, 0);
	if (node->arguments[1][0] == '~')
	{
		dir = cd_tilde(node);
		while (*dir)
		{
			if (stat(*dir, &sb) == 0 && S_ISDIR(sb.st_mode))
				chdir(*dir);
			dir++;
		}
	}
	else if (stat(node->arguments[1], &sb) == 0 && S_ISDIR(sb.st_mode))
		chdir(node->arguments[1]);
	else if (S_ISREG(sb.st_mode))
		printf("cd: %s: Not a directory\n", node->arguments[1]);
	else
		printf("cd: no such file or directory: %s\n", node->arguments[1]);
	if (!pwd)
		perror("chdir: error retrieving current directory:"
			"getcwd: cannot access parent directories: ");
	free (pwd);
}

void	cd_command(t_node *node, char **env, char **export)
{
	if (!node->arguments[1] || !strcmp(node->arguments[1], "~"))
		chdir(getenv("HOME"));
	else
		cd(node);
	update(get_export(NULL));
}
