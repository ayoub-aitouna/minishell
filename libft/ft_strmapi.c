/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:09:02 by aaitouna          #+#    #+#             */
/*   Updated: 2022/10/14 16:09:03 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies the function ’f’ to each character of the
string ’s’, and passing its index as first argument
to create a new string (with malloc(3)) resulting
from successive applications of ’f’.
 *
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 * @return s {char*} The string created from the successive applications of ’f’.
Returns NULL if the allocation fails.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		buff;
	char	*ns;

	if (!s || !f)
		return (NULL);
	buff = ft_strlen((char *)s);
	ns = (char *)malloc(sizeof(char) * buff + 1);
	if (!ns)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ns[i] = (*f)(i, s[i]);
		i++;
	}
	ns[i] = 0;
	return (ns);
}
