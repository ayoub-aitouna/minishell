/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:34:35 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/04 05:09:38 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_between_qute(char *line)
{
	int	i;
	int	qute_flag;
	int	flag;

	qute_flag = 0;
	flag = 0;
	i = 0;
	while (line[i] != 0 && (is_token_sep(line, i) || qute_flag))
	{
		flag = qute_flag;
		toggle_quteflag(line[i], &qute_flag);
		i++;
	}
	return (flag);
}

int	open_file(char *file_name, int open_flag, int input)
{
	int	fd;

	fd = NONE;
	if (file_name == NULL)
	{
		fd = ERROR;
		printf(RED "ambiguous redirect\n" RESET);
	}
	else if (input != ERROR && input != NO_FILE)
	{
		fd = open(file_name, open_flag, 0664);
		if (fd == -1)
			perror("-bash :");
	}
	return (fd);
}

int	open_input_file(char *line, int *i, int output)
{
	int		input_file;
	char	*file_name;
	int		open_flag;

	input_file = NONE;
	if (line[(*i) + 1] == '<')
	{
		(*i) += 2;
		return (here_doc(is_between_qute(&line[*i]), get_input_value(&line[*i],
					NULL, i, 2)));
	}
	else if (line[(*i) + 1] == '>')
	{
		++(*i);
		open_flag = O_CREAT | O_RDWR | O_TRUNC;
	}
	open_flag = O_RDONLY;
	file_name = get_input_value(&line[++(*i)], NULL, i, 1);
	input_file = open_file(file_name, open_flag, output);
	if (file_name != NULL)
		free(file_name);
	return (input_file);
}

int	open_output_file(char *line, int *i, int input)
{
	int		opne_flag;
	int		output_file;
	char	*file_name;

	opne_flag = 0;
	output_file = NONE;
	if (line[(*i) + 1] == '>')
	{
		(*i)++;
		opne_flag = O_CREAT | O_RDWR | O_APPEND;
	}
	else
		opne_flag = O_CREAT | O_RDWR | O_TRUNC;
	file_name = get_input_value(&line[++(*i)], NULL, i, 1);
	output_file = open_file(file_name, opne_flag, input);
	if (file_name != NULL)
		free(file_name);
	return (output_file);
}
