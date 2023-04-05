/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:41:01 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/04 04:39:42 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst | !del)
		return ;
	while ((*lst))
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = temp;
	}
	lst = 0;
}
