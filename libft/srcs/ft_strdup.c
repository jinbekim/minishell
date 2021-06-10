/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:09:01 by jinbekim          #+#    #+#             */
/*   Updated: 2021/05/10 18:29:49 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*c1;

	len = ft_strlen(s1);
	c1 = (char *)malloc(sizeof(char) * (len + 1));
	if (!c1)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		c1[len] = s1[len];
		len++;
	}
	c1[len] = 0;
	return (c1);
}
