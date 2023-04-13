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

int	main(int ac, char **av, char **env)
{
	char	**export;
	char	**new_env;

	(void)ac;
	(void)av;
	g__helper.checker = -1;
	g__helper.sh_lvl = is_high_shlvl(env) + 1;
	print_name();
	if (!size(env))
		g__helper.checker = 0;
	export = necessary_values(env, 0);
	new_env = necessary_values(env, 1);
	get_env(new_env);
	get_export(export);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	tty();
}

