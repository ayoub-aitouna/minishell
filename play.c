#include "./tree.h"
#include "stdio.h"

int is_and_or(char *line)
{
	if ((line[0] == '|' && line[1] == '|') && (line[0] == '&' && line[1] == '&'))
		return (2);
	else
		return (0);
}
int check_for_op(char *line)
{
	int flag;
	int i;

	i = 0;
	flag = 0;
	if (line[i] == 0)
		return (0);
	if (is_and_or(line) != 0)
		return (2);
	if (ft_strchr(">;<|", line[i]))
		return (1);
	return (0);
}

int check_brackets_balance(char *line)
{
	int i;
	int brackets_flag;

	i = 0;
	brackets_flag = 0;
	while (line[i])
	{
		if (brackets_flag < 0)
			return (0);
		if (line[i] == '(')
			brackets_flag++;
		if (line[i] == ')')
			brackets_flag--;
		i++;
	}
	return (brackets_flag == 0);
}
int spaces_count(char *s)
{
	int i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	return (i);
}
int is_between_brackets(char *line)
{
	int i;
	int brackets_flag;

	i = 0;
	brackets_flag = 0;
	if (!check_brackets_balance(line))
		return (0);
	while (line[i])
	{
		if (line[i] == '(')
			brackets_flag++;
		else if (line[i] == ')')
			brackets_flag--;
		if (brackets_flag == 0)
		{
			i++;
			return (!line[i + spaces_count(line + i)]);
		}
		i++;
	}
	return (1);
}

char *ft_str_append(char *s, char c)
{
	int i;
	int len;
	char *new_str;

	i = 0;
	len = ft_strlen(s);
	new_str = malloc((len + 3) * sizeof(char));
	while (i < len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = 0;
	if (s != NULL)
		free(s);
	return (new_str);
}

char *remove_outer_brackets(char *ptr)
{
	char *new_ptr;
	int i;

	new_ptr = NULL;

	if (!is_between_brackets(ptr))
		return (ptr);
	i = 1;
	new_ptr = ft_strtrim(ptr, " ");
	free(ptr);
	ptr = new_ptr;
	new_ptr = NULL;
	while (ptr[i + 1])
		new_ptr = ft_str_append(new_ptr, ptr[i++]);
	free(ptr);
	if (is_between_brackets(new_ptr))
		return (remove_outer_brackets(new_ptr));
	return (new_ptr);
}

char *copy_str(int start, int end, char *ptr)
{
	char *new_ptr;

	new_ptr = NULL;
	start += spaces_count(ptr + start);
	while (start < end)
		new_ptr = ft_str_append(new_ptr, ptr[start++]);
	return (new_ptr);
}

void split_by_op(char *ptr, t_tree **tree)
{
	int i;
	int brackets_flag;
	int op;

	op = 0;
	i = 0;
	brackets_flag = 0;
	if (!ptr)
		return;
	while (ptr[i])
	{
		op = 0;
		if (ptr[i] == '(')
			brackets_flag++;
		else if (ptr[i] == ')')
			brackets_flag--;
		if (ptr[i] == '|' && ptr[i + 1] == '|' && brackets_flag == 0)
		{
			op = 1;
			break;
		}
		if (ptr[i] == '&' && ptr[i + 1] == '&' && brackets_flag == 0)
		{
			op = 2;
			break;
		}
		i++;
	}
	*tree = new_tree_node(op, ptr);
	if (op)
	{
		char *lft = copy_str(0, i, ptr);
		split_by_op(remove_outer_brackets(copy_str(0, i, ptr)),
					&(*tree)->left);
		split_by_op(remove_outer_brackets(copy_str(i + 2, ft_strlen(ptr), ptr)),
					&(*tree)->right);
	}
}

int exit_if_null(char *line)
{
	if (!line)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

int main(int ac, char **av)
{
	char *line;
	t_tree *tree;

	line = NULL;
	while (1)
	{
		tree = NULL;
		line = readline("test > ");
		if (exit_if_null(line))
			break;
		add_history(line);
		split_by_op(remove_outer_brackets(line), &tree);
		tree_iterat(tree, 1);
		free(line);
	}
}