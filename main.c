#include "main.h"
#include "minishell.h"
char **get_env(char **p)
{
	static char **env;
	if(p != NULL)
		env = p;
	return (env);
}
void printf_arg(char **str)
{
	int i = 0;
	ft_printf("arguments  		< ");
	if (str == NULL)
	{
		ft_printf("(null) >\n");
		return;
	}
	while (str[i])
		printf("%s ,", str[i++]);
	printf(" >\n");
}

void print_table(m_node *node)
{
	ft_printf("input file 		<%d> \n", node->input_file);
	ft_printf("commend    		<%s> \n", node->commend);
	printf_arg(node->arguments);
	ft_printf("output_file file 	<%d> \n", node->output_file);
}

void printf_list(t_list *list)
{
	int i;

	i = 0;
	if (list == NULL)
		return;
	while (list)
	{
		m_node *node = (m_node *)list->content;
		if (!node)
		{
			printf("node null");
			return;
		}
		printf("\n---------------\tnode_%d\t--------------\n", i);
		print_table(node);
		printf("\n--------------------------------------\n");
		i++;
		list = list->next;
	}
}

int main(int ac, char **av, char **env)
{
	get_env(env);
	tty();
}