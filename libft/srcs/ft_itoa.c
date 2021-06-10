/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 15:58:58 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 16:04:20 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_itoa_core(int n, int len, int token)
{
	char		*arr;

	arr = malloc(len + 1);
	if (!arr)
		return (0);
	arr[len] = 0;
	if (token == -1)
		arr[0] = '-';
	while (n)
	{
		len--;
		arr[len] = n % 10 + '0';
		n /= 10;
	}
	return (arr);
}

char			*ft_itoa(int n)
{
	int			tmp;
	int			token;
	int			len;

	len = 0;
	token = 1;
	if (n == 0)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n < 0)
	{
		token = -1;
		n = -n;
		len++;
	}
	tmp = n;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	return (ft_itoa_core(n, len, token));
}
