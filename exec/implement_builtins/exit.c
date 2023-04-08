/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:33:11 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/07 12:10:33 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

int	get_nub_len(char *str)
{
	int	len;

	if (!str)
		return (0);
	if (str[0] == '-')
		len = ft_strlen(str) - 1;
	else
		len = ft_strlen(str);
	return (len);
}

void	is_max_min(char *str)
{
	long	status;
	int		check;
	int		len;

	len = get_nub_len(str);
	check = -1;
	if (strcmp(str, "-9223372036854775807") == 0
		|| strcmp(str, "-9223372036854775808") == 0)
	{
		status = ft_atoi(str);
		exit_msg("MiniSHell: exit_else\n", status);
	}
	else if ((str[0] == '-' ) && (strcmp(str, "-9223372036854775809") == 0
			|| (len == 19 && !strncmp(str, "-922337203685477580", len)
				&& !f_isdigit(str[len]))))
		check = 0;
	else if ((strcmp(str, "9223372036854775808") == 0)
		|| (len == 19 && (!(strncmp(str, "922337203685477580", len - 1)
					&& f_isdigit(str[len - 1])))))
		check = 0;
	if (!check || len > 19)
	{
		printf("exit\nMiniSHell: exit: %s: ", str);
		exit_msg("numeric argument required\n", 255);
	}
}

void	numeric_required(m_node *node, int len)
{
	long	status;
	int		i;
	int		check;

	status = 0;
	check = 1;
	i = 0;
	status = ft_atoi(node->arguments[1]);
	if (node->arguments[1][0] == '-' || node->arguments[1][0] == '+')
		i = 1;
	while (node->arguments[1][i])
		if (!ft_isdigit(node->arguments[1][i++]))
			check = 0;
	if (!check || len > 19)
	{
		is_max_min(node->arguments[1]);
		printf("exit\nMiniSHell: exit: %s: ", node->arguments[1]);
		exit_msg("numeric argument required\n", 255);
	}
	else
		exit_msg("MiniSHell: exit\n", status);
}

void	exit_command(m_node *node)
{
	int	len;

	len = get_nub_len(node->arguments[1]);
	if (!node->arguments[1])
		exit_msg("MiniSHell: exit\n", 0);
	else if (node->arguments[2] && (ft_atoi(node->arguments[1])) != 0)
	{
		printf("exit\nMiniSHell: exit: too many arguments\n");
		return ;
	}
	else if (strcmp(node->arguments[1], "0") == 0 && !node->arguments[2])
		exit_msg("MiniSHell: exit\n", 0);
	else if (node->arguments[2] && (ft_atoi(node->arguments[1])) == 0)
	{
		printf("exit\nMiniSHell: exit: %s: ", node->arguments[1]);
		exit_msg("numeric argument required\n", 255);
	}
	else if (!node->arguments[2])
		numeric_required(node, len);
}
