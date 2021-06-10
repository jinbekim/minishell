/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:03:54 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:28:28 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static t_builtin	builtin_switch(char *cmd)
{
	t_builtin		name;

	if (ft_strncmp(cmd, "cd", 3) == 0)
		name = b_cd;
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		name = b_echo;
	else if (ft_strncmp(cmd, "env", 4) == 0)
		name = b_env;
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		name = b_exit;
	else if (ft_strncmp(cmd, "export", 7) == 0)
		name = b_export;
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		name = b_pwd;
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		name = b_unset;
	else
		name = non_b;
	return (name);
}

int					is_builtin(char *cmd)
{
	return (builtin_switch(cmd));
}

void				exe_builtin(char **argv, t_list *env)
{
	t_builtin		name;

	name = builtin_switch(argv[0]);
	if (name == b_cd)
		bt_cd(argv, env);
	else if (name == b_echo)
		bt_echo(argv);
	else if (name == b_env)
		bt_env(env);
	else if (name == b_exit)
		bt_exit(argv);
	else if (name == b_export)
		bt_export(argv, env);
	else if (name == b_pwd)
		bt_pwd();
	else if (name == b_unset)
		bt_unset(argv, env);
}
