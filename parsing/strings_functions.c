/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:44:21 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/23 07:04:00 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	size(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

char	**append(char **Strings, char *String)
{
	int		i;
	int		len;
	char	**new_Strings;

	i = 0;
	if (Strings == NULL)
		len = 0;
	else
		len = size(Strings);
	new_Strings = malloc((len + 2) * sizeof(char *));
	while (i < len)
	{
		new_Strings[i] = ft_strdup(Strings[i]);
		i++;
	}
	new_Strings[i++] = String;
	new_Strings[i] = NULL;
	if (Strings != NULL)
		free_list(Strings);
	return (new_Strings);
}

size_t	string_list_len(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

char	*mini_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ns;
	int		j;
	int		i;

	if (s1 == NULL)
		return ((char *)s2);
	len2 = ft_strlen(s2);
	len1 = ft_strlen(s1);
	j = 0;
	i = 0;
	ns = malloc(len1 + len2 + 1);
	if (ns == NULL)
		return (NULL);
	while (s1[j])
		ns[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ns[i++] = s2[j++];
	ns[i] = '\0';
	return (ns);
}

int	is_token_sep(char *c, int i)
{
	return (!is_n_escaped(c, '|', i) && !is_n_escaped(c, '>', i)
		&& !is_n_escaped(c, '<', i) && !is_n_escaped(c, ' ', i));
}

int	is_n_escaped(char *s, char c, int i)
{
	int	b_s_count;

	b_s_count = 0;
	if (s[i] != c)
		return (0);
	--i;
	while (i >= 0 && s[i--] == '\\')
		b_s_count++;
	return (b_s_count % 2 == 0);
}
