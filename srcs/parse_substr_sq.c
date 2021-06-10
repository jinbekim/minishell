/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_substr_sq.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:51 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:27:36 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
** 1. loop til single quote
** 2. rechange ESCAPE code which changed at first parsing.
*/

char		*substr_quote_single(char *cmd, t_list *env, int *i)
{
	char	*tmp[3];
	int		start;

	tmp[0] = NULL;
	start = ++(*i);
	while (cmd[(*i)] != '\'')
	{
		if (cmd[*i] == ESCAPE)
			cmd[(*i)] = '\\';
		(*i)++;
	}
	tmp[0] = make_tmp(cmd, tmp[0], start, i);
	if (ft_isblank(cmd[++(*i)]) || cmd[(*i)] == '\0'
	|| cmd[(*i)] == '>' || cmd[(*i)] == '<')
		return (tmp[0]);
	tmp[1] = ft_separate(cmd, env, i);
	tmp[2] = ft_join_both_free(tmp[0], tmp[1]);
	return (tmp[2]);
}
