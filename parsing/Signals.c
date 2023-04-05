/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:21:33 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/04 05:09:38 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(0, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
void	handle_sigint_n_chld(int sig)
{
	(void)sig;
	write(0, "\n", 1);

}

void	handle_sigquit(int sig)
{
	(void)sig;
	exit(0);
}
void	here_doc_signal(int sig)
{
	(void)sig;
	exit(M_SIG_INT);
}
