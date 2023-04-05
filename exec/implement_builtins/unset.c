/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:49:48 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/05 11:17:02 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

int	ft_is_alnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}

int	is_forbidden_unset(char *str)
{
	int index;

	index = 1;

	while(str[index])
	{
		if(!ft_is_alnum(str[index]))
			return (1);
		index++;
	}
	return (0);
}
void unset_valid(char **str, char **env)
{
	int	i;

	i = 1;
	int env_index = 0;
	while (str && str[i])
	{
		env_index = 0;
		if(str[i][0] == '#')
			break;
		if ((str && str[i]) && (!ft_isalpha(str[i][0]) || (is_forbidden_unset(str[i]))))
		{
			printf("unset: '%s' : not a valid identifier\n", str[i++]);
			continue;	
		}
		while (env[env_index])
		{
			if(!ft_strncmp(env[env_index], str[i], ft_strlen(env[env_index])))
			{
				printf("unset: '%s' : not a valid identifier\n", str[i]);
				break;
			}
			if ((str && str[i]) && !ft_strncmp(env[env_index], str[i], ft_strlen(str[i]))
				&& env[env_index][ft_strlen(str[i])] == '=')
				remove_env(env + env_index);
			env_index++;
		}
		i++;
	}
}
char	**unset_env(char **str, char **env)
{
	char	**tmp;

	tmp = env;
	// while (*env)
	unset_valid(str, env);
	return (tmp);
}

void	unset_command(m_node *node, char **env)
{
	char	**new_env;
	
	// new_env = env;
	new_env = unset_env(node->arguments, env);
	get_env(new_env);
	get_export(new_env);
	free_list(new_env);	
}
