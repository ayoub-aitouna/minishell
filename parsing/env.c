/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:41:59 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/23 09:42:23 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_getenv(char *name)
{
	int i;
	char **env;
	char *value;
	i = 0;
	if (!name)
		return (NULL);
	env = get_env(NULL);
	while (env[i])
	{
		char *new_name = ft_strjoin(name, "=");
		value = ft_strnstr(env[i], new_name, ft_strlen(new_name));
		if (value != NULL)
			return (value + ft_strlen(new_name));
		i++;
	}
	return (NULL);
}
