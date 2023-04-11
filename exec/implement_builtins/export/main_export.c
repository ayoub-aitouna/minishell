/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:13:06 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/11 11:51:44 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void	remove_env(char **env)
{
	char	**va_unset;

	va_unset = env + 1;
	while (va_unset && *va_unset)
	{
		*(va_unset - 1) = *va_unset;
		va_unset++;
	}
	*(va_unset - 1) = NULL;
	free(*(va_unset));
}

void	sorted_list(char **export, int len)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (strcmp(export[j], export[j + 1]) > 0)
			{
				temp = export[j];
				export[j] = export[j + 1];
				export[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
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
	printf_arg(new_args);
	if (new_args)
	{
		env = reset(old_env, new_args);
		export = reset(old_export, new_args);
	}
	underscore_export(export);
	export = get_new_export(export, new_args);
	sorted_list(export, size(export));
	print_export(export, new_args);
	env = get_new_env(env, new_args);
	get_export(export);
	get_env(env);
}
