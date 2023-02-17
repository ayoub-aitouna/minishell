/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:34:35 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/17 18:36:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_between_qute(char *line)
{
	int	i;

	int qute_flag, flag;
	qute_flag = 0;
	flag = 0;
	i = 0;
	while (line[i] != 0 && ((line[i] != '|' && line[i] != '>' && line[i] != '<'
				&& line[i] != ' ') || qute_flag))
	{
		flag = qute_flag;
		toggle_quteflag(line[i], &qute_flag);
		i++;
	}
	return (flag);
}

int	open_input_file(char *line, int *i)
{
	int		input_file;
	char	*fine_name;
	int		qute_flag;

	if (line[(*i) + 1] == '<')
	{
		qute_flag = is_between_qute(&line[(*i) + 2]);
		printf(">> : <%d> \n", qute_flag);
		return (here_doc(qute_flag, get_str(&line[(*i) + 2], i, 0)));
	}
	else
	{
		fine_name = get_str(&line[++(*i)], i, 1);
		input_file = open(fine_name, O_RDONLY);
		if (input_file == -1)
		{
		}
		if (fine_name != NULL)
			free(fine_name);
	}
	return (input_file);
}

int	open_output_file(char *line, int *i)
{
	int		opne_flag;
	int		output_file;
	char	*name;

	opne_flag = 0;
	if (line[(*i) + 1] == '>')
	{
		(*i)++;
		opne_flag = O_CREAT | O_RDWR | O_APPEND;
	}
	else
		opne_flag = O_CREAT | O_RDWR | O_TRUNC;
	name = get_str(&line[++(*i)], i, 1);
	output_file = open(name, opne_flag, 0664);
	if (output_file == -1)
	{
	}
	if (name != NULL)
		free(name);
	return (output_file);
}
