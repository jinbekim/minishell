/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:38 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:25:57 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
** 1. if you want to change env, use EXPORT func
*/

void		parse_env_list(char **envp, t_list **env)
{
	t_env	*new;
	int		i;
	int		j;

	i = -1;
	*env = NULL;
	while (envp[++i])
	{
		j = 0;
		new = malloc(sizeof(t_env));
		if (new == NULL)
			exit(1);
		while (envp[i][j] != '=')
			j++;
		new->key = ft_substr(envp[i], 0, j);
		new->value = ft_strdup(getenv(new->key));
		ft_lstadd_back(env, ft_lstnew(new));
	}
}
