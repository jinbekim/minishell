/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 22:11:22 by jinbekim          #+#    #+#             */
/*   Updated: 2020/12/28 14:52:47 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp2 = *lst;
	while (tmp2)
	{
		tmp = tmp2;
		tmp2 = tmp2->next;
		ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}
