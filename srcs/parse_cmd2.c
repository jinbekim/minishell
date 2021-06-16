/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:36 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/15 20:59:00 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
** 1. make t_cmd struct.
** 2. and initialize.
*/

t_cmd		*ft_newcmd(char *line, int i, int j)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return (0);
	new->cmd = ft_substr(line, i, (j - i));
	new->end = line[j];
	new->read_fd = 0;
	new->write_fd = 1;
	return (new);
}

/*
** 1. strjoin and free both
*/

char		*ft_join_both_free(char *tmp1, char *tmp2)
{
	char	*tmp3;

	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (tmp3);
}

/*
** 1. Separate cmd first.
** 2. substr each token.
** 	2-1. if meet ' ' skip.
**	2-2. if meet separator (dq, sq, rdr), substr
** 3. if fail return NULL.
**	3-1. In case :last char == ' ', place condition.
*/

char		*ft_separate(char *cmd, t_list *env, int *i)
{
	char	*tmp;
	int		escape;

	escape = (*i) - 1;
	if (escape < 0)
		escape = 0;
	tmp = NULL;
	if (cmd[(*i)] == '\"' && cmd[escape] != ESCAPE)
		tmp = substr_quote_double(cmd, env, i);
	else if (cmd[(*i)] == '\'' && cmd[escape] != ESCAPE)
		tmp = substr_quote_single(cmd, env, i);
	else if ((cmd[(*i)] == '>' || cmd[(*i)] == '<') && cmd[escape] != ESCAPE)
		tmp = substr_redirect(cmd, env, i);
	else
		tmp = substr_normal(cmd, env, i);
	return (tmp);
}

/*
** 0. convert t_cmd to char **argv
** 1. to error handle, use ptr.
*/

t_list		*parse_cmd2(char *cmd, t_list *env)
{
	char	*tmp;
	t_list	*argv;
	int		i;

	i = -1;
	tmp = NULL;
	argv = NULL;
	cmd = substitution_env_var(cmd, env);
	while (cmd[++i])
	{
		if (cmd[i] == ' ')
			continue ;
		tmp = ft_separate(cmd, env, &i);
		if ((long)tmp == -1)
		{
			ft_lstclear(&argv, free);
			break ;
		}
		else if (tmp != NULL)
			ft_lstadd_back(&argv, ft_lstnew(tmp));
		if (cmd[i] == '\0' || cmd[i] == '<' || cmd[i] == '>')
			i--;
	}
	free(cmd);
	return (argv);
}
