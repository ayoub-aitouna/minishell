/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:21 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/22 09:22:09 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_file_name(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i] && ptr[i] == ' ')
	{
		i++;
	}
	if (ptr[i] == 0)
		return (0);
	else if (ft_strchr(">;|<\n", ptr[i]))
		return (ptr[i]);
	return (-1);
}

char	check_redirections_syntax(char *line)
{
	int	i;
	int	val;

	i = 0;
	if (is_n_escaped(line, '>', i))
	{
		if (is_n_escaped(line, '>', i + 1))
			i++;
		if (ft_strchr(">;|<\n", line[i + 1]) || line[i + 1] == 0)
			return (line[i]);
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
			return (line[i + 1]);
		val = find_file_name(&line[i + 1]);
		if (val != 1)
			return (val);
	}
	return (-1);
}

char	check_syntax(char *line, int *pos)
{
	int		pipe_flag;
	char	element_err;

	int i, qute_flag;
	i = 0;
	qute_flag = 0;
	pipe_flag = 0;
	i += spaces_count(line);
	if (line[i] == '|')
		return (line[i]);
	while (line[i])
	{
		*pos = i;
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
	*pos = -1;
	return (-1);
}

void	manage_here_doc(char *line, int pos)
{
	int	i;

	if (line == NULL)
		return ;
	i = 0;
	while (i < pos)
	{
		if (is_n_escaped(line, '<', i) && is_n_escaped(line, '<', i + 1))
		{
			i += 2;
			here_doc(is_between_qute(&line[i]),
						get_input_value(&line[i], NULL, &i, 2));
		}
		i++;
	}
}

int	handle_syntax(char *line)
{
	char	near;
	int		pos;

	if ((near = check_syntax(line, &pos)) != -1)
	{
		if (near == '\n' || near == 0)
			ft_printf(RED "-bash: syntax error near  unexpected token `newline' \n" RESET);
		else
			ft_printf(RED "-bash: syntax error near  unexpected token `%c' \n" RESET,
						near);
		add_history(line);
		manage_here_doc(line, pos);
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
		if (is_n_escaped(line, '|', i) || is_n_escaped(line, '\\', i))
			is_complete = 0;
		else if (line[i] != ' ' && line[i] != '\n')
			is_complete = 1;
		i++;
	}
	return (is_complete);
}
