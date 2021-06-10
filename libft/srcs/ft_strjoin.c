/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 21:45:21 by jinbekim          #+#    #+#             */
/*   Updated: 2021/05/10 18:26:28 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*arr;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	arr = malloc(len1 + len2 + 1);
	if (!arr)
		return (0);
	while (s1[i])
	{
		arr[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		arr[len1 + i] = s2[i];
		i++;
	}
	arr[len1 + i] = 0;
	return (arr);
}
