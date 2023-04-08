/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:41:59 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/08 07:13:21 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_env(char **p)
{
	static char	**env;
	int			i;

	i = 0;
	if (p != NULL)
	{
		env = malloc((size(p) + 1) * sizeof(char *));
		while (p[i])
		{
			env[i] = ft_strdup(p[i]);
			i++;
		}
		env[i] = NULL;
	}
	return (env);
}

char	*ft_getenv(char *name)
{
	int		i;
	char	**env;
	char	*value;
	char	*new_name;

	i = 0;
	if (!name)
		return (NULL);
	env = get_env(NULL);
	while (env[i])
	{
		new_name = ft_strjoin(name, "=");
		value = ft_strnstr(env[i], new_name, ft_strlen(new_name));
		if (value != NULL)
		{
			value += ft_strlen(new_name);
			free(new_name);
			return (value);
		}
		i++;
	}
	return (NULL);
}
