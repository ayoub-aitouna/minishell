/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:23:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/23 12:25:53 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	remove_env(char **p, int index)
{
	int		i;
	int		j;
	char	**new_env;

	j = 0;
	i = 0;
	new_env = malloc(sizeof(char *) * (size(p)));
	while (p[i])
	{
		if (i != index)
			new_env[j++] = ft_strdup(p[i]);
		i++;
	}
	new_env[j] = NULL;
	get_env(new_env);
	free_list(p);
	free_list(new_env);
}
void	add_env(char *env_val)
{
	int		i;
	char	**new_env;
	char	**p;

	i = 0;
	p = get_env(NULL);
	new_env = malloc(sizeof(char *) * (size(p) + 2));
	while (p[i])
	{
		new_env[i] = ft_strdup(p[i]);
		i++;
	}
	new_env[i++] = ft_strdup(env_val);
	new_env[i] = NULL;
	get_env(new_env);
	free_list(p);
	free_list(new_env);
}

void	env(void)
{
	int		i;
	char	**env;

	i = 0;
	env = get_env(NULL);
	while (env[i])
		printf("%s\n", env[i++]);
}

void	unset(char *name)
{
	int		i;
	char	**env;
	char	*value;

	i = 0;
	if (!name)
		return ;
	env = get_env(NULL);
	while (env[i])
	{
		value = ft_strnstr(env[i], name, ft_strlen(name));
		if (value != NULL)
			return (remove_env(env, i));
		i++;
	}
}

void	export(char *env_var)
{
	int i = 0;
	char *var_name = NULL;
	char *var_value = NULL;
	if (env_var == NULL)
		return ;
	while (env_var[i] && env_var[i] != '=')
		var_name = ft_str_append(var_name, env_var[i++]);
	if (env_var[i] == '=')
		i++;
	while (env_var[i])
		var_value = ft_str_append(var_value, env_var[i++]);
	ft_printf("<%s> = <%s> <%s>", var_name, var_value, env_var);
	if (var_name == NULL || var_value == NULL)
		return ;
	unset(var_name);
	add_env(env_var);
}