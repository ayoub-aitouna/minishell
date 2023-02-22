/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:21 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/21 10:19:58 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int find_file_name(char *ptr)
{
	int i = 0;
	while (ptr[i] && ptr[i] == ' ')
	{
		i++;
	}
	if (ptr[i] == 0)
		return 0;
	else if (ft_strchr(">;|<\n", ptr[i]))
		return ptr[i];
	return (-1);
}

char check_redirections_syntax(char *line)
{
	int i;
	int val;

	i = 0;
	if (is_n_escaped(line, '>', i))
	{
		if (is_n_escaped(line, '>', i + 1))
			i++;
		if (ft_strchr(">;|<\n", line[i + 1]) || line[i + 1] == 0)
			return line[i];
		val = find_file_name(&line[i + 1]);
		printf("val %d %c \n", val, val);
		if (val != 1)
			return (val);
	}
	if (is_n_escaped(line, '<', i))
	{
		if (is_n_escaped(line, '<', i + 1))
			i++;
		else if (is_n_escaped(line, '>', i + 1))
			i++;
		if (ft_strchr(">;|<\n", line[i + 1]) || line[i + 1] == 0)
			return line[i + 1];
		val = find_file_name(&line[i + 1]);
		if (val != 1)
			return (val);
	}
	return (-1);
}

char check_syntax(char *line)
{
	int pipe_flag;
	char element_err;
	int i, qute_flag;

	i = 0;
	qute_flag = 0;
	pipe_flag = 0;
	i += spaces_count(line);
	if (line[i] == '|')
		return (line[i + 1]);
	while (line[i])
	{
		if (is_n_escaped(line, '"', i) || is_n_escaped(line, '\'', i))
			toggle_quteflag(line[i], &qute_flag);
		if (is_n_escaped(line, '|', i))
			pipe_flag++;
		else if (line[i] != ' ' && line[i] != '\n')
			pipe_flag = 0;
		if (pipe_flag == 2)
			return (line[i]);
		if ((element_err = check_redirections_syntax(&line[i++])) != -1)
			return (element_err);
	}
	if (qute_flag != 0)
		return (qute_flag == 2 ? '"' : '\'');
	return (-1);
}

int handle_syntax(char *line)
{
	char near;

	if ((near = check_syntax(line)) != -1)
	{
		if (near == '\n' || near == 0)
			ft_printf(RED "-bash: syntax error near  unexpected token `newline' \n" RESET);
		else
			ft_printf(RED "-bash: syntax error near  unexpected token `%c' \n" RESET, near);
		add_history(line);
		return (1);
	}
	return (0);
}

int is_nl(char *line, int i)
{
	int n_only;

	n_only = 0;
	if (i > 0)
		n_only = (line[i - 1] == '\\');
	return (line[i] == '\\' && line[i + 1] == 0 && !n_only);
}

int is_complete(char *line)
{
	int i;
	int is_complete;

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
