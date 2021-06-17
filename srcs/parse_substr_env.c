/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_substr_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:42 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/17 10:37:05 by jinbekim         ###   ########.fr       */
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
		if (ft_strcmp(((t_env *)env->content)->key, key) == 0)
		{
			free(key);
			value = ft_strdup(((t_env *)env->content)->value);
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
	{
		free(key);
		value = ft_strdup("");
	}
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
		return (ft_itoa(g_exitcode));
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

static void	init_var(int *i, int *start, char *sing, char **cmd)
{
	*i = 0;
	*start = 0;
	*sing = 0;
	*cmd = NULL;
}

char		*substitution_env_var(char *cmd, t_list *env)
{
	char	single_quote;
	char	*new_cmd;
	int		i;
	int		start;

	init_var(&i, &start, &single_quote, &new_cmd);
	while (cmd[i])
	{
		if (cmd[i] == '\'' && single_quote == 0\
		&& (i == 0 || cmd[i - 1] != ESCAPE))
			single_quote = 1;
		else if (cmd[i] == '\'' && single_quote == 1)
			single_quote = 0;
		else if (single_quote == 0 && cmd[i] == '$'\
		&& (i == 0 || cmd[i - 1] != ESCAPE))
		{
			new_cmd = make_tmp(cmd, new_cmd, start, &i);
			new_cmd = ft_join_both_free(new_cmd, substr_env(cmd, env, &i));
			start = i;
		}
		i++;
	}
	return (new_cmd = make_tmp(cmd, new_cmd, start, &i));
}
