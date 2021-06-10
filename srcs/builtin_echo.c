/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:05:15 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 16:28:52 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	check_nling(char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (strncmp(&str[i], "n", 1))
			return (0);
		i++;
	}
	return (1);
}

static int	find_nl(char *argv[], int *i)
{
	int	check_nl;

	check_nl = 1;
	while (argv[*i])
	{
		if (!(ft_strncmp(argv[*i], "-n", 2)))
		{
			if (argv[*i][2])
				if (!(check_nling(argv[*i])))
				{
					(*i)++;
					return (check_nl);
				}
			check_nl = 0;
		}
		else
		{
			(*i)++;
			return (check_nl);
		}
		(*i)++;
	}
	(*i)++;
	return (check_nl);
}

int			bt_echo(char *argv[])
{
	int	i;
	int	check_nl;

	i = 1;
	check_nl = find_nl(argv, &i);
	while (argv[i - 1])
	{
		ft_putstr_fd(argv[i - 1], 1);
		if (argv[i])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (check_nl)
		ft_putchar_fd('\n', 1);
	g_exitcode = 0;
	return (0);
}
