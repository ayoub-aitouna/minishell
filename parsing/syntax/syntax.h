/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:43:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/09 19:43:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

int		handle_syntax(char *line);
int		is_nl(char *line, int i);
int		is_complete(char *line);
char	check_syntax(char *line, int *pos);
void	manage_here_doc(char *line, int pos);
void	update_pipe(int *flag, char *line, int qute_flag, int i);
int		type(int flag, int *pos);
#endif
