/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/02/13 02:05:59 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/13 02:05:59 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	print_name();
	get_env(env);
	get_export(env);
	env = necessary_values(env);
	get_env(env);
	// set SHLVL
	// if Size(env) == 0 , set _ and PWD and OLDPWD
	// set /bin/ as default if size(env) == 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	tty();
}