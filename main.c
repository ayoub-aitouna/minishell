#include"minishell.h"

void tty()
{
    char *line;
    while (1)
    {
        ft_printf("minishell> ");
        line = get_next_line(0);
        if(line == NULL) break;
    }
    
}


int main()
{
    tty();
}