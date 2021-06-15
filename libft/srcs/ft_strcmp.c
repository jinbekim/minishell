/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:10:29 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/15 19:45:16 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	const unsigned char	*c1;
	const unsigned char	*c2;

	c1 = (const unsigned char *)s1;
	c2 = (const unsigned char *)s2;
	i = 0;
	while (c1[i] && c2[i])
	{
		if (c1[i] != c2[i])
			return ((int)(c1[i] - c2[i]));
		i++;
	}
	if (c1[i] != c2[i])
		return ((int)(c1[i] - c2[i]));
	return (0);
}
