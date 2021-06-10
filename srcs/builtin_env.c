/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:05:17 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:31:03 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	bt_env(t_list *env)
{
	if (env == NULL)
		return (0);
	while (env)
	{
		if (((t_env *)env->content)->value)
			printf("%s=%s\n", ((t_env *)env->content)->key,
			((t_env *)env->content)->value);
		env = env->next;
	}
	g_exitcode = 0;
	return (0);
}
