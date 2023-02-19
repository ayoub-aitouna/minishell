/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:34:35 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/17 18:36:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_between_qute(char *line)
{
	int i;

	int qute_flag, flag;
	qute_flag = 0;
	flag = 0;
	i = 0;
	while (line[i] != 0 && ((line[i] != '|' && line[i] != '>' && line[i] != '<' && line[i] != ' ') || qute_flag))
	{
		flag = qute_flag;
		toggle_quteflag(line[i], &qute_flag);
		i++;
	}
	return (flag);
}



char *copy_file_name(char *s, int *index)
{
	int qute_flag;
	char *new_str;
	char *env_value = NULL;
	char **new_str_spltd;
	qute_flag = 0;
	new_str = NULL;
	int i = 0;
	while (s[i] != 0 && (is_token_sep(s[i]) || qute_flag))
	{
		if (s[i] == '"' || s[i] == '\'')
			toggle_quteflag(s[i], &qute_flag);
		else
		{
			if (qute_flag != 1 && s[i] == '$')
			{
				env_value = copy_variable_value(env_value, s, &i);
				if (qute_flag == 0)
				{
					new_str_spltd = ft_split(env_value, ' ');
					if (size(new_str_spltd) > 1)
					{
						free_list(new_str_spltd);
						if (new_str != NULL)
							free(new_str);
						(*index) += i + 1;
						return (NULL);
					}
					free_list(new_str_spltd);
				}
				new_str = mini_strjoin(new_str, env_value);
				if ((s[i] == '"' && qute_flag == 2))
					qute_flag = 0;
			}
			else if (((s[i] != '"' && s[i] != '\'') || qute_flag))
				new_str = concate_str(s[i], new_str, qute_flag);
		}
		i++;
	}
	(*index) += i;
	return (new_str);
}

char *get_file_name(char *line, int *index)
{
	int		i;
	char	*file_name;

	i = 0;
	i += spaces_count(line);
	file_name = copy_file_name(&line[i], &i);
	i += spaces_count(line);
	*index = *index + i;
	return file_name;
}

int open_input_file(char *line, int *i)
{
	int input_file;
	char *file_name;
	int qute_flag;

	if (line[(*i) + 1] == '<')
	{
		qute_flag = is_between_qute(&line[(*i) + 2]);
		return (here_doc(qute_flag, get_str(&line[(*i) + 2], i, 0)));
	}
	else
	{
		file_name = get_file_name(&line[++(*i)], i);
		if (file_name == NULL)
			printf(RED "ambiguous redirect \n"RESET);
		else
			input_file = open(file_name, O_RDONLY);
		if (input_file == -1)
		{
		}
		if (file_name != NULL)
			free(file_name);
	}
	return (input_file);
}

int open_output_file(char *line, int *i)
{
	int opne_flag;
	int output_file;
	char *file_name;

	opne_flag = 0;
	if (line[(*i) + 1] == '>')
	{
		(*i)++;
		opne_flag = O_CREAT | O_RDWR | O_APPEND;
	}
	else
		opne_flag = O_CREAT | O_RDWR | O_TRUNC;
	file_name = get_file_name(&line[++(*i)], i);
	if (file_name == NULL)
		printf(RED "ambiguous redirect\n" RESET);
	else
		output_file = open(file_name, O_RDONLY);
	output_file = open(file_name, opne_flag, 0664);
	if (output_file == -1)
	{
	}
	if (file_name != NULL)
		free(file_name);
	return (output_file);
}
