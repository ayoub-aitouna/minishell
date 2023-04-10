/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:01:27 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/10 01:01:27 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

t_helper	g__helper;

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g__helper.checker = -1;
	print_name();
	if (!size(env))
		g__helper.checker = 0;
	env = necessary_values(env);
	get_export(env);
	get_env(env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	tty();
}
