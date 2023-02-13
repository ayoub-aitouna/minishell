/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:22:45 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/13 18:26:37 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void change_directory(char *derictory)
{
	if (ft_strncmp("~", derictory, 1) == 0 || derictory == NULL)
		derictory = getenv("HOME");
	chdir(derictory);
}
