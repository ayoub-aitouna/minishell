#ifndef MINISHELL_H
#define MINISHELL_H
#include "./libft/libft.h"

typedef enum TOKEN_TYPE
{
	CMD, REDECTION, FILE_TOKEN
} TOKEN;

typedef struct node
{
	void *content;
	TOKEN token;
} m_node;

#endif
