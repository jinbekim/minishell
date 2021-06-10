/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:43:40 by jinbekim          #+#    #+#             */
/*   Updated: 2021/05/10 18:50:24 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*cst;
	const char	*crc;

	cst = dst;
	crc = (const char *)src;
	if (len == 0)
		return (dst);
	i = len - 1;
	if ((dst > src) && ((size_t)(dst - src) < len))
	{
		while (i > 0)
		{
			cst[i] = crc[i];
			i--;
		}
		cst[0] = crc[0];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
