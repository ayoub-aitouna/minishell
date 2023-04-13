/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:49:48 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/13 17:36:56 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

int	is_forbidden_unset(char *str)
{
	int	index;

	index = 1;
	while (str[index])
	{
		if (!ft_is_alnum(str[index]))
			return (1);
		index++;
	}
	return (0);
}

void	unset_arguments(char **str, char **env, int i)
{
	int	env_index;

	env_index = 0;
	while (env[env_index])
	{
		if (!ft_strncmp(env[env_index], str[i], ft_strlen(env[env_index])))
		{
			printf("unset: '%s' : not a valid identifier\n", str[i]);
			break ;
		}
		if ((str && str[i]) && !ft_strncmp(env[env_index], \
			str[i], ft_strlen(str[i]))
			&& env[env_index][ft_strlen(str[i])] == '=')
			remove_env(env + env_index);
		env_index++;
	}
}

void	unset_valid(char **str, char **env)
{
	int	i;

	i = 1;
	while (str && str[i])
	{
		if (str[i][0] == '#')
			break ;
		if ((str && str[i]) && (!ft_isalpha(str[i][0])
			|| (is_forbidden_unset(str[i]))))
		{
			printf("unset: '%s' : not a valid identifier\n", str[i++]);
			continue ;
		}
		unset_arguments(str, env, i++);
	}
}

char	**unset_env(char **str, char **env)
{
	char	**tmp;

	tmp = env;
	unset_valid(str, env);
	return (tmp);
}

void	unset_command(t_node *node, char **env)
{
	char	**new_env;

	free_list(get_export(NULL));
	new_env = unset_env(node->arguments, env);
	get_env(new_env);
	get_export(new_env);
	free_list(new_env);
}
