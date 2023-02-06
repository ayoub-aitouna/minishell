#include "minishell.h"

m_node *new_m_node(char *str, TOKEN token)
{
	if (!str)
		return (NULL);
	m_node *new_node = malloc(sizeof(m_node));
	if (!new_node)
		return (NULL);
	new_node->content = str;
	new_node->token = token;
	return (new_node);
}

void printf_list(t_list *list)
{
	if (list == NULL)
		return;
	while (list)
	{
		m_node *node = (m_node *)list->content;
		if (!node)
		{
			printf("node null");
			return;
		}
		printf("cmd %s, token %d \n",node->content, node->token);
		list = list->next;
	}
}

void parse(char *line)
{
	int i = 0;
	t_list *list = NULL;
	char **line_parts = ft_split(line, ' ');
	if (line_parts == NULL)
		return;
	while (line_parts[i])
	{
		ft_lstadd_back(&list, ft_lstnew(new_m_node(line_parts[i], CMD)));
		i++;
	}
	printf_list(list);
}

void tty()
{
	char *line;
	while (1)
	{
		ft_printf("minishell> ");
		line = get_next_line(0);
		parse(line);
		if (line == NULL)
			break;
	}
}

int main()
{
	tty();
}#include "minishell.h"

m_node *new_m_node(char *str, TOKEN token)
{
	if (!str)
		return (NULL);
	m_node *new_node = malloc(sizeof(m_node));
	if (!new_node)
		return (NULL);
	new_node->content = str;
	new_node->token = token;
	return (new_node);
}

void printf_list(t_list *list)
{
	if (list == NULL)
		return;
	while (list)
	{
		m_node *node = (m_node *)list->content;
		if (!node)
		{
			printf("node null");
			return;
		}
		printf("cmd %s, token %d \n",node->content, node->token);
		list = list->next;
	}
}

void parse(char *line)
{
	int i = 0;
	t_list *list = NULL;
	char **line_parts = ft_split(line, ' ');
	if (line_parts == NULL)
		return;
	while (line_parts[i])
	{
		ft_lstadd_back(&list, ft_lstnew(new_m_node(line_parts[i], CMD)));
		i++;
	}
	printf_list(list);
}

void tty()
{
	char *line;
	while (1)
	{
		ft_printf("minishell> ");
		line = get_next_line(0);
		parse(line);
		if (line == NULL)
			break;
	}
}

int main()
{
	tty();
}