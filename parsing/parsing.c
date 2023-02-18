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

char **parse_arguments(char *line, char *cmd, int *i)
{
	char **arguments;

	arguments = NULL;
	arguments = append(arguments, cmd);
	while (line[*i] && ((line[*i] != '|' && line[*i] != '<' && line[*i] != '>')))
		arguments = append(arguments, get_str(&line[*i], i, 1));
	return (arguments);
}

void splite_env_val(char *line, m_node *node, int *index)
{
	int j;
	int k;
	char *env_value = NULL;
	char **splited_env_val;

	j = 0;
	k = 0;
	env_value = copy_variable_value(env_value, line, &k);
	if (env_value != NULL)
	{
		(*index)++;
		splited_env_val = ft_split(env_value, ' ');
		while (splited_env_val[j])
		{
			if (!node->command)
				node->command = ft_strdup(splited_env_val[j]);
			node->arguments = append(node->arguments, ft_strdup(splited_env_val[j]));
			free(splited_env_val[j]);
			j++;
		}
		free(splited_env_val);
		(*index) += k;
	}
}

void get_cmd_n_args(char *line, m_node *node, int *i)
{
	(*i) += spaces_count(&line[*i]);
	if (line[*i] == '$')
		splite_env_val(line, node, i);
	else
	{
		if (!node->command)
			node->command = get_str(&line[*i], i, 1);
		node->arguments = parse_arguments(line, ft_strdup(node->command),
										  i);
	}
}

void parse(char *line, t_list **list)
{
	int i;
	int k = 0;
	m_node *node;

	if (line == NULL)
		return;
	node = new_m_node();
	i = 0;
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '<')
			node->input_file = open_input_file(line, &i);
		else if (line[i] == '>')
			node->output_file = open_output_file(line, &i);
		else
			get_cmd_n_args(line, node, &i);
	}
	node->command = update_command(node->command);
	ft_lstadd_back(list, ft_lstnew(node));
	if (line[i] && line[i] == '|')
		parse(&line[++i], list);
}

char *get_promt_text()
{
	char *working_directory;
	char *dir;
	char *default_promt;

	working_directory = getcwd(NULL, 0);
	dir = ft_strjoin(working_directory, "$ " RESET);
	default_promt = ft_strjoin(BOLDGREEN "minishell:\e" RESET BOLDBLUE,
							   dir);
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

char *wrap(char *s, char c)
{
	int i = 0;
	char *new_str = NULL;
	new_str = ft_str_append(new_str, c);
	while (s[i])
		new_str = ft_str_append(new_str, s[i++]);
	new_str = ft_str_append(new_str, c);
	// free(s);
	return (new_str);
}

char *replace_env_values(char *line)
{
	int i = 0;
	int k = 0;
	int flag = 0;
	char *new_line = NULL;
	char *env_value = NULL;
	char **splited_env_val;
	while (line[i])
	{
		toggle_quteflag(line[i], &flag);
		if (!flag && line[i] == '$')
		{
			int j = 0;
			env_value = copy_variable_value(env_value, line, &k);
			if (env_value != NULL)
			{
				splited_env_val = ft_split(env_value, ' ');

				while (splited_env_val[j])
				{
					char *wraped = wrap(splited_env_val[j], '"');
					new_line = mini_strjoin(new_line, wrap(splited_env_val[j++], '"'));
				}
				i += k;
			}
		}
		new_line = ft_str_append(new_line, line[i]);
		i++;
	}
	return (new_line);
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
		if (handle_syntax(line))
			continue;
		line = get_full_line(line);
		add_history(line);
		parse(line, &list);
		// exec(list);
		printf_list(list);
		ft_lstclear(&list, clear_node);
		free(line);
	}
}
