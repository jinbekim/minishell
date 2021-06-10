/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_substr_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:42 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:27:18 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_is_env_element(char chr)
{
	if (ft_isalnum(chr) || chr == '_')
		return (1);
	return (0);
}

/*
** 0. substr_env
** 1. $env_var must end with dq, sq, space, redirect, or null
** 2. find the var in list.
** 3. if dont have return empty str
** 4. else return env value.
*/

char		*ft_getenv(char *key, t_list *env)
{
	char	*value;

	value = NULL;
	while (env)
	{
		if (ft_strncmp(((t_env *)env->content)->key, key, ft_strlen(key)) == 0)
		{
			free(key);
			value = ft_strdup(((t_env *)env->content)->value);
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
		value = ft_strdup("");
	return (value);
}

char		*substr_env(char *cmd, t_list *env, int *i)
{
	char	*env_key;
	char	*env_value;
	int		start;

	start = ++(*i);
	if (cmd[start] == '?')
	{
		(*i)++;
		return (ft_strdup(ft_itoa(g_exitcode)));
	}
	if (ft_isdigit(cmd[start]))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	while (ft_is_env_element(cmd[*i]))
		(*i)++;
	if (start == (*i))
		return (ft_strdup("$"));
	env_key = ft_substr(cmd, start, (*i) - start);
	env_value = ft_getenv(env_key, env);
	return (env_value);
}
