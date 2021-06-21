/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:52:33 by sushin            #+#    #+#             */
/*   Updated: 2021/06/21 10:14:52 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void		set_pwd(t_list *env)
{
	while (env)
	{
		if (!(ft_strncmp(((t_env *)env->content)->key, "PWD", 4)))
		{
			free(((t_env *)env->content)->value);
			((t_env *)env->content)->value = getcwd(0, 1024);
			break ;
		}
		env = env->next;
	}
	return ;
}

char		*get_oldpwd(t_list *env)
{
	char	*value;

	value = NULL;
	while (env)
	{
		if (ft_strncmp(((t_env *)env->content)->key, "OLDPWD", 7) == 0)
		{
			value = ft_strdup(((t_env *)env->content)->value);
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
	{
		print_err_msg("cd", "OLDPWD");
		ft_putstr_fd("not set\n", 2);
	}
	return (value);
}

int			set_oldpwd(t_list *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (1);
	while (env)
	{
		if (!(ft_strncmp(((t_env *)env->content)->key, "OLDPWD", 7)))
		{
			free(((t_env *)env->content)->value);
			((t_env *)env->content)->value = getcwd(0, 1024);
			free(new);
			return (0);
		}
		env = env->next;
	}
	new->key = ft_strdup("OLDPWD");
	new->value = getcwd(0, 1024);
	ft_lstadd_back(&env, ft_lstnew(new));
	return (0);
}

void		reset_oldpwd(t_list *env, char *buf)
{
	while (env)
	{
		if (ft_strncmp(((t_env *)env->content)->key, "OLDPWD", 7) == 0)
		{
			free(((t_env *)env->content)->value);
			((t_env *)env->content)->value = buf;
			break ;
		}
		env = env->next;
	}
	return ;
}
