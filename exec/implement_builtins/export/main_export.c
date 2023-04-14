/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:13:06 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/14 08:12:30 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int len_comparison(char *s1, char *s2)

{
	int index1 = get_name_index(s1);
	int index2 = get_name_index (s2);

	if ((index2 - index1) == 0 && !ft_strncmp(s1, s2, index2))
		return (1);
	return (0);
}

int	add_or_replace(char **arguments, char **new_arg, int j , int i)
{
	int	been_added;

	been_added = 0;
	while (new_arg && new_arg[j])
	{
		if (is_equal_plus_str(arguments[i]) == 2)
		{	
			if (len_comparison(arguments[i], new_arg[j]))
			{
				new_arg[j] = join_values(new_arg[j], arguments[i]);
				been_added = 1;
			}
		}
		else if (len_comparison(arguments[i], new_arg[j])
			&& is_equal_plus_str(arguments[i]) == 1)
		{
			new_arg[j] = ft_strdup(arguments[i]);
			been_added = 1;
		}
		j++;
	}
	return (been_added);
}

char	**get_new_arguments(char **arguments)
{
	char	**new_arg;
	int		i;
	int		j;
	int		been_added;

	new_arg = NULL;
	i = 0;
	while (arguments && arguments[i])
	{
		j = 0;
		been_added = add_or_replace(arguments, new_arg, j, i);
		if (!been_added)
			new_arg = append(new_arg, ft_strdup(arguments[i]));
		i++;
	}
	return (new_arg);
}

char	*join_values(char *s1, char *s2)
{
	char	*re;
	int		j;

	re = NULL;
	j = get_start(s1);
	while (s1 && s1[j])
		re = ft_str_append(re, s1[j++]);
	j = get_start(s2);
	while (s2 && s2[j])
		re = ft_str_append(re, s2[j++]);
	re = ft_strjoin(ft_substr(s1, 0, get_start(s1)), re);
	return (re);
}

void	print_export(char **export, char **new_args)
{
	char	*value;
	int		i;

	i = 0;
	while (export && export[i] && !new_args[1])
	{
		if (is_value(export[i]) && !is_underscore(export))
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

void	export_command(t_node *node, char	**old_export, char	**old_env)
{
	char	**export;
	char	**env;
	char	**new_args;

	export = NULL;
	env = NULL;
	new_args = get_new_arguments(node->arguments);
	if (new_args)
	{
		env = reset(old_env, new_args);
		export = reset(old_export, new_args);
	}
	underscore_export(export);
	export = get_new_export(export, new_args);
	sorted_list(export, size(export));
	print_export(export, new_args);
	free_list(get_export(NULL));
	get_export(export);
	env = get_new_env(env, new_args);
	get_env(env);
	free_list(export);
	free_list(new_args);
}