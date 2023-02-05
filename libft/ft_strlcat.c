/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:08:18 by aaitouna          #+#    #+#             */
/*   Updated: 2022/10/14 16:08:19 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	dstslen;
	size_t			len;

	len = ft_strlen(src);
	dstslen = ft_strlen(dst);
	if (dstslen >= size)
		return (ft_strlen(src) + size);
	i = dstslen;
	j = 0;
	while (src[j] && j < (size - dstslen - 1))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dstslen + len);
}
