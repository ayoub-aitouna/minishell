/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/20 19:39:53 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *splite_env_val(char *line, char *new_str, m_node *node, int *index)
{
	int j;
	char *env_value;
	char **splited_env_val;
	int max;

	env_value = NULL;
	j = 0;
	env_value = copy_variable_value(env_value, line, index);
	if (env_value != NULL)
	{
		splited_env_val = ft_split(env_value, ' ');
		max = size(splited_env_val);
		while (j < max - 1)
		{
			add_arg_t_node(node, mini_strjoin(new_str,
											  ft_strdup(splited_env_val[j])));
			free(new_str);
			new_str = NULL;
			free(splited_env_val[j]);
			j++;
		}
		new_str = mini_strjoin(new_str, ft_strdup(splited_env_val[j]));
		free(splited_env_val);
	}
	return (new_str);
}

void parse(char *line, t_list **list)
{
	int i;
	int k;
	m_node *node;

	k = 0;
	if (line == NULL)
		return;
	node = new_m_node();
	i = 0;
	while (line[i] && line[i] != '|')
	{
		if (is_n_escaped(line, '<', i))
			node->input_file = open_input_file(line, &i);
		else if (is_n_escaped(line, '>', i))
			node->output_file = open_output_file(line, &i);
		else
			parse_arguments(&line[i], node, &i);
	}
	node->command = update_command(node->command);
	ft_lstadd_back(list, ft_lstnew(node));
	if (line[i] && line[i] == '|')
		parse(&line[++i], list);
}

char *get_promt_text(void)
{
	char *working_directory;
	char *dir;
	char *default_promt;

	working_directory = getcwd(NULL, 0);
	dir = ft_strjoin(working_directory, "$ " RESET);
	default_promt = ft_strjoin(BOLDGREEN "minishell:\e" RESET BOLDBLUE, dir);
	free(dir);
	free(working_directory);
	return (default_promt);
}

char *get_full_line(char *line)
{
	char *temp;

	while (!is_complete(line))
	{
		temp = ft_strjoin(line, readline(">"));
		free(line);
		line = temp;
	}
	return (line);
}

void tty(void)
{
	char *line;
	t_list *list;
	char *default_promt;

	list = NULL;
	line = NULL;
	while (1)
	{
		default_promt = get_promt_text();
		line = readline(default_promt);
		free(default_promt);
		if (!line)
			break;
		// if (handle_syntax(line))
		// 	continue ;
		// line = get_full_line(line);
		add_history(line);
		parse(line, &list);
		// exec(list);
		printf_list(list);
		ft_lstclear(&list, clear_node);
		free(line);
	}
}
