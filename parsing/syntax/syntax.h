#ifndef SYNTAX_H
#define SYNTAX_H

int		handle_syntax(char *line);
int		is_nl(char *line, int i);
int		is_complete(char *line);
char	check_syntax(char *line, int *pos);
void	manage_here_doc(char *line, int pos);

#endif
