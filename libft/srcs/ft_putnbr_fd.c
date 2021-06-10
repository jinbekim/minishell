/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 20:08:04 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 16:03:49 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_recursive(unsigned int n, int fd)
{
	if (n / 10)
		ft_recursive(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

void				ft_putnbr_fd(int n, int fd)
{
	unsigned int	tmp;

	if (n < 0)
	{
		tmp = (unsigned int)n * -1;
		ft_putchar_fd('-', fd);
		ft_recursive(tmp, fd);
	}
	else if (n >= 0)
	{
		ft_recursive((unsigned int)n, fd);
	}
}
