#include "minishell.h"

m_node	*new_m_node()
{
	m_node *new_node = malloc(sizeof(m_node));
	if (!new_node)
		return (NULL);
	new_node->input_file = -1;
	new_node->commend = NULL;
	new_node->arguments = NULL;
	new_node->output_file = -1;
	return (new_node);
}

void	printf_arg(char **str)
{
	int i = 0;
	ft_printf("arguments  		");
	if (str == NULL)
	{
		ft_printf("(null)\n");
		return ;
	}
	while (str[i])
		printf("%s ,", str[i++]);
	printf("\n");
}

void	print_table(m_node *node)
{
	ft_printf("input file 		%d \n", node->input_file);
	ft_printf("commend    		%s \n", node->commend);
	printf_arg(node->arguments);
	ft_printf("output_file file 	%d \n", node->output_file);
}

void	printf_list(t_list *list)
{
	int i;

	i = 0;
	if (list == NULL)
		return ;
	while (list)
	{
		m_node *node = (m_node *)list->content;
		if (!node)
		{
			printf("node null");
			return ;
		}
		printf("\n---------------\tnode_%d\t--------------\n", i);
		print_table(node);
		printf("\n--------------------------------------\n");
		i++;
		list = list->next;
	}
}

char	*get_str(char *s, int *index)
{
	int len = 0;
	int i = 0;
	while (s[i] && s[i] == ' ')
	{
		i++;
	}
	while (s[i] != 0 && s[i] != '|' && s[i] != '>' && s[i] != '<'
		&& s[i] != ' ')
	{
		i++;
		len++;
	}
	while (s[i] && s[i] == ' ')
	{
		i++;
	}
	char *new_str = malloc(len + 1);
	*index = *index + i;
	i = 0;
	while (i < len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

size_t	size(char **ptr)
{
	size_t i = 0;
	while (ptr[i++])
		;
	return (i);
}

void	parse_cur_commend(char *line, t_list **list)
{
	int i;
	m_node *node;
	char *arguments;
	int input_file;
	int output_file;

	i = 0;
	arguments = NULL;
	node = new_m_node();
	while (line[i] && line[i] != '|')
	{
		ft_printf("loop %d \n", i);
		if (line[i] == '<')
		{
			char *s = get_str(&line[++i], &i);
			ft_printf("file name  <%s> \n", s);
			if ((input_file = open(s, O_RDONLY)) == -1)
			{
				// input file doesn't open
			}
			node->input_file = input_file;
		}
		else if (line[i] == '>')
		{
			if ((output_file = open(get_str(&line[++i], &i),
									O_CREAT | O_RDWR)) ==
				-1)
			{
				// input file doesn't open
			}
			node->output_file = output_file;
		}
		else
		{
			if (!node->commend)
				node->commend = get_str(&line[i], &i);
			while (line[i] && line[i] != '|' && line[i] != '<'
				&& line[i] != '>')
			{
				ft_printf("inner loop %d <%c> \n", i, line[i]);
				if (arguments == NULL)
					arguments = get_str(&line[i], &i);
				else
					arguments = ft_strjoin(arguments, ft_strjoin(" ",
								get_str(&line[i], &i)));
			}
			node->arguments = ft_split(arguments, ' ');
		}
	}
	ft_lstadd_back(list, ft_lstnew(node));
	if (line[i] && line[i] == '|')
		parse_cur_commend(&line[++i], list);
}

t_list	*parse(char *line)
{
	int i = 0;
	t_list *list = NULL;
	parse_cur_commend(line, &list);
	printf_list(list);
}

char	*strip_nl(char *line)
{
	int i = 0;
	while (line[i] != 0 && line[i] != '\n')
	{
		i++;
	}
	if (line[i] == '\n')
		line[i] = 0;
	return (line);
}

void	tty(void)
{
	char *line;
	char cur_dir[64];
	while (1)
	{
		getcwd(cur_dir, 64);
		ft_printf("minishell:\e[1;34m%s\e[0m>", cur_dir);
		line = strip_nl(get_next_line(0));
		parse(line);
		if (line == NULL)
			break ;
	}
}

int	main(void)
{
	tty();
}