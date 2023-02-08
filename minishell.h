#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <fcntl.h>
# include <unistd.h>


typedef struct node
{
	int input_file;
	char *commend;
	char **arguments;
	int output_file;
} m_node;

int		here_doc(char *limiter);
void	parse_cur_commend(char *line, t_list **list);
t_list	*parse(char *line);
void	tty(void);
char	*get_str(char *s, int *index);
size_t	size(char **ptr);
char	*strip_nl(char *line);
m_node	*new_m_node();
void	printf_list(t_list *list);

#endif
