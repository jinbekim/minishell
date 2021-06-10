/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 20:48:51 by jinbekim          #+#    #+#             */
/*   Updated: 2021/05/10 18:26:56 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	i;

	i = 0;
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	arr = malloc(len + 1);
	if (!arr)
		return (0);
	while ((i < len) && s[i + start])
	{
		arr[i] = s[i + start];
		i++;
	}
	arr[i] = 0;
	return (arr);
}
