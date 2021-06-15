/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:05:06 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/15 16:26:07 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*separate_value(char *str)
{
	char	*value;
	int		start;

	start = 0;
	while (str[start] != '=')
		start++;
	value = ft_strdup(&str[start + 1]);
	return (value);
}

static char	*separate_key(char *str)
{
	char	*key;
	int		i;
	int		start;

	start = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			key = ft_substr(str, start, i);
			return (key);
		}
		i++;
	}
	return (0);
}

void		add_env(char *str, char *newkey, t_list *env)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		exit(1);
	new->key = newkey;
	new->value = separate_value(str);
	ft_lstadd_back(&env, ft_lstnew(new));
}

void		no_equal_sign_export(char *str, t_list *env)
{
	t_env *new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		exit(1);
	if (is_exist_env(str, env))
	{
		free(new);
		return ;
	}
	new->key = ft_strdup(str);
	new->value = NULL;
	ft_lstadd_back(&env, ft_lstnew(new));
}

void		yes_equal_sign_export(char *str, t_list *env)
{
	char *new_key;

	new_key = separate_key(str);
	if (is_exist_env(new_key, env))
	{
		unset_by_export(new_key, env);
		add_env(str, new_key, env);
	}
	else
		add_env(str, new_key, env);
	return ;
}
