/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:13:06 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/07 11:32:31 by kmahdi           ###   ########.fr       */
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

void	print_export(char **export, m_node *node)
{
	char	*value;
	int		i;

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
	export = get_new_export(old_export, node->arguments);
	export = the_new_env(export, node);
	export = export_underscore(export, node);
	sorted_list(export, size(export));
	print_export(export, node);
	env = get_new_env(old_env, node->arguments);
	get_export(export);
	get_env(env);
}
