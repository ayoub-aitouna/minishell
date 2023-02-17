/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/17 16:16:25 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**parse_arguments(char *line, char *cmd, int *i)
{
	char	**arguments;

	arguments = NULL;
	arguments = append(arguments, cmd);
	while (line[*i] && ((line[*i] != '|' && line[*i] != '<'
				&& line[*i] != '>')))
		arguments = append(arguments, get_str(&line[*i], i, 1));
	return (arguments);
}

void	parse(char *line, t_list **list)
{
	int		i;
	m_node	*node;

	if (line == NULL)
		return ;
	node = new_m_node();
	i = 0;
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '<')
			node->input_file = open_input_file(line, &i);
		else if (line[i] == '>')
			node->output_file = open_output_file(line, &i);
		else
		{
			if (!node->command)
				node->command = get_str(&line[i], &i, 1);
			node->arguments = parse_arguments(line, ft_strdup(node->command),
					&i);
		}
	}
	node->command = update_command(node->command);
	ft_lstadd_back(list, ft_lstnew(node));
	if (line[i] && line[i] == '|')
		parse(&line[++i], list);
}

char	*get_promt_text()
{
	char	*working_directory;
	char	*dir;
	char	*default_promt;

	working_directory = getcwd(NULL, 0);
	dir = ft_strjoin(working_directory, "$ " RESET);
	default_promt = ft_strjoin(BOLDGREEN "minishell:\e" RESET BOLDBLUE,
								dir);
	free(dir);
	free(working_directory);
	return (default_promt);
}

char	*get_full_line(char *line)
{
	char	*temp;

	while (!is_complete(line))
	{
		temp = ft_strjoin(line, readline(">"));
		free(line);
		line = temp;
	}
	return (line);
}

void	tty(void)
{
	char	*line;
	t_list	*list;
	char	*default_promt;

	list = NULL;
	line = NULL;
	while (1)
	{
		default_promt = get_promt_text();
		line = readline(default_promt);
		free(default_promt);
		if (!line)
			break ;
		if (handle_syntax(line))
			continue ;
		line = get_full_line(line);
		add_history(line);
		parse(line, &list);
		printf_list(list);
		ft_lstclear(&list, clear_node);
		free(line);
	}
}
