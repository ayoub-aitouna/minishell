/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:09:32 by aaitouna          #+#    #+#             */
/*   Updated: 2023/03/31 06:42:52 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && cs1[i] == cs2[i] && cs1[i] && cs2[i] && cs1 && cs2)
		i++;
	return (cs1[i] - cs2[i]);
}
