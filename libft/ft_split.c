/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:02:51 by aaitouna          #+#    #+#             */
/*   Updated: 2022/10/14 16:02:53 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief counts how many str in result of spliting
 *
 * @param s {char *} str to be splited
 * @param c {char } sip
 * @return  {size_t} number of strs in result
 */
static size_t	cont_strings(const char *s, char c)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			counter++;
		while (s[i] && s[i] != c)
			i++;
		i++;
	}
	return (counter);
}

/**
 * @brief counts how many litter in one part of string
 *
 * @param s {char *} str to be splited
 * @param c {char } Spirator
 *@return size_t {size_t} how many litter in str
  starting from an adreess tell finding the sip
 */
static size_t	count_litters(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

/**
* @brief allocated new memory of <count_litters> bytes and
		copies the from s tell sip found
 * @param s {char *} str to be splited
 * @param c {char } sip
 * @return {char *} a part of result
 */
static char	*part(const char *s, char c)
{
	int		n;
	int		i;
	char	*ptr;

	i = 0;
	n = count_litters(s, c);
	ptr = (char *)malloc(sizeof(char) * (n + 1));
	if (ptr == NULL)
		return (NULL);
	while (i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

/**

	* @brief loops on S and increments if found any C if not
		call function part of that address and assing rsukt to rs,
			and increment i tell new sip fond
 *
 * @param rs {Char **} holder to put result string in it
 * @param s {Char *} source string to be splited
 * @param c {char } Spiratpor
 * @return {char **} returns rs
 */
static char	**spliter(char **rs, char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			rs[i] = part(s, c);
			if (rs[i] == NULL)
			{
				i = 0;
				while (rs[i] != NULL)
					free(rs[i]);
				return (NULL);
			}
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	rs[i] = 0;
	return (rs);
}

/**
	* @param {String} cs:  The string to be split
	* @param {Char} c:  The delimiter character.
 	* @returns  The array of new strings resulting from
					the split. NULL if the allocation fails.
 	* @brief Allocates (with malloc(3)) and returns an array
				of strings obtained by splitting ’s’ using the
				character ’c’ as a delimiter.  The array must end
				with a NULL pointer.
 */
char	**ft_split(char const *s, char c)
{
	int		strings_count;
	char	**rs;

	if (!s)
		return (NULL);
	strings_count = cont_strings(s, c);
	rs = (char **)malloc((strings_count + 1) * sizeof(char *));
	if (!rs)
		return (NULL);
	if (!spliter(rs, s, c))
		return (NULL);
	return (rs);
}
