/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_for_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:15 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:33:02 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		eof_return(int readsize, char **backup, char **line)
{
	if (!(*backup))
	{
		if (readsize == -1)
			return (readsize);
		else
			*line = ft_strdup("");
	}
	else
	{
		*line = *backup;
		*backup = NULL;
	}
	return (readsize);
}

static char		*return_line(char *backup)
{
	int			i;
	int			j;
	char		*arr;

	j = 0;
	i = has_newline(backup);
	arr = malloc(i + 1);
	if (!arr)
		return (NULL);
	arr[i] = '\0';
	while (j < i)
	{
		arr[j] = backup[j];
		j++;
	}
	save_history(arr);
	call_history(0);
	return (arr);
}

static void		eof_handle(int *readsize, char **backup, char *buff)
{
	if (*backup == NULL || **backup == '\0')
		*readsize = 0;
	else if (*backup != NULL)
		buff[0] = '\0';
}

int				get_next_line(int fd, char **line)
{
	int			readsize;
	char		buff[BUFFER_SIZE + 1];
	static char	*backup[OPEN_MAX] = {0, };

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0 || !line)
		return (-1);
	while (has_newline(backup[fd]) == -1)
	{
		readsize = read(fd, buff, BUFFER_SIZE);
		buff[readsize] = '\0';
		if (*buff == CTRLD)
			eof_handle(&readsize, &backup[fd], buff);
		else
			handle_input(&backup[fd], buff);
		if (readsize <= 0)
			return (eof_return(readsize, &backup[fd], line));
		if (!backup[fd])
			backup[fd] = ft_strdup(buff);
		else
			backup[fd] = ft_strjoin_free(backup[fd], buff);
	}
	*line = return_line(backup[fd]);
	cut_with_newline(&backup[fd]);
	return (1);
}
