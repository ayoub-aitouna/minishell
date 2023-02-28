#include "./shell.h"
#include "stdio.h"

int	is_and_or(char *line)
{
	if ((line[0] == '|' && line[1] == '|') && (line[0] == '&'
			&& line[1] == '&'))
		return (2);
	else
		return (0);
}
int	check_for_op(char *line)
{
	int	flag;
	int	i;

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

int	check_brackets_balance(char *line)
{
	int	i;
	int	brackets_flag;

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

int	is_between_brackets(char *line)
{
	int	i;
	int	brackets_flag;

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

char	*remove_outer_brackets(char *ptr)
{
	char	*new_ptr;
	int		i;

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

char	*tr_copy_str(int start, int end, char *ptr)
{
	char	*new_ptr;

	new_ptr = NULL;
	start += spaces_count(ptr + start);
	while (start < end)
		new_ptr = ft_str_append(new_ptr, ptr[start++]);
	return (new_ptr);
}

void	split_by_op(char *ptr, t_tree **tree)
{
	int		i;
	int		brackets_flag;
	int		op;
	char	*lft;

	op = 0;
	i = 0;
	brackets_flag = 0;
	if (!ptr)
		return ;
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
			break ;
		}
		if (ptr[i] == '&' && ptr[i + 1] == '&' && brackets_flag == 0)
		{
			op = 2;
			break ;
		}
		i++;
	}
	*tree = new_tree_node(op, ptr);
	if (op)
	{
		split_by_op(remove_outer_brackets(tr_copy_str(0, i, ptr)),
					&(*tree)->left);
		split_by_op(remove_outer_brackets(tr_copy_str(i + 2, ft_strlen(ptr),
						ptr)),
					&(*tree)->right);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *default_promt;
	get_env(env);
	char *line;
	t_tree *tree;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	line = NULL;
	while (1)
	{
		default_promt = get_promt_text();
		line = readline(default_promt);
		free(default_promt);
		if (exit_if_null(line))
			break ;
		if (handle_syntax(line))
			continue ;
		line = get_full_line(line);
		if (exit_if_null(line))
			break ;
		add_history(line);
		split_by_op(remove_outer_brackets(line), &tree);
		parse_tree(tree);
		tree_iterat(tree, 1);
		free(line);
	}
}
