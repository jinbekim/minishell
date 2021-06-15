/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:05:34 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/15 16:34:44 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void		unset_by_export(char *str, t_list *env)
{
	while (env)
	{
		if (!(ft_strncmp(((t_env *)env->content)->key, str, 50)))
		{
			env->prev->next = env->next;
			if (env->next != NULL)
				env->next->prev = env->prev;
			free(((t_env *)env->content)->key);
			free(((t_env *)env->content)->value);
			free(env->content);
			free(env);
			break ;
		}
		env = env->next;
	}
	return ;
}

static int	find_env(char *str, t_list *env)
{
	if (!(ft_strncmp(((t_env *)env->content)->key, str, 50)))
	{
		env->prev->next = env->next;
		if (env->next != NULL)
			env->next->prev = env->prev;
		free(((t_env *)env->content)->key);
		if (((t_env *)env->content)->value != NULL)
			free(((t_env *)env->content)->value);
		free(env->content);
		free(env);
		return (1);
	}
	return (0);
}

int			bt_unset(char *argv[], t_list *env)
{
	int		i;
	t_list	*init_env;

	if (argv[1] == NULL)
		return (0);
	if (ft_isdigit(argv[1][0]))
	{
		print_err_msg(argv[1], NULL);
		ft_putstr_fd("not a vlid identifier\n", 2);
		g_exitcode = 1;
	}
	init_env = env;
	i = 0;
	while (argv[++i])
	{
		env = init_env;
		while (env)
		{
			if (find_env(argv[i], env))
				break ;
			env = env->next;
		}
	}
	g_exitcode = 0;
	return (0);
}
