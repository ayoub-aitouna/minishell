/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:21 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/26 08:01:41 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int find_file_name(char *ptr)
{
	int i;

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

char check_redirections_syntax(char *line)
{
	int i;
	int val;

	i = 0;
	val = -1;
	if (is_n_escaped(line, '>', i))
	{
		if (is_n_escaped(line, '>', i + 1))
			i++;
		if (ft_strchr(">;|<\n", line[i + 1]) || line[i + 1] == 0)
			return (line[i]);
		val = find_file_name(&line[i + 1]);
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
	}
	return (val);
}

char check_syntax(char *line, int *pos)
{
	int pipe_flag;
	char element_err;

	int i, qute_flag;
	i = 0;
	qute_flag = 0;
	pipe_flag = 0;
	i += spaces_count(line);
	if (line[i] == '|' || line[i] == ';')
		return (line[i]);
	while (line[i])
	{
		*pos = i;
		if (toggle_flag(line[i], &qute_flag, &i))
			continue;
		if (!qute_flag && (is_n_escaped(line, '|', i) || is_n_escaped(line, ';', i)))
			pipe_flag++;
		else if (!qute_flag && line[i] != ' ' && line[i] != '\n')
			pipe_flag = 0;
		if (pipe_flag == 2)
			return (line[i]);
		if (!qute_flag && (element_err = check_redirections_syntax(&line[i])) != -1)
			return (element_err);
		i++;
	}
	if (qute_flag != 0)
		return (qute_flag == 2 ? '"' : '\'');
	*pos = -1;
	return (-1);
}

int syntax_here_doc(int flag, char *limiter)
{
	int fd;
	int pid;

	fd = open(".temp_file", O_CREAT | O_RDWR | O_TRUNC, 0664);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, here_doc_signal);
		handle_here_doc(fd, limiter, flag);
	}
	close(fd);
	signal(SIGINT, SIG_IGN);
	free(limiter);
	return (pid);
}

void manage_here_doc(char *line, int pos)
{
	int i;
	int status;
	int canceled;

	canceled = 0;
	if (line == NULL)
		return;
	i = 0;
	while (i < pos)
	{
		if (is_n_escaped(line, '<', i) && is_n_escaped(line, '<', i + 1) && !canceled)
		{
			i += 2;
			int pid = syntax_here_doc(is_between_qute(&line[i]),
									  get_input_value(&line[i], NULL, &i, 2));
			waitpid(pid, &status, 0);
			if (WEXITSTATUS(status) != 0 && WEXITSTATUS(status) == M_SIG_INT)
				canceled = 1;
		}
		else
			i++;
	}
	signal(SIGINT, handle_sigint);
}

int handle_syntax(char *line)
{
	char near;
	int pos;

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
		if (is_n_escaped(line, '|', i) || is_n_escaped(line, '\\', i))
			is_complete = 0;
		else if (line[i] != ' ' && line[i] != '\n')
			is_complete = 1;
		i++;
	}
	return (is_complete);
}
