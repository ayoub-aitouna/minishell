/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:17:18 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/14 16:18:35 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_equal(char *s, char *s2)
{
	return (ft_strlen(s) == ft_strlen(s2) && !ft_strncmp(s, s2, ft_strlen(s)));
}