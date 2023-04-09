/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:30:45 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/09 18:30:46 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "syntax.h"

int	handle_syntax(char *line)
{
	char	near;
	int		pos;

	near = check_syntax(line, &pos);
	if (near != -1)
	{
		if (near == '\n' || near == 0)
			ft_printf(RED "-bash: syntax error near "
				" unexpected token `newline' \n" RESET);
		else
			ft_printf(RED "-bash: syntax error near "
				" unexpected token `%c' \n" RESET, near);
		add_history(line);
		manage_here_doc(line, pos);
		return (1);
	}
	return (0);
}

int	is_nl(char *line, int i)
{
	int	n_only;

	n_only = 0;
	if (i > 0)
		n_only = (line[i - 1] == '\\');
	return (line[i] == '\\'
		&& line[i + 1] == 0 && !n_only);
}

int	is_complete(char *line)
{
	int	i;
	int	is_complete;

	i = 0;
	is_complete = 1;
	while (line[i])
	{
		if (is_n_escaped(line, '|', i)
			|| is_n_escaped(line, '\\', i))
			is_complete = 0;
		else if (line[i] != ' ' && line[i] != '\n')
			is_complete = 1;
		i++;
	}
	return (is_complete);
}
