/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:05:19 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/21 10:14:52 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	cd_option_check(t_list *env, t_list *init_env)
{
	if (!(ft_strncmp(((t_env *)env->content)->key, "HOME", 5)))
	{
		set_oldpwd(init_env);
		chdir(((t_env *)env->content)->value);
		set_pwd(init_env);
	}
}

static void	cd_option_check2(t_list *env)
{
	char	*buf;

	buf = get_oldpwd(env);
	set_oldpwd(env);
	chdir(buf);
	free(buf);
	set_pwd(env);
}

static int	cd_option_check3(char *buf, char *str, t_list *env)
{
	if ((chdir(str) == -1))
	{
		print_err_msg("cd", str);
		ft_putstr_fd("No such file or directory\n", 2);
		reset_oldpwd(env, buf);
		g_exitcode = 1;
		return (1);
	}
	return (0);
}

int			bt_cd(char *argv[], t_list *env)
{
	char	*buf;
	t_list	*init_env;

	init_env = env;
	if (argv[1] == NULL || !(ft_strncmp(argv[1], "~", ft_strlen(argv[1]) + 1)))
	{
		while (env)
		{
			cd_option_check(env, init_env);
			env = env->next;
		}
	}
	else if (!(ft_strncmp(argv[1], "-", ft_strlen(argv[1]) + 1)))
		cd_option_check2(env);
	else
	{
		buf = get_oldpwd(env);
		set_oldpwd(env);
		if ((cd_option_check3(buf, argv[1], env)))
			return (1);
		free(buf);
		set_pwd(env);
	}
	g_exitcode = 0;
	return (0);
}
