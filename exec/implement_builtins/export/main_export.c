/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:13:06 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/10 08:33:12 by kmahdi           ###   ########.fr       */
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

int	is_underscore(char **export)
{
	while (export && *export)
	{
		if (!ft_strncmp(*export, "_=", 2))
			return (1);
		else
			export++;
	}
	return (0);
}

void	print_export(char **export, t_node *node)
{
	char	*value;
	int		i;

	i = 0;
	while (export && export[i] && !node->arguments[1])
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
		if (!ft_strncmp(env[i], "SHLVL", 5))
		{
			shell_lvl = malloc(ft_strlen(env[i] + 1));
			if (!shell_lvl)
				exit(1);
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

void	export_command(t_node *node, char	**old_export, char	**old_env)
{
	char	**export;
	char	**env;

	export = NULL;
	env = NULL;
	if (node->arguments)
	{
		env = reset(old_env, node->arguments);
		export = reset(old_export, node->arguments);
	}
	underscore_export(export);
	export = get_new_export(export, node->arguments);
	sorted_list(export, size(export));
	print_export(export, node);
	env = get_new_env(env, node->arguments);
	get_export(export);
	get_env(env);
}
