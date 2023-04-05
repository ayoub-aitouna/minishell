/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:25:36 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/05 07:47:25 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec.h"

char *add_quotes(char *str, int is_env)
{
	int start;
	int len;
	int i;
	int j;
	char *new_string;

	start = 0;
	len = ft_strlen(str)  + 3;
	i = 0;
	j = 0;
	while(str[start] != '=' && str[start])
		start++;
	if (str[start] == '=')
		start++;
	new_string = malloc(len * sizeof(char));
	while(j < start)
	{
		if(str[j] == '+')
			j++;
		new_string[i++] = str[j++];
	}
	if (is_env == 0)
		new_string[i++] = '\"';
	while(str[start])
		new_string[i++] = str[start++];
	if (is_env == 0)
		new_string[i++] = '\"';
	new_string[i] = '\0';
	// free(str);
	return (new_string);
}

char *add_plus_string(char **export , char *new_str)
{
	int i;
	int j ;
	int start;
	int len;
	int is_equal;
	char *new_string;
	char *new_export;
	
	i = 0;
	start = 0;
	int k = 0;
	is_equal = -1;
	new_str = add_quotes(new_str, 1);
	while(new_str[start] && (new_str[start] != '='))
		start++;
	if (new_str[start] == '=')
			start++;
	while (export[i])
	{
		if (!ft_strncmp(export[i], new_str, start))
		{
			new_export = ft_strdup(export[i]);
			is_equal = 0;
		}
		i++;
	}
	if (!is_equal && new_export)
	{
		len = ft_strlen(new_str) + ft_strlen(new_export) + 3;
		new_string = malloc(len * sizeof(char));
		j = 0;
		while (export && new_export && new_export[j])
			j++;
		k = 0;
		int n = 0;
		while(k < j)
			new_string[k++] = new_export[n++];
		while(new_str[start])
			new_string[k++] = new_str[start++];
		new_string[k] = '\0';
	}
	else
		new_string = new_str;
	return (new_string);
}
