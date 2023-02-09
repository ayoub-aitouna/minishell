/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:32:11 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/09 18:21:37 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_name(char *s)
{
	int		i;
	char	*name;
	char	*env;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '$')
		i++;
	if (i == 0)
		return (0);
	name = malloc(i);
	ft_strlcpy(name, s, i);
	return (name);
}

size_t	calculate_len(char *s, int *expanded)
{
	int		qute_flag;
	size_t	i;

	qute_flag = 0;
	i = 0;
	while (s[i] != 0 && ((s[i] != '|' && s[i] != '>' && s[i] != '<'
				&& s[i] != ' ') || qute_flag))
	{
		if (qute_flag == 2 && s[i] == '$')
			*expanded += ft_strlen(getenv(get_env_name(&s[i + 1])));
		if (s[i] == '"' && qute_flag == 0)
			qute_flag = 2;
		else if (s[i] == '\'' && qute_flag == 0)
			qute_flag = 1;
		else if ((s[i] == '\'' && qute_flag == 1) || (s[i] == '"'
					&& qute_flag == 2))
			qute_flag = 0;
		i++;
	}
	qoute(qute_flag, 0);
	return (i);
}

void	copy_expanded(char *dst, char *src, int len)
{
	int		i;
	int		j;
	int		k;
	char	*env_variable;
	char	*name;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '$')
		{
			name = get_env_name(&src[i + 1]);
			env_variable = getenv(name);
			if (env_variable != NULL)
			{
				k = 0;
				while (env_variable[k])
					dst[j++] = env_variable[k++];
				i += ft_strlen(name) + 1;
			}
		}
		dst[j++] = src[i++];
	}
	dst[j] = 0;
}
