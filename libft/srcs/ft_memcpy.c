/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:38:08 by jinbekim          #+#    #+#             */
/*   Updated: 2020/12/28 22:45:33 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*cst;
	char		*crc;

	if (!dst && !src)
		return (NULL);
	i = 0;
	cst = dst;
	crc = (char *)src;
	while (i < n)
	{
		cst[i] = crc[i];
		i++;
	}
	return (dst);
}
