/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:24 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/17 09:59:22 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void		print_history(char **backup, char *past)
{
	static char	*tmp;
	int			i;

	i = 0;
	if (tmp == NULL && past == NULL)
		return ;
	erase_all(*backup);
	if (past != NULL)
	{
		if (tmp == NULL && *backup)
			tmp = ft_strdup(*backup);
		else if (tmp == NULL)
			tmp = ft_strdup("");
		if (*backup)
			free(*backup);
		*backup = ft_strdup(past);
	}
	else
	{
		free(*backup);
		*backup = tmp;
		tmp = NULL;
	}
	write(1, *backup, ft_strlen(*backup));
}

void			handle_input(char **backup, char *buff)
{
	char		*past;

	tgetent(NULL, "xterm");
	if (ft_isprint(*buff) || *buff == 10)
	{
		write(1, buff, 1);
		return ;
	}
	if (*buff == CTRLC)
	{
		if (*backup)
			free(*backup);
		*backup = NULL;
		g_exitcode = 1;
		write(1, "\ncash$ ", 8);
	}
	else if (*buff == BCKSPC)
		erase_one(backup);
	else if (*(int *)buff == UP_KEY)
		past = call_history(1);
	else if (*(int *)buff == DW_KEY)
		past = call_history(-1);
	if (*(int *)buff == UP_KEY || *(int *)buff == DW_KEY)
		print_history(backup, past);
	*buff = '\0';
}
