/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:23:23 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/14 16:39:46 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	echo(char **arguments)
{
	int i;
	int nl_flag;

	i = 0;
	nl_flag = 0;
	if (arguments == NULL)
	{
		printf("\n");
		return ;
	}
	if (is_equal(arguments[0], "-n"))
		nl_flag = 1;
	i += nl_flag;
	while (arguments[i])
	{
		printf("%s", arguments[i]);
		i++;
		if (arguments[i] != NULL)
			printf(" ");
		else
			break ;
	}
	if (!nl_flag)
		printf("\n");
}