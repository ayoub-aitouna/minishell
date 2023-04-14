/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:21:01 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/13 13:47:32 by kmahdi           ###   ########.fr       */
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

int	is_builtin(char *s, char *arg)
{
	if (is_equal(s, "exit") || is_equal(s, "cd")
		|| is_equal(s, "unset")
		|| (is_equal(s, "export") && arg))
		return (1);
	return (0);
}

int	is_child_builtins(char *s, char *arg)
{
	if (is_equal(s, "echo") || is_equal(s, "pwd")
		|| (is_equal(s, "export") && !arg)
		|| is_equal(s, "env"))
		return (1);
	return (0);
}
