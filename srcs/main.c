/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:32 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/17 10:45:01 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAIN
#include "mini.h"

int	g_exitcode = 0;
/*
** 0. main.c
** shell name : cash;
** 1. make list of environment valiable.
** 	1-1. hook signal and manage.
** 	1-2. if subshell error exit, change $? value.
** 2. printf prompt.
** 3. loop to get_next_line infinitely til ^D.
** 4. execute cmd.
** 	4-1. parse
** 	4-2. if not need fork, execute.
** 5. printf prompt again.
** 6. repeat from step #3.
*/

static void	clear_shell(t_list *cmd, char *line, int std[2])
{
	set_input_termios();
	clear_cmd(cmd);
	free(line);
	if (dup2(std[1], 1) == -1)
		print_errno_exit(1);
	if (dup2(std[0], 0) == -1)
		print_errno_exit(1);
	write(1, "cash$ ", 7);
}

static void	init_shell(t_list **env, char **envp, int (*std)[2])
{
	set_initial_termios();
	set_input_termios();
	handle_signal();
	parse_env_list(envp, env);
	(*std)[0] = dup(0);
	(*std)[1] = dup(1);
	if ((*std)[0] == -1 || (*std)[1] == -1)
		print_errno_exit(1);
	write(1, "cash$ ", 7);
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*env;
	t_list	*cmd;
	int		std[2];

	if (argc == 0 && argv == 0)
		return (1);
	init_shell(&env, envp, &std);
	while (get_next_line(0, &line) > 0)
	{
		set_initial_termios();
		cmd = parse_cmd(line, cmd);
		if ((cmd == NULL && line[0] != '\0' && ft_isblank(line[0]) == 0)
		|| (ft_lstsize(cmd) > 9))
		{
			g_exitcode = 258;
			printf("syntax error\n");
		}
		else
			execute_cmd(cmd, env);
		clear_shell(cmd, line, std);
	}
	set_initial_termios();
	printf("exit\n");
	return (0);
}
