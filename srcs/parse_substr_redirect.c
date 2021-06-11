/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_substr_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:44 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/11 18:37:03 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
** 0. substr_redirect.c
*/

static void	dup_fd(int fd, char *cmd, int idx)
{
	int		err;

	if (cmd[idx] == '<')
	{
		err = dup2(fd, 0);
		close(fd);
	}
	else
	{
		err = dup2(fd, 1);
		close(fd);
	}
	if (err == -1)
		print_errno_exit(1);
}

char		*substr_redirect(char *cmd, t_list *env, int *i)
{
	char	*path;
	int		fd;
	int		start;

	start = (*i);
	while (cmd[*i] == '>' || cmd[*i] == '<')
		(*i)++;
	while (ft_isblank(cmd[(*i)]))
		(*i)++;
	path = ft_separate(cmd, env, i);
	if (cmd[start] == '<')
		fd = open(path, O_RDONLY);
	else if (cmd[start] == '>' && cmd[start + 1] == '>')
		fd = open(path, O_APPEND | O_CREAT | O_WRONLY, 0644);
	else
		fd = open(path, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	free(path);
	if (fd == -1)
		return ((char *)-1);
	dup_fd(fd, cmd, start);
	return (NULL);
}
