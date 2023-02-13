/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:21 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/13 16:59:47 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*set_error_msg(char **holder, char *msg)
{
	*holder = msg;
	return (NULL);
}

char	*check_syntax(char *line, char **msg)
{
	int	pipe_flag;

	int i, qute_flag;
	i = 0;
	qute_flag = 0;
	pipe_flag = 0;
	*msg = NULL;
	i += spaces_count(line);
	if (line[i] == '|')
		return (set_error_msg(msg, "`|'"));
	while (line[i])
	{
		toggle_quteflag(line[i], &qute_flag);
		if (line[i] == '|')
			pipe_flag++;
		else if (line[i] != ' ' && line[i] != '\n')
			pipe_flag = 0;
		if (pipe_flag == 2)
			return (set_error_msg(msg, "`|'"));
		if (line[i] == '>')
		{
			if (line[i + 1] == '>')
				i++;
			if (get_str(&line[i + 1], &i) == NULL)
				return (set_error_msg(msg, "`newline'"));
		}
		if (line[i] == '<')
		{
			if (line[i + 1] == '<')
				i++;
			if (get_str(&line[i + 1], &i) == NULL)
				return (set_error_msg(msg, "`newline'"));
		}
		i++;
	}
	if (qute_flag != 0)
		return (set_error_msg(msg, "`\"'"));
	return (line);
}

int	handle_syntax(char *line)
{
	char	*msg;

	msg = NULL;
	if (check_syntax(line, &msg) == NULL)
	{
		ft_printf(RED "-bash: syntax error near  unexpected "
						"token %s\n" RESET,
					msg);
		add_history(line);
		return (1);
	}
	return (0);
}


char	*handle_uncomplete(char *line)
{

	return (line);
}