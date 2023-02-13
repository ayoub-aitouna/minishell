/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:32:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/12 16:14:13 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/readline.h>

char **parse_arguments(char *line, char *cmd, int *i)
{
	char **arguments;

	arguments = NULL;
	arguments = append(arguments, cmd);
	while (line[*i] && ((line[*i] != '|' && line[*i] != '<' && line[*i] != '>')))
		arguments = append(arguments, get_str(&line[*i], i));
	return (arguments);
}

char *get_path(void)
{
	char **env;
	int i;

	i = 0;
	env = get_env(NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char *get_fullpath(char *s)
{
	int i;
	char **paths;
	char *cmd;

	i = 0;
	if (!access(s, X_OK) || ft_strncmp(s, "exit", 4) == 0)
		return (s);
	paths = ft_split(get_path(), ':');
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], ft_strjoin("/", s));
		if (!access(cmd, X_OK))
			return (cmd);
		i++;
	}
	return (NULL);
}

void parse_cur_command(char *line, t_list **list)
{
	int i;
	m_node *node;
	char *full_path;

	i = 0;
	node = new_m_node();
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
	full_path = get_fullpath(node->command);
	if (full_path == NULL)
		ft_printf("%s: command not found \n", node->command);
	node->command = full_path;
	ft_lstadd_back(list, ft_lstnew(node));
	if (line[i] && line[i] == '|')
		parse_cur_command(&line[++i], list);
}

void parse(char *line, t_list **list)
{
	if (line == NULL)
		return;
	parse_cur_command(line, list);
}

int is_complete(char *line)
{
	int i;
	int is_complete;

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

void handle_sigint(int sig)
{
	rl_replace_line("", 0);
	rl_redisplay();
}

void tty(void)
{
	char *line;
	char *msg;
	char cur_dir[64];
	t_list *list;
	char *promt;

	struct sigaction sa;
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	getcwd(cur_dir, 64);
	char *default_promt = ft_strjoin("minishell:\e[1;34m",
									 ft_strjoin(cur_dir,
												"\e[0m>"));
	list = NULL;
	line = NULL;
	while (1)
	{
		line = readline(default_promt);
		ft_printf("\n");
		add_history(line);
		if (check_syntax(line, &msg) == NULL)
		{
			ft_printf("-bash: syntax error near %s\n", msg);
			continue;
		}
		while (!is_complete(line))
			line = ft_strjoin(line, readline(">"));
		parse(line, &list);
		printf_list(list);
		ft_lstiter(list, exec);
		ft_lstclear(&list, free);
		if (line == NULL)
			break;
	}
}
