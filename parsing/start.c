/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:22:08 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/22 07:09:48 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_name(void)
{
	printf("\e[1;1H\e[2J\n");
	printf("\n");
    printf(BOLDGREEN" *****     *****  ***  *****     ***  ***  "BOLDBLUE"*********   ***      ***  *********  ***        ***      \n");
    printf(BOLDGREEN" *** **   ** ***  ***  *** **    ***  ***  "BOLDBLUE"***         ***      ***  ***        ***        ***      \n");
    printf(BOLDGREEN" ***  ** **  ***  ***  ***  **   ***  *** "BOLDBLUE" ***         ***      ***  ***        ***        ***      \n");
    printf(BOLDGREEN" ***   ***   ***  ***  ***   **  ***  *** "BOLDBLUE" **********  ************  ********   ***        ***      \n");
    printf(BOLDGREEN" ***    *    ***  ***  ***    ** ***  *** "BOLDBLUE"        ***  ***      ***  ***        ***        ***      \n");
    printf(BOLDGREEN" ***         ***  ***  ***     *****  ***        "BOLDBLUE" ***  ***      ***  ***        ***        ***      \n");
    printf(BOLDGREEN" ***         ***  ***  ***      ****  ***  "BOLDBLUE"*********   ***      ***  *********  *********  *********\n");
    printf(RESET "\n");
}
