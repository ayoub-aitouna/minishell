/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:38:53 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/28 12:39:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stddef.h>
#ifndef BUILT_H
# define BUILT_H
void	change_directory(char *derictory);
void	env(void);
void	unset(char *name);
void	echo(char **arguments);
void	export(char *env_var);
size_t	size(char **ptr);
int		get_exit_status(void);
void	set_exit_status(int status_val);

#endif