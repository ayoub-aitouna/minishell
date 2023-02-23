#include "../../minishell.h"
#ifndef BUILT_H
# define BUILT_H
void	change_directory(char *derictory);
void	env(void);
void	unset(char *name);
void	export(char *env_var);
#endif