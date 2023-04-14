/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:30:45 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/14 07:38:49 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "syntax.h"

int	handle_syntax(char *line)
{
	char	near;
	int		pos;

	pos = 0;
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

int	type(int flag, int *pos)
{
	if (flag == 2)
		return ('"');
	else if (flag == 1)
		return ('\'');
	*pos = -1;
	return (-1);
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

void	update_pipe(int *flag, char *line, int qute_flag, int i)
{
	if (!qute_flag && (is_n_escaped(line, '|', i)
			|| is_n_escaped(line, ';', i)))
		(*flag)++;
	else if (!qute_flag && line[i] != ' ' && line[i] != '\n')
		*flag = 0;
}
