/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_substr_dq.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:40 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/15 20:55:18 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
** 1. join tmp str and substr;
*/

char		*make_tmp(char *cmd, char *tmp, int start, int *i)
{
	char	*tmp2;
	char	*tmp3;

	if (tmp == NULL)
		return (ft_substr(cmd, start, (*i) - start));
	tmp2 = ft_substr(cmd, start, (*i) - start);
	tmp3 = ft_join_both_free(tmp, tmp2);
	return (tmp3);
}

/*
** 1. loop til wrap-up double_quote
** 2. In the middle if you find $(env_key) substitute.
*/

static int	check_exception(char arg)
{
	if (arg == '$' || arg == '`' || arg == '\\' || arg == '\"')
		return (0);
	else
		return (1);
}

char		*substr_quote_double(char *cmd, t_list *env, int *i)
{
	char	*tmp[3];
	int		start;

	tmp[0] = NULL;
	start = ++(*i);
	while (cmd[(*i)] != '\"' || cmd[(*i) - 1] == ESCAPE)
	{
		if (cmd[(*i)] == ESCAPE && check_exception(cmd[(*i) + 1]))
			cmd[(*i)] = '\\';
		else if (cmd[(*i)] != '\"' || cmd[(*i) - 1] == ESCAPE)
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
