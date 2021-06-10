/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:22 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:33:27 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int			reset_index(int flag)
{
	static int		i;

	if (flag == 0)
	{
		i = 0;
		return (0);
	}
	i += flag;
	if (i > 10)
		i = 10;
	else if (i < 0)
		i = 0;
	return (i);
}

t_list				*save_history(char *cmd)
{
	static t_list	*past;
	t_list			*tmp;

	if (cmd == NULL || *cmd == 0)
		return (past);
	if (ft_lstsize(past) == 10)
	{
		tmp = ft_lstlast(past);
		tmp->prev->next = NULL;
		ft_lstdelone(tmp, free);
	}
	ft_lstadd_front(&past, ft_lstnew(ft_strdup(cmd)));
	return (past);
}

char				*call_history(int flag)
{
	t_list			*tmp;
	int				j;

	j = reset_index(flag);
	if (j == 0)
		return (NULL);
	tmp = save_history(NULL);
	if (tmp == NULL)
		return (NULL);
	j--;
	while (j && tmp->next)
	{
		j--;
		tmp = tmp->next;
	}
	if (j == 1)
		reset_index(-1);
	return (tmp->content);
}
