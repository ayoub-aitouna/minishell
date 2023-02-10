/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:32:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/10 20:29:54 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strip_nl(char *line)
{
	int	i;

	i = 0;
	if(line == NULL)
		return (NULL);
	while (line[i] != 0 && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		line[i] = 0;
	return (line);
}

int	spaces_count(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

char	*get_str(char *s, int *index)
{
	int		len;
	int		i;
	int		expanded;
	char	*new_str;

	i = 0;
	expanded = 0;
	i += spaces_count(s);
	len = calculate_len(&s[i], &expanded);
	new_str = malloc(len + expanded + 1);
	if (expanded != 0)
		copy_expanded(new_str, &s[i], len);
	else
		ft_strlcpy(new_str, &s[i], len + 1);
	i += spaces_count(&s[i + len]);
	*index = *index + i + len;
	ft_printf("get_str<%s>", new_str);
	return (new_str);
}