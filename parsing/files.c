/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:34:35 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/13 16:49:02 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_input_file(char *line, int *i)
{
	int		input_file;
	char	*name;

	if (line[(*i) + 1] == '<')
	{
		name = get_str(&line[(*i) += 2], i);
		return (here_doc(name));
	}
	else
	{
		name = get_str(&line[++(*i)], i);
		input_file = open(name, O_RDONLY);
		if (input_file == -1)
		{
		}
		if (name != NULL)
			free(name);
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
	name = get_str(&line[++(*i)], i);
	output_file = open(name, opne_flag, 0664);
	if (output_file == -1)
	{
	}
	if (name != NULL)
		free(name);
	return (output_file);
}
