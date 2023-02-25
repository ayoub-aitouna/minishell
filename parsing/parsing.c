/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/25 11:04:42 by aaitouna         ###   ########.fr       */
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
	m_node *node;

	if (line == NULL)
		return;
	node = new_m_node();
	i = 0;
	while (line[i] && line[i] != '|')
	{
		if (is_n_escaped(line, '<', i))
			node->input_file = open_input_file(line, &i, node->output_file);
		else if (is_n_escaped(line, '>', i))
			node->output_file = open_output_file(line, &i, node->input_file);
		else
			get_input_value(&line[i], node, &i, 0);
	}
	node->command = update_command(node->command);
	ft_lstadd_back(list, ft_lstnew(node));
	if (line[i] && line[i] == '|')
		parse(&line[++i], list);
}

char *get_relative_path(char *HOME, char *w_directory)
{
	int i;
	char *relative_dir;
	char *temp;

	relative_dir = NULL;
	i = 0;
	while (w_directory[i] && HOME[i] && w_directory[i] == HOME[i])
		i++;
	relative_dir = ft_str_append(relative_dir, ':');
	relative_dir = ft_str_append(relative_dir, '~');
	while (w_directory[i])
		relative_dir = ft_str_append(relative_dir, w_directory[i++]);
	relative_dir = m_safe_strjoin(relative_dir, RESET, 1);
	relative_dir = ft_str_append(relative_dir, '$');
	relative_dir = ft_str_append(relative_dir, ' ');
	return (relative_dir);
}

char *get_promt_text(void)
{
	char *working_directory;
	char *dir;
	char *default_promt;
	char *HOME;
	char *USER;

	working_directory = getcwd(NULL, 0);
	HOME = getenv("HOME");
	USER = getenv("USER");
	dir = get_relative_path(HOME, working_directory);
	default_promt = m_safe_strjoin(USER, "@", 0);
	default_promt = m_safe_strjoin(default_promt, "minishell", 1);
	default_promt = m_safe_strjoin(BOLDMAGENTA, default_promt, 2);
	default_promt = m_safe_strjoin(default_promt, RESET, 1);
	default_promt = m_safe_strjoin(default_promt, BOLDBLUE, 1);
	default_promt = m_safe_strjoin(default_promt, dir, 3);
	free(working_directory);
	return (default_promt);
}

void replace_b_slash(char *ptr)
{
	int i;

	i = ft_strlen(ptr);
	while (i >= 0 && ptr[i] != '\\' && ptr[i] != '|')
		i--;
	if (is_n_escaped(ptr, '\\', i))
		ptr[i] = 0;
}

char *get_full_line(char *line)
{
	char *temp;
	char *new_line;

	while (!is_complete(line))
	{
		replace_b_slash(line);
		new_line = readline(">");
		if (!new_line)
		{
			return (NULL);
		}
		temp = ft_strjoin(line, new_line);
		free(line);
		free(new_line);
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
		{
			printf("exit\n");
			break;
		}
		if (handle_syntax(line))
			continue;
		line = get_full_line(line);
		if (!line)
		{
			printf("exit\n");
			break;
		}
		add_history(line);
		parse(line, &list);
		// printf_list(list);
		exec(list);
		ft_lstclear(&list, clear_node);
		free(line);
		// exit(0);
	}
}
