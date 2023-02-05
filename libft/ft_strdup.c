/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:03:18 by aaitouna          #+#    #+#             */
/*   Updated: 2022/10/14 16:03:20 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	n;

	n = ft_strlen(s);
	ptr = malloc(n + 1);
	if (ptr == NULL)
		return (NULL);
	if (n == 0)
	{
		*ptr = 0;
		return (ptr);
	}
	ft_strlcpy(ptr, s, n + 1);
	return (ptr);
}
