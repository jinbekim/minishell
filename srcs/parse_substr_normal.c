/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_substr_normal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:46 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/15 20:38:17 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
** 1. substr objs between ' ' and ' ' or ' ' and eof.
*/

static int	ft_is_end(char chr)
{
	if (ft_isblank(chr) || chr == '>' || chr == '<' || chr == '\0')
		return (1);
	return (0);
}

static char	*substr_switch(char *tmp, char *cmd, t_list *env, int *i)
{
	char	*tmp2;

	tmp2 = NULL;
	if (cmd[(*i)] == '\"')
		tmp2 = substr_quote_double(cmd, env, i);
	else if (cmd[(*i)] == '\'')
		tmp2 = substr_quote_single(cmd, env, i);
	tmp = ft_join_both_free(tmp, tmp2);
	return (tmp);
}

char		*substr_normal(char *cmd, t_list *env, int *i)
{
	char	*tmp;
	int		start;

	start = *i;
	tmp = NULL;
	while (ft_is_end(cmd[(*i)]) == 0)
	{
		if (cmd[(*i)] == ESCAPE)
			(*i)++;
		else if (cmd[(*i)] == '\"' || cmd[(*i)] == '\'')
		{
			tmp = make_tmp(cmd, tmp, start, i);
			tmp = substr_switch(tmp, cmd, env, i);
			start = (*i);
		}
		if (ft_isblank(cmd[(*i)]) || cmd[(*i)] == '\0'
		|| cmd[*i] == '>' || cmd[*i] == '<')
			break ;
		(*i)++;
	}
	if (start != (*i))
		tmp = make_tmp(cmd, tmp, start, i);
	return (tmp);
}
