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

char *set_error_msg(char **holder, char *msg)
{
	*holder = msg;
	return (NULL);
}

char *check_syntax(char *line, char **msg)
{
	int i, qute_flag;
	i = 0;
	qute_flag = 0;
	int pipe_flag = 0;
	*msg = NULL;
	i += spaces_count(line);
	if (line[i] == '|')
		return (set_error_msg(msg, " unexpected token `|'"));
	while (line[i])
	{
		toggle_quteflag(line[i], &qute_flag);
		if (line[i] == '|')
			pipe_flag++;
		else if (line[i] != ' ' && line[i] != '\n')
			pipe_flag = 0;
		if (pipe_flag == 2)
			return (set_error_msg(msg, " unexpected token `|'"));
		if (line[i] == '>')
		{
			if (line[i + 1] == '>')
				i++;
			if (get_str(&line[i + 1], &i) == NULL)
				return (set_error_msg(msg, " unexpected token `newline'"));
		}
		if (line[i] == '<')
		{
			if (line[i + 1] == '<')
				i++;
			if (get_str(&line[i + 1], &i) == NULL)
				return (set_error_msg(msg, " unexpected token `newline'"));
		}
		i++;
	}
	if (qute_flag != 0)
		return (set_error_msg(msg, " unexpected token `\"'"));
	return (line);
}
