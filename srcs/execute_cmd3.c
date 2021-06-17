/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:04 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/17 11:16:38 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	exit_process(int i_am_child)
{
	if (i_am_child == 0)
		return ;
	if (!g_exitcode)
		exit(0);
	else if (g_exitcode)
		exit(g_exitcode);
}

static void	free_argv(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

static void	fork_exe_non_builtin(char **argv, t_list *env, int *i_am_child)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		print_errno();
	else if (pid == 0)
	{
		*i_am_child = 1;
		exe_non_builtin(argv, env);
	}
	else
		wait_child(pid);
}

void		execute_cmd3(t_list *tmp, t_list *env, int i_am_child)
{
	char	**argv;

	argv = convert_to_argv(tmp);
	if (argv == NULL)
		print_errno_exit(1);
	if (is_builtin(argv[0]))
		exe_builtin(argv, env);
	else if (i_am_child)
		exe_non_builtin(argv, env);
	else
		fork_exe_non_builtin(argv, env, &i_am_child);
	free_argv(argv);
	exit_process(i_am_child);
}
