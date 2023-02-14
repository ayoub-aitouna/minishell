/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:23:36 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/14 17:08:58 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	print_working_directory(void)
{
	char *working_directory = NULL;
	working_directory = getcwd(NULL, 0);
	printf("%s\n", working_directory);
	free(working_directory);
}