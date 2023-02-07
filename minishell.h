#ifndef MINISHELL_H
#define MINISHELL_H
#include "./libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

typedef enum TOKEN_TYPE
{
	CMD, REDECTION, FILE_TOKEN
} TOKEN;

typedef struct node
{
	int input_file;
	char *commend;
	char **arguments;
	int output_file;
} m_node;

#endif
