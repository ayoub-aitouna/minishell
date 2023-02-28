#ifndef TREE_H
# define TREE_H
# include "../minishell.h"
# include "../types.h"

t_tree	*new_tree_node(int op, char *content);
void	tree_iterat(t_tree *tree, int depth);
int		calculat_debpt(t_tree *tree);
void	parse_tree(t_tree *tree);
#endif