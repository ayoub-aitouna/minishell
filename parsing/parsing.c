#include "../minishell.h"

int	qoute(int i, int mode)
{
	static int	qoute_flag;

	if (mode == 0)
		qoute_flag = i;
	return (qoute_flag);
}

int	here_doc(char *limiter)
{
	char	*line;
	int		fd;

	fd = open(".temp_file", O_CREAT | O_RDWR, 0664);
	while (1)
	{
		ft_printf("here_doc> ");
		line = strip_nl(get_next_line(0));
		if (ft_strlen(limiter) == ft_strlen(line) && !ft_strncmp(line, limiter,
				ft_strlen(line)))
			break ;
		write(fd, line, ft_strlen(line));
	}
	close(fd);
	return (open(".temp_file", O_RDONLY));
}

int	open_input_file(char *line, int *i)
{
	int	input_file;

	if (line[(*i) + 1] == '<')
		return (here_doc(get_str(&line[(*i) += 2], i)));
	else if ((input_file = open(get_str(&line[++(*i)], i), O_RDONLY)) == -1)
	{
		// input file doesn't open
	}
	return (input_file);
}

int	open_output_file(char *line, int *i)
{
	int	opne_flag;
	int	output_file;

	opne_flag = 0;
	if (line[(*i) + 1] == '>')
	{
		opne_flag = O_CREAT | O_RDWR | O_APPEND;
		(*i)++;
	}
	else
		opne_flag = O_CREAT | O_RDWR | O_TRUNC;
	if ((output_file = open(get_str(&line[++(*i)], i), opne_flag, 0664)) ==
		-1)
	{
		// input file doesn't open
	}
	return (output_file);
}

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

char	*get_path(void)
{
	char	**env;
	int		i;

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

char	*get_fullpath(char *s)
{
	int		i;
	char	**paths;
	char	*cmd;

	i = 0;
	if (!access(s, X_OK))
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

void	parse_cur_command(char *line, t_list **list)
{
	int		i;
	m_node	*node;
	char	*full_path;

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
		ft_printf("%s: command not found", node->command);
	node->command = full_path;
	ft_lstadd_back(list, ft_lstnew(node));
	if (line[i] && line[i] == '|')
		parse_cur_command(&line[++i], list);
}

void	parse(char *line, t_list **list)
{
	parse_cur_command(line, list);
}

size_t	string_list_len(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

void	append_qoute(m_node *node, char *line)
{
	int	len;

	len = string_list_len(node->arguments) - 1;
	node->arguments[len] = ft_strjoin(node->arguments[len], line);
	if ((ft_strchr(line, '\'') && qoute(0, -1) == 1) || (ft_strchr(line, '"')
				&& qoute(0, -1) == 2))
		qoute(0, 0);
}

void	tty(void)
{
	char	*line;
	char	cur_dir[64];
	t_list	*list;
	char	*promt;

	getcwd(cur_dir, 64);
	char *default_promt = ft_strjoin("minishell:\e[1;34m",
										ft_strjoin(cur_dir,
												"\e[0m>"));
	list = NULL;
	while (1)
	{
		getcwd(cur_dir, 64);
		if (qoute(0, -1) == 1)
			promt = "qoute>";
		else if (qoute(0, -1) == 2)
			promt = "dqoute>";
		else
			promt = default_promt;
		line = readline(promt);
		if (qoute(0, -1) == 1 || qoute(0, -1) == 2)
			append_qoute((m_node *)(ft_lstlast(list)->content), line);
		else
			parse(strip_nl(line), &list);
		if (qoute(0, -1) == 0)
		{
			printf_list(list);
			ft_lstclear(&list, free);
		}
		if (line == NULL)
			break ;
	}
}
