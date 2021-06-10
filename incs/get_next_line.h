/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 23:09:12 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/09 09:35:18 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define OPEN_MAX 256
# define BUFFER_SIZE 4

# include <signal.h>
# include <termcap.h>
# include <termios.h>
# include "libft.h"

enum	e_keycode{
	CTRLC = 3,
	CTRLD = 4,
	BCKSPC = 127,
	UP_KEY = 4283163,
	DW_KEY = 4348699,
};

/*
**Part. get_next_line
*/
int		has_newline(char *backup);
int		get_next_line(int fd, char **line);
void	cut_with_newline(char **backup);
char	*ft_strjoin_free(char *s1, char *s2);

/*
**Part. termios setting
*/
void	set_initial_termios(void);
void	set_input_termios(void);

/*
**Part. termcap setting
*/
void	handle_input(char **backup, char *buff);
void	erase_one(char **backup);
void	erase_all(char *backup);

/*
**Part. signal handle
*/
void	handle_signal(void);

/*
**Part. history handle
*/
t_list	*save_history(char *cmd);
char	*call_history(int flag);

#endif
