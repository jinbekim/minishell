/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_non_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:08 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:33:39 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	free_envp_in_err(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void		exe_non_builtin(char **argv, t_list *env)
{
	int		err;
	char	*path_cmd;
	char	**envp;

	envp = convert_to_envp(env);
	if (argv[0][0] != '.' && argv[0][0] != '/')
	{
		path_cmd = search_path(argv, envp);
		err = execve(path_cmd, argv, envp);
		print_err_msg(argv[0], NULL);
		ft_putstr_fd("command not found\n", 2);
	}
	else
	{
		err = execve(argv[0], argv, envp);
		print_err_msg(argv[0], NULL);
		print_errno();
	}
	free_envp_in_err(envp);
	exit(127);
}
