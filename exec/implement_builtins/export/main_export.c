/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:13:06 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/08 08:36:30 by kmahdi           ###   ########.fr       */
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

int	is_high_shlvl(char **env)
{
	char		*shell_lvl;
	char		*shlvl_value;
	static int	len = 1;
	int			i;

	i = 0;
	shell_lvl = NULL;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL",5))
		{
			shell_lvl = malloc(ft_strlen(env[i] + 1));
			shell_lvl = ft_strdup(env[i]);
			break ;
		}
		i++;
	}
	if (shell_lvl)
		i = get_start(shell_lvl);
	shlvl_value = ft_substr(shell_lvl, i, ft_strlen(shell_lvl));
		len = ft_atoi(shlvl_value);
	
	return (len);
}

void	export_command(m_node *node, char	**old_export, char	**old_env)
{
	char	**export = NULL;
	char	**env = NULL;
	(void)old_env;

	export = necessary_values (old_export);
	if (node->arguments)
	{
		env = reset(env, node->arguments);
		export = reset(export, node->arguments);
	}
	underscore_export(export);
	get_export(export);
	export = get_new_export(export, node->arguments);
	sorted_list(export, size(export));
	print_export(export, node);
	env = get_new_env(env, node->arguments);
	get_export(export);
	get_env(env);
}
