/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:34:35 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/12 14:37:26 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_input_file(char *line, int *i)
{
	int	input_file;

	if (line[(*i) + 1] == '<')
		return (here_doc(get_str(&line[(*i) += 2], i)));
	else if ((input_file = open(get_str(&line[++(*i)], i), O_RDONLY)) == -1)
	{
		// input file doesn't open
	}
	return (input_file);
}

int	open_output_file(char *line, int *i)
{
	int	opne_flag;
	int	output_file;

	opne_flag = 0;
	if (line[(*i) + 1] == '>')
	{
		opne_flag = O_CREAT | O_RDWR | O_APPEND;
		(*i)++;
	}
	else
		opne_flag = O_CREAT | O_RDWR | O_TRUNC;
	if ((output_file = open(get_str(&line[++(*i)], i), opne_flag, 0664)) ==
		-1)
	{
		// input file doesn't open
	}
	return (output_file);
}
