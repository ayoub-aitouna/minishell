/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/14 17:13:43 by aaitouna         ###   ########.fr       */
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
		arguments = append(arguments, get_str(&line[*i], i));
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
				node->command = get_str(&line[i], &i);
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
	char	cur_dir[64];
	char	*dir;
	char	*default_promt;

	getcwd(cur_dir, 64);
	dir = ft_strjoin(cur_dir, "$ " RESET);
	default_promt = ft_strjoin(BOLDGREEN "minishell:\e" RESET BOLDBLUE, dir);
	free(dir);
	return (default_promt);
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
		if (line[i] == '|' || is_nl(line, i))
			is_complete = 0;
		else if (line[i] != ' ' && line[i] != '\n')
			is_complete = 1;
		i++;
	}
	return (is_complete);
}

char	*clean_line(char *line)
{
	// int		i;
	// int		qute_flag;
	// char	*new_str;
	// i = 0;
	// qute_flag = 0;
	// new_str = NULL;
	// while (line[i] != 0)
	// {
	// 	toggle_quteflag_n_increment(line[i], &qute_flag, &i);
	// 	if (qute_flag != 0 && !is_nl(line, i))
	// 	{
	// 	}
	// 	i++;
	// }
	return (line);
}

void	tty(void)
{
	char	*line;
	t_list	*list;
	char	*temp;
	char	*default_promt;

	list = NULL;
	line = NULL;
	while (1)
	{
		default_promt = get_promt_text();
		line = readline(default_promt);
		if (!line)
			break ;
		free(default_promt);
		handle_syntax(line);
		if (handle_syntax(line))
			continue ;
		while (!is_complete(line))
		{
			temp = ft_strjoin(line, readline(">"));
			free(line);
			line = temp;
		}
		line = clean_line(line);
		add_history(line);
		parse(line, &list);
		exec(list);
		// ft_lstiter(list, exec);
		ft_lstclear(&list, clear_node);
		if (line != NULL)
			free(line);
		else
			break ;
	}
}
