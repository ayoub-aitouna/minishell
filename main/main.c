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

// char **fill_necessary_values(char **env)
// {
// 	char **new_export;

// 	new_export = NULL;
// 	if(!env)
// 	{
// 		new_env = ft_strdup("heta _tji a khadija");
// 	}
// }

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	print_name();
	get_env(env);
	get_export(env);
	// fill_necessary_values();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	tty();
}