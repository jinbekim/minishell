/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:05:09 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 15:04:22 by sushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	digit_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

static void	result_exit(char *argv[], int i)
{
	if (i == 2)
		exit(ft_atoi(argv[1]));
	else
	{
		printf("exit\n");
		print_err_msg(argv[0], NULL);
		ft_putstr_fd("too many arguments\n", 2);
		g_exitcode = 1;
	}
}

int			bt_exit(char *argv[])
{
	int	i;

	if (argv[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	i = 0;
	while (argv[i])
		i++;
	if (digit_exit(argv[1]))
		result_exit(argv, i);
	else
	{
		printf("exit\n");
		print_err_msg(argv[0], NULL);
		ft_putstr_fd("numeric argument required\n", 2);
		exit(255);
	}
	return (0);
}
