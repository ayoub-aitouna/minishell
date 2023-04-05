#include "./shell.h"
#include "stdio.h"

int	update_brackets_flag(char c)
{
	if (c == '(')
		return (1);
	else if (c == ')')
		return (-1);
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
	if (line == NULL)
		return (0);
	if (!check_brackets_balance(line))
		return (0);
	while (line[i])
	{
		brackets_flag += update_brackets_flag(line[i]);
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
	if (!is_between_brackets(ptr) || ptr == NULL)
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

char	*get_part_of_string(int start, int end, char *ptr)
{
	char	*new_ptr;

	new_ptr = NULL;
	start += spaces_count(ptr + start);
	while (start < end)
		new_ptr = ft_str_append(new_ptr, ptr[start++]);
	return (new_ptr);
}

int	get_operatur(char *ptr, int *index)
{
	int	brackets_flag;
	int	i;

	i = 0;
	brackets_flag = 0;
	while (ptr[i])
	{
		brackets_flag += update_brackets_flag(ptr[i]);
		*index = i;
		if (ptr[i] == '&' && ptr[i + 1] == '&' && brackets_flag == 0)
			return (3);
		if (ptr[i] == '|' && ptr[i + 1] == '|' && brackets_flag == 0)
			return (2);
		if (ptr[i] == '|' && brackets_flag == 0)
			return (1);
		i++;
	}
	return (0);
}

void	split_by_nd_n_or(char *ptr, t_tree **tree)
{
	int	i;
	int	op;

	if (!ptr)
		return ;
	op = get_operatur(ptr, &i);
	*tree = new_tree_node(op, ptr);
	if (op == 2 || op == 3)
	{
		split_by_nd_n_or(remove_outer_brackets(get_part_of_string(0, i, ptr)),
							&(*tree)->left);
		split_by_nd_n_or(remove_outer_brackets(get_part_of_string(i + 2,
																	ft_strlen(ptr),
																	ptr)),
							&(*tree)->right);
	}
	else
		split_by_pip(ptr, tree);
}

void	split_by_pip(char *ptr, t_tree **tree)
{
	int	i;
	int	op;

	if (!ptr)
		return ;
	op = get_operatur(ptr, &i);
	if (op)
	{
		*tree = new_tree_node(op, ptr);
		split_by_nd_n_or(remove_outer_brackets(get_part_of_string(0, i, ptr)),
							&(*tree)->left);
		split_by_nd_n_or(remove_outer_brackets(get_part_of_string(i + 1,
																	ft_strlen(ptr),
																	ptr)),
							&(*tree)->right);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*default_promt;
	char	*line;
	t_tree	*tree;

	(void)ac;
	(void)av;
	get_env(env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	line = NULL;
	while (1)
	{
		tree = NULL;
		default_promt = get_prompt_text();
		line = readline(default_promt);
		free(default_promt);
		if (exit_if_null(line))
			break ;
		line = get_full_line(line);
		if (exit_if_null(line))
			break ;
		add_history(line);
		split_by_nd_n_or(remove_outer_brackets(line), &tree);
		parse_tree(tree);
//		tree_iterat(tree, 1);
		shell_exec(tree);
		clear_tree(tree);
	}
}
