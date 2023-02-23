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

char	*ft_getenv(char *name)
{
	int		i;
	char	**env;
	char	*value;

	i = 0;
	if (!name)
		return (NULL);
	env = get_env(NULL);
	while (env[i])
	{
		value = ft_strnstr(env[i], name, ft_strlen(name));
		if (value != NULL)
			return (value + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}
