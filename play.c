/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 21:07:41 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/12 15:07:09 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// char *ftstrappend(char *s, char c)
// {
//     int i = 0;
//     int len = ft_strlen(s);
//     char *new_str = malloc(len + 2);
//     while (i < len)
//     {
//         new_str[i] = s[i];
//         i++;
//     }
//     new_str[i++] = c;
//     new_str[i] = 0;
//     free(s);
//     return (new_str);
// }



void test(int *a)
{
    int k = *a;
    (*a)++;
}

int main()
{
    int i = 0;
    char *s = NULL;
    // while (i < 10)
    // {
    //     s = ftstrappend(s, 'A');
    //     i++;
    // }
    test(&i);
    printf("<%d>",i);
}