/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:05:04 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/14 20:22:22 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*check_value(char *str, t_list *env)
{
	char	*tmp;

	tmp = NULL;
	while (env)
	{
		if (!(ft_strncmp(((t_env *)env->content)->key, str, 50)))
		{
			tmp = ((t_env *)env->content)->value;
			if (tmp != NULL)
			{
				return (((t_env *)env->content)->value);
			}
			else
			{
				return (0);
			}
		}
		env = env->next;
	}
	return (NULL);
}

static void	set_export_list(char **tmp_key, t_list *env)
{
	int		i;
	char	*value;

	i = 0;
	while (tmp_key[i])
	{
		value = check_value(tmp_key[i], env);
		if (value)
			printf("declare -x %s=\"%s\"\n", tmp_key[i], value);
		else
			printf("declare -x %s\n", tmp_key[i]);
		i++;
	}
}

static int	show_export(t_list *env)
{
	char	**tmp_key;
	int		i;
	t_list	*init_env;

	init_env = env;
	if (!(tmp_key = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1))))
		return (-1);
	i = 0;
	while (env)
	{
		tmp_key[i] = ft_strdup(((t_env *)env->content)->key);
		env = env->next;
		i++;
	}
	tmp_key[i] = NULL;
	sort_argv(tmp_key, (i - 1));
	set_export_list(tmp_key, init_env);
	i = 0;
	while (tmp_key[i])
	{
		free(tmp_key[i]);
		i++;
	}
	free(tmp_key);
	return (0);
}

static int	check_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
		{
			print_err_msg(str, NULL);
			ft_putstr_fd("not a valid identifier\n", 2);
			return (1);
		}
	}
	return (0);
}

int			bt_export(char *argv[], t_list *env)
{
	int	i;

	if (argv[1] == NULL)
		return (show_export(env));
	i = 1;
	while (argv[i])
	{
		if (ft_isdigit(argv[i][0]) || argv[i][0] == '=')
		{
			print_err_msg(argv[i], NULL);
			ft_putstr_fd("not a valid identifier\n", 2);
			return (g_exitcode = 1);
		}
		else if (check_alnum(argv[i]))
			return (g_exitcode = 1);
		if (ft_strchr(argv[i], '='))
			yes_equal_sign_export(argv[i], env);
		else
			no_equal_sign_export(argv[i], env);
		i++;
	}
	return (g_exitcode = 0);
}
