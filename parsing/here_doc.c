/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:30:17 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/04 05:09:38 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parse_input(char *line, int qute_flag)
{
	char	*new_str;
	int		i;

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

void	handle_here_doc(int fd, char *limiter, int flag)
{
	char	*line;
	char	*parsed_input;

	while (1)
	{
		line = readline("here_doc> ");
		if (line == NULL || is_equal(limiter, line))
			break ;
		parsed_input = parse_input(line, flag);
		parsed_input = ft_str_append(parsed_input, '\n');
		write(fd, parsed_input, ft_strlen(parsed_input));
		free(line);
		free(parsed_input);
	}
	if (line != NULL)
		free(line);
	exit(0);
}

int	here_doc(int flag, char *limiter)
{
	int		fd;
	int		pid;
	int		status;
	char	*random;
	char	*file_name;
	if(is_interrupted())
		return (NO_FILE);
	random = random_string(10);
	file_name = ft_strjoin("tmp/", random);
	free(random);
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0664);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, here_doc_signal);
		handle_here_doc(fd, limiter, flag);
	}
	close(fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if (WEXITSTATUS(status) != 0 && WEXITSTATUS(status) == M_SIG_INT)
	{
		set_interrupted(1);
		return (NO_FILE);
	}
	free(limiter);
	fd = open(file_name, O_RDONLY);
	return (fd);
}
