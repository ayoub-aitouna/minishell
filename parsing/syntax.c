/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:21 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/12 14:39:12 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_syntax(char *line, char **msg)
{
	int i, qute_flag;
	i = 0;
	qute_flag = 0;
	*msg = NULL;
	if (line[i] == '|')
	{
		*msg = "unexpected token `|'";
		return (NULL);
	}
	while (line[i])
	{
		toggle_quteflag(line[i], &qute_flag);
		i++;
	}
	if (qute_flag != 0)
	{
		*msg = " unexpected token `\"'";
		return (NULL);
	}
	return (line);
}
