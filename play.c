/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 21:07:41 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/13 18:39:39 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int main(int ac, char **av)
{

	change_directory(av[1]);
	char cur_dir[64];
	getcwd(cur_dir, 64);
	printf("cur dir <%s>\n", cur_dir);
}