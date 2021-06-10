/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:48:27 by jinbekim          #+#    #+#             */
/*   Updated: 2021/05/10 18:27:29 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ans;

	i = 0;
	ans = malloc(ft_strlen(s) + 1);
	if (!ans)
		return (0);
	while (*s)
	{
		ans[i] = f(i, *s);
		s++;
		i++;
	}
	ans[i] = 0;
	return (ans);
}
