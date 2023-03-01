#ifndef TREE_H
# define TREE_H
# include "../minishell.h"
# include "../types.h"

t_tree	*new_tree_node(int op, char *content);
void	tree_iterat(t_tree *tree, int depth);
void	parse_tree(t_tree *tree);
void	split_by_pip(char *ptr, t_tree **tree);
void	split_by_nd_n_or(char *ptr, t_tree **tree);
void	shell_exec(t_tree *tree);
#endif