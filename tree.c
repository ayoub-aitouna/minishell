#include "./tree.h"

t_tree	*new_tree_node(int op, char *content)
{
	t_tree	*new_tree;

	new_tree = malloc(sizeof(t_tree));
	new_tree->op = op;
	new_tree->content = content;
	new_tree->left = NULL;
	new_tree->right = NULL;
	return (new_tree);
}
void	tree_iterat(t_tree *tree, int depth)
{
	if (tree == NULL)
	{
		return ;
	}

	// Print the current node with indentation based on the depth
	for (int i = 0; i < depth; i++)
	{
		printf("    ");
	}
	printf("|--%d:%s\n", tree->op, tree->content);

	// Recursively print the left and right subtrees with increased depth
	tree_iterat(tree->left, depth + 1);
	tree_iterat(tree->right, depth + 1);
}