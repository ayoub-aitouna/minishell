/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:43:34 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/09 02:08:35 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct node
{
	int		input_file;
	char	*command;
	char	**arguments;
	int		output_file;
	int		checker;
}			t_node;

typedef struct s_helper
{
	int	checker;

}	t_helper;

enum	e_exit_status
{
	M_SIG_INT = 78
};

enum	e_file_input
{
	NONE = -3,
	NO_FILE = -1,
	ERROR = -2,
};

typedef struct s_tree
{
	int				op;
	char			*content;

	struct s_tree	*left;
	struct s_tree	*right;
	struct node		*node;
}					t_tree;

typedef struct proccess
{
	int	length;
	int	*proccess;
}	t_proccess;

#endif
