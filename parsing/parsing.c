/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/13 15:27:42 by aaitouna         ###   ########.fr       */
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
			node->arguments = parse_arguments(line, node->command, &i);
		}
	}
	update_command(node);
	ft_lstadd_back(list, ft_lstnew(node));
	if (line[i] && line[i] == '|')
		parse(&line[++i], list);
}

int	is_complete(char *line)
{
	int	i;
	int	is_complete;

	i = 0;
	is_complete = 1;
	while (line[i])
	{
		if (line[i] == '|' || (line[i] == '\\' && line[i + 1] == 0))
			is_complete = 0;
		else if (line[i] != ' ' && line[i] != '\n')
			is_complete = 1;
		i++;
	}
	return (is_complete);
}

void	tty(void)
{
	char	*line;
	char	*msg;
	char	cur_dir[64];
	t_list	*list;
	char	*promt;
	char	*default_promt;
	char	*dir;
	char	*temp;

	getcwd(cur_dir, 64);
	dir = ft_strjoin(cur_dir, "$ " RESET);
	default_promt = ft_strjoin(BOLDGREEN "minishell:\e" RESET BOLDBLUE, dir);
	free(dir);
	list = NULL;
	line = NULL;
	while (1)
	{
		line = readline(default_promt);
		if (check_syntax(line, &msg) == NULL)
		{
			ft_printf(RED "-bash: syntax error near  unexpected "
							"token %s\n" RESET,
						msg);
			add_history(line);
			continue ;
		}
		while (!is_complete(line))
		{
			temp = ft_strjoin(line, readline(">"));
			free(line);
			line = temp;
		}
		add_history(line);
		parse(line, &list);
		// printf_list(list);
		ft_lstiter(list, exec);
		ft_lstclear(&list, clear_node);
		if (line != NULL)
			free(line);
		else
			break ;
	}
}
