#ifndef TREE_H
# define TREE_H
# include "./minishell.h"

typedef struct s_tree
{
	int				op;
	char			*content;

	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

t_tree				*new_tree_node(int op, char *content);
void				tree_iterat(t_tree *tree, int i);
#endif