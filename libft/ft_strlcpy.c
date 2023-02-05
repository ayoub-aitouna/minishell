/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:08:31 by aaitouna          #+#    #+#             */
/*   Updated: 2022/10/14 16:08:32 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	const char	*osrc;
	size_t		l_room;

	osrc = src;
	l_room = dst_size;
	if (l_room != 0)
	{
		while (--l_room != 0)
		{
			*dst = *src;
			if (*src == '\0')
				break ;
			dst++;
			src++;
		}
	}
	if (l_room == 0)
		if (dst_size != 0)
			*dst = '\0';
	return (ft_strlen(osrc));
}
