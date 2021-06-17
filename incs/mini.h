/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:54:57 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/17 09:53:45 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# define ESCAPE 24

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include "get_next_line.h"

# ifndef MAIN

extern int		g_exitcode;
# endif

typedef enum	e_bool{
	FALSE,
	TRUE
}				t_bool;

typedef enum	e_separator{
	e_null = 0,
	e_semicolon = 59,
	e_pipe = 124
}				t_separator;
typedef enum	e_builtin{
	non_b = 0,
	b_cd,
	b_echo,
	b_env,
	b_exit,
	b_export,
	b_pwd,
	b_unset
}				t_builtin;
typedef struct	s_env{
	char		*key;
	char		*value;
}				t_env;
typedef struct	s_cmd{
	char		*cmd;
	t_separator	end;
	int			read_fd;
	int			write_fd;
}				t_cmd;

/*
** init_shell
*/
t_cmd			*ft_newcmd(char *line, int i, int j);
void			clear_cmd(t_list *cmd);

/*
** Part. parsing
*/
void			parse_env_list(char **envp, t_list **env);
t_list			*parse_fail(t_list *cmd);
t_list			*parse_cmd(char *line, t_list *cmd);
t_list			*parse_cmd2(char *cmd, t_list *env);
char			*ft_separate(char *cmd, t_list *env, int *i);
char			**convert_to_argv(t_list *tmp);
char			**convert_to_envp(t_list *tmp);
char			*substr_env(char *cmd, t_list *env, int *i);
char			*make_tmp(char *cmd, char *tmp, int start, int *i);
char			*ft_join_both_free(char *tmp1, char *tmp2);
char			*ft_getenv(char *key, t_list *env);
char			*substr_normal(char *cmd, t_list *env, int *i);
char			*substr_quote_double(char *cmd, t_list *env, int *i);
char			*substr_quote_single(char *cmd, t_list *env, int *i);
char			*substr_redirect(char *cmd, t_list *env, int *i);
char			*substitution_env_var(char *cmd, t_list *env);

/*
** Part. executer
*/
void			execute_cmd(t_list *cmd, t_list *env);
void			execute_cmd2(t_cmd *cmd, t_list *env);
void			execute_cmd3(t_list *tmp, t_list *env, int i_am_child);
void			exe_non_builtin(char **argv, t_list *env);
char			*search_path(char **argv, char **envp);
void			exe_builtin(char **argv, t_list *env);
int				is_builtin(char *cmd);

/*
** Part. err_handle
*/
void			print_err_msg(char *cmd, char *arg);
void			print_errno(void);
void			print_errno_exit(int status);

/*
** Part. pipe
*/
void			wait_childs(int pid[10]);
void			wait_child(int pid);

/*
** Part. built_in function
*/
int				bt_cd(char *argv[], t_list *env);
int				bt_echo(char *argv[]);
int				bt_env(t_list *env);
int				bt_exit(char *argv[]);
int				bt_pwd(void);
int				bt_unset(char *argv[], t_list *env);
void			unset_by_export(char *str, t_list *env);

/*
**Part. built_in function
*/
int				bt_cd(char *argv[], t_list *env);
int				bt_echo(char *argv[]);
int				bt_env(t_list *env);
int				bt_exit(char *argv[]);
int				bt_pwd(void);
int				bt_unset(char *argv[], t_list *env);
void			unset_by_export(char *str, t_list *env);

/*
** export
*/
int				bt_export(char *argv[], t_list *env);
int				is_exist_env(char *str, t_list *env);
void			no_equal_sign_export(char *str, t_list *env);
void			yes_equal_sign_export(char *str, t_list *env);
void			sort_argv(char **tmp_key, int count);

/*
** pwd_set
*/
void			reset_oldpwd(t_list *env, char *buf);
int				set_oldpwd(t_list *env);
char			*get_oldpwd(t_list *env);
void			set_pwd(t_list *env);

#endif
