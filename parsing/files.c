/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:34:35 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/24 09:00:17 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (file_name == NULL)
	{
		input_file = ERROR;
		printf(RED "ambiguous redirect \n" RESET);
	}
	else if (output != ERROR && output != NO_FILE)
	{
		if ((input_file = open(file_name, open_flag, 0664)) == -1)
			perror("-bash :");
	}
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
	if (file_name == NULL)
	{
		output_file = ERROR;
		printf(RED "ambiguous redirect\n" RESET);
	}
	else if (input != ERROR && input != NO_FILE)
	{
		if ((output_file = open(file_name, opne_flag, 0664)) == -1)
			perror("-bash :");
	}
	if (file_name != NULL)
		free(file_name);
	return (output_file);
}
