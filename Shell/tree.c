#include "./shell.h"

t_tree	*new_tree_node(int op, char *content)
{
	t_tree	*new_tree;

	new_tree = malloc(sizeof(t_tree));
	new_tree->op = op;
	new_tree->content = content;
	new_tree->left = NULL;
	new_tree->node = NULL;
	new_tree->right = NULL;
	return (new_tree);
}
void	t_printf_arg(char **str, int white_space)
{
	int	i;

	i = 0;
	printf("%*s arguments  		< ", white_space, "-");
	if (str == NULL)
	{
		printf("(null) >\n");
		return ;
	}
	while (str[i])
		printf("%s ,", str[i++]);
	printf(" >\n");
}

void	t_print_table(m_node *node, int white_space)
{
	printf("%*s-input file 		<%d> \n", white_space, "", node->input_file);
	printf("%*s-command    		<%s> \n", white_space, "", node->command);
	t_printf_arg(node->arguments, white_space);
	printf("%*s-output_file file 	<%d> \n", white_space, "",
				node->output_file);
}

void	print_node(t_tree *tree, int white_space)
{
	m_node	*node;

	if (tree == NULL || tree->node == NULL)
		return ;
	node = (m_node *)tree->node;
	if (!node)
	{
		printf("node null");
		return ;
	}
	printf("\n%*s---------------\tnode\t--------------\n", white_space, "");
	t_print_table(node, white_space);
	printf("%*s--------------------------------------\n", white_space, "");
}

void	tr_parse(char *line, t_tree *tree)
{
	int		i;
	m_node	*node;

	if (line == NULL)
		return ;
	node = new_m_node();
	i = 0;
	while (line[i])
	{
		if (is_n_escaped(line, '<', i))
			node->input_file = open_input_file(line, &i, node->output_file);
		else if (is_n_escaped(line, '>', i))
			node->output_file = open_output_file(line, &i, node->input_file);
		else
			get_input_value(&line[i], node, &i, 0);
	}
	node->command = update_command(node->command);
	tree->node = node;
}

void	parse_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left == NULL && tree->right == NULL)
	{
		tr_parse(tree->content, tree);
	}
	parse_tree(tree->left);
	parse_tree(tree->right);
}

void	tree_iterat(t_tree *tree, int depth)
{
	if (tree == NULL)
		return ;
	for (int i = 0; i < depth + 7; i++)
	{
		if (i < depth)
			printf(" ");
		else
			printf("-");
	}
	printf(BOLDBLUE "|--%d:" BOLDMAGENTA "%s\n" RESET, tree->op, tree->content);
	print_node(tree, depth + 7);
	tree_iterat(tree->left, depth + ft_strlen(tree->content));
	tree_iterat(tree->right, depth + ft_strlen(tree->content));
}
