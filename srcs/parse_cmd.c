/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:34 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/17 09:48:48 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
** 0. parse_cmd.c
*/

/*
** 1. To ignore (;, |, null) in quote
** 2. skip quote by looping.
*/

static int	skip_quote(char *line, int j, char quote)
{
	if (j != 0 && line[j - 1] == ESCAPE)
		return (j);
	j++;
	while (line[j] != quote && line[j] != '\0')
	{
		if (quote == '\"' && line[j] == ESCAPE)
			j++;
		if (line[j] == '\0')
			return (j);
		j++;
	}
	return (j);
}

/*
** 1. initialize arguments.
*/

static void	init_arg(char **line, int (*idx)[2], t_list **cmd)
{
	int		find;

	find = 0;
	(*idx)[0] = 0;
	(*idx)[1] = 0;
	*cmd = NULL;
	while ((*line)[find])
	{
		if ((*line)[find] == '\\')
		{
			(*line)[find] = ESCAPE;
			if ((*line)[find - 1] == ESCAPE)
				(*line)[find] = '\\';
		}
		find++;
	}
}

static int	check_angle_bracket_err(char *line, int idx, char bracket)
{
	int		mix_check;
	int		num_check;
	int		err_rtn;

	mix_check = idx;
	num_check = idx;
	err_rtn = idx;
	while (line[err_rtn])
		err_rtn++;
	while (line[mix_check] == '>' || line[mix_check] == '<')
		mix_check++;
	while (line[idx] == bracket)
		idx++;
	if (mix_check != idx || num_check + 2 < idx)
		return (err_rtn);
	while (line[idx] == ' ')
		idx++;
	if (line[idx] == '>' || line[idx] == '<'
	|| line[idx] == '\0' || line[idx] == '|' || line[idx] == ';')
		return (err_rtn);
	return (num_check);
}

/*
** make the cmd lists separated by null, semicolon, pipe
** 1. loop til the line end separator(null, semicolon, pipe)
**	1.1. To prevent empty cmd, loop space.
** 2. double loop til find "separator"(;, |, null)
**	2-0. if meet quote mark, skip the quote.
** 	2-1. if meet separator, make t_cmd
** 	2.2. sync j and i.
**	2.3. else in case ;; || occur, handling error
** 3. return cmd list
*/

static int	exception_cases(char *line, int idx)
{
	if (line[idx] == '"' || line[idx] == '\'')
		idx = skip_quote(line, idx, line[idx]);
	if (line[idx] == '>' || line[idx] == '<')
		idx = check_angle_bracket_err(line, idx, line[idx]);
	if (line[idx] == ESCAPE)
		idx++;
	return (idx);
}

t_list		*parse_cmd(char *line, t_list *cmd)
{
	int		id[2];

	init_arg(&line, &id, &cmd);
	while (line[id[1]])
	{
		while (ft_isblank(line[id[0]]))
			id[0]++;
		id[1] = id[0];
		while (line[id[1]] != ';' && line[id[1]] != '|' && line[id[1]] != '\0')
		{
			id[1] = exception_cases(line, id[1]);
			if (line[id[1]] == '\0')
				return (parse_fail(cmd));
			id[1]++;
		}
		if (id[1] != id[0])
			ft_lstadd_back(&cmd, ft_lstnew(ft_newcmd(line, id[0], id[1])));
		else if (line[id[1]] != '\0' || line[id[1] - 1] == '|')
			return (parse_fail(cmd));
		id[0] = id[1] + 1;
	}
	return (cmd);
}
