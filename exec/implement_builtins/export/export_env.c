/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:38:44 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/05 10:59:50 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec.h"

void	add_new_env(char **env, char **old_env, char **arguments)
{
	int	i;
	int	j;
	int	k;
	
	i = 0;
	k = 1;
	while (old_env && old_env[i])
	{
		env[i] = ft_strdup(old_env[i]);
		i++;
	}
	while (arguments && arguments[k])
	{
		if (arguments && arguments[k])
		{
			j = 0;
			if (arguments[k][0] == '#')
				break ;
			while (arguments && arguments[k] && arguments[k][j])
			{
				if (arguments[k][j] == '=' && arguments[k][j- 1] != '+')
				{
					env[i++] = ft_strdup(arguments[k]);
					break ;
				}
				else if (arguments[k][j] == '=' && arguments[k][j - 1] == '+' && arguments[k][j - 1])
				{
					env[i++] = ft_strdup(add_plus_string(old_env, arguments[k]));
					break ;
				}
				j++;
			}
			k++;
		}
		else
			k++;
	}
	env[i] = NULL;
	// free_list(old_env);
}

char	**get_new_env(char **old_env, char **arguments)
{
	char	**env;

	env = NULL;
	if (old_env != NULL && !arguments[1])
		env = get_env(NULL);
	else if (old_env != NULL)
	{
		env = malloc((size(old_env) + size(arguments)) * sizeof(char *));
		add_new_env(env, old_env, arguments);
	}
	env = reset_forbidden_env(env);
	env = remove_duplicate(env);
	return (env);
}

void print_export(char **export, m_node *node)
{
	char	*value;
	int i;

	i = 0;
	while (export && export[i] && !node->arguments[1])
	{
		if (is_value(export[i]))
		{
			value = add_quotes(export[i], 0);
			printf("declare -x %s\n", value);
			free(value);
		}
		else
			printf("declare -x %s\n", export[i]);
		i++;
	}
}

void	export_command(m_node *node, char	**old_export, char	**old_env)
{
	char	**export;
	char	**env;
	
	if (node->arguments)
	{
		env = reset(old_env, node->arguments);
		export = reset(old_export, node->arguments);
	}
	env = get_new_env(old_env, node->arguments);
	export = get_new_export(old_export, node->arguments);
	export = the_new_env(export, node);
	export = export_underscore(export, node);
	print_export(export, node);
	get_export(export);
	get_env(env);
}


