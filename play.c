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

void	go_to_home(void)
{
	char	cur_dir[64];

	getcwd(cur_dir, 64);
}

void	change_directory(char *derictory)
{
	if (ft_strncmp("", derictory, 1) == 0)
		return (go_to_home());
	chdir(derictory);
}

int	main(void)
{
	chdir("/home/ayoub/1337");
	char cur_dir[64];

	getcwd(cur_dir, 64);
	printf("cur dir <%s>", cur_dir);

	chdir("");
	getcwd(cur_dir, 64);
	printf("cur dir <%s>", cur_dir);
}