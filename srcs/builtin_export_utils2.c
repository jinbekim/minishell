/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sushin <sushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:47:52 by sushin            #+#    #+#             */
/*   Updated: 2021/06/10 14:58:14 by sushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int			is_exist_env(char *str, t_list *env)
{
	while (env)
	{
		if (!(ft_strncmp(((t_env *)env->content)->key, str, 50)))
			return (1);
		env = env->next;
	}
	return (0);
}

void		sort_argv(char **tmp_key, int count)
{
	int		i;
	int		k;
	char	*temp;

	i = 0;
	while (i < count)
	{
		k = 0;
		while (k < count - i)
		{
			if (ft_strncmp(tmp_key[k], tmp_key[k + 1], 50) > 0)
			{
				temp = tmp_key[k];
				tmp_key[k] = tmp_key[k + 1];
				tmp_key[k + 1] = temp;
			}
			k++;
		}
		i++;
	}
}
