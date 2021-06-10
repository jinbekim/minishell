/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:34:12 by jinbekim          #+#    #+#             */
/*   Updated: 2021/05/10 18:27:53 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*arr;
	size_t		len;

	len = count * size;
	arr = malloc(len);
	if (!arr)
		return (0);
	ft_memset(arr, 0, len);
	return (arr);
}
