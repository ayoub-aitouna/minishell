/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:25:36 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/11 11:07:39 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

char	*add_quotes(char *str, int is_env)
{
	char	*new_string;
	int		start;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str) + 3;
	i = 0;
	j = 0;
	start = get_start(str);
	new_string = malloc(len * sizeof(char));
	if (!new_string)
		exit(1);
	while (j < start)
	{
		if (str[j] == '+')
			j++;
		new_string[i++] = str[j++];
	}
	if (is_env == 0)
		new_string[i++] = '\"';
	while (str[start])
		new_string[i++] = str[start++];
	if (is_env == 0)
		new_string[i++] = '\"';
	new_string[i] = '\0';
	return (new_string);
}

char	*the_added_string(char	*n_exp, char **exp, char *n_str, int start)
{
	char	*n_string;
	int		len;
	int		j;
	int		k;

	len = ft_strlen(n_str) + ft_strlen(n_exp) + 3;
	n_string = malloc(len * sizeof(char));
	if (!n_string)
		exit(1);
	j = 0;
	while (exp && n_exp && n_exp[j])
		j++;
	k = -1;
	while (++k < j)
		n_string[k] = n_exp[k];
	while (n_str[start])
		n_string[k++] = n_str[start++];
	n_string[k] = '\0';
	return (n_string);
}

char	*add_plus_string(char **export, char *new_str)
{
	int		i;
	int		start;
	int		is_equal;
	char	*new_string;
	char	*new_export;

	i = 0;
	start = 0;
	is_equal = -1;
	new_str = add_quotes(new_str, 1);
	start = get_start(new_str);
	export = get_export(NULL);
	while (export && export[i])
	{
		if (!ft_strncmp(export[i], new_str, start))
		{
			new_export = ft_strdup(export[i]);
			is_equal = 0;
		}
		i++;
	}
	if (!is_equal && new_export)
		new_string = the_added_string(new_export, export, new_str, start);
	else
		new_string = new_str;
	return (new_string);
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
		been_added = 0;
		while (new_arg && new_arg[j])
		{
			if (!ft_strncmp(arguments[i], new_arg[j], get_start(arguments[i]))
				&& is_equal_plus_str(arguments[i]) == 2)
			{		
					new_arg[j] = join_values(new_arg[j], arguments[i]);
					been_added = 1;
			}
			if (!ft_strncmp(arguments[i], new_arg[j],
					get_name_index(arguments[i]))
				&& is_equal_plus_str(arguments[i]) == 1)
			{
				new_arg[j] = ft_strdup(arguments[i]);
				been_added = 1;
			}
			j++;
		}
		if (!been_added)
			new_arg = append(new_arg, ft_strdup(arguments[i]));
		i++;
	}
	return (new_arg);
}