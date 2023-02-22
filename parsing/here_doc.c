/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:30:17 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/17 19:01:07 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *parse_input(char *line, int qute_flag)
{
	char *new_str;
	int i;

	i = 0;
	new_str = NULL;
	while (line[i] != 0)
	{
		if (qute_flag == 0 && line[i] == '$')
		{
			new_str = copy_variable_value(new_str, line, &i);
			i++;
		}
		new_str = ft_str_append(new_str, line[i]);
		i++;
	}
	return (new_str);
}

int here_doc(int flag, char *limiter)
{
	char *line;
	char *parsed_input;
	int fd;

	printf("limiter %s \n", limiter);
	fd = open(".temp_file", O_CREAT | O_RDWR, 0664);
	while (1)
	{
		line = readline("here_doc> ");
		if (line == NULL || is_equal(limiter, line))
			break;
		parsed_input = parse_input(line, flag);
		printf("\n%s\n", parsed_input);
		write(fd, parsed_input, ft_strlen(parsed_input));
		free(line);
		free(parsed_input);
	}
	if (line != NULL)
		free(line);
	close(fd);
	free(limiter);
	return (open(".temp_file", O_RDONLY));
}
