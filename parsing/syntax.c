/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:21 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/17 16:28:18 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*set_error_msg(char **holder, char *msg)
{
	*holder = msg;
	return (NULL);
}

int	check_redirections_syntax(char *line, char **msg)
{
	int	i;

	i = 0;
	if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			i++;
		if (get_str(&line[i + 1], &i, 1) == NULL)
			return (1);
	}
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
		{
			if (get_str(&line[i + 2], &i, 0) == NULL)
				return (1);
		}
		else if (get_str(&line[i + 1], &i, 1) == NULL)
			return (1);
	}
	return (0);
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
		if (check_redirections_syntax(&line[i++], msg))
			return (set_error_msg(msg, "`newline'"));
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

int	is_nl(char *line, int i)
{
	int	n_only;

	n_only = 0;
	if (i > 0)
		n_only = (line[i - 1] == '\\');
	return (line[i] == '\\' && line[i + 1] == 0 && !n_only);
}

int	is_complete(char *line)
{
	int	i;
	int	is_complete;

	i = 0;
	is_complete = 1;
	while (line[i])
	{
		if (line[i] == '|' || is_nl(line, i))
			is_complete = 0;
		else if (line[i] != ' ' && line[i] != '\n')
			is_complete = 1;
		i++;
	}
	return (is_complete);
}
