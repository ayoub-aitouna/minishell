/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:07:55 by aaitouna          #+#    #+#             */
/*   Updated: 2023/03/29 03:56:49 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ns;
	int		j;
	int		i;

	if (!s1 || !s2)
		return (NULL);
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
