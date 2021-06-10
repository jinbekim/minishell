/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_non_builtin2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:10 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:32:29 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char			**find_path_env(char **envp)
{
	char			*key;
	char			**path_list;
	int				i;

	i = 0;
	key = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			key = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
		i++;
	}
	if (key == NULL)
		return (NULL);
	path_list = ft_split(key, ':');
	return (path_list);
}

static int			search_dir(char *dir_name, char *exe_name)
{
	DIR				*dir_ptr;
	struct dirent	*read;

	if (dir_name == NULL)
		return (-1);
	dir_ptr = opendir(dir_name);
	if (dir_ptr == NULL)
		return (0);
	read = readdir(dir_ptr);
	while (read)
	{
		if (ft_strncmp(read->d_name, exe_name, ft_strlen(exe_name) + 1) == 0)
		{
			closedir(dir_ptr);
			return (1);
		}
		read = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	return (0);
}

static char			*make_cmd(char **argv, char **path_list)
{
	int				i;
	char			*tmp;
	char			*cmd;

	i = 0;
	cmd = NULL;
	while (search_dir(path_list[i], argv[0]) == 0)
		i++;
	if (path_list[i] == NULL)
		return (cmd);
	tmp = ft_strjoin(path_list[i], "/");
	cmd = ft_strjoin(tmp, argv[0]);
	free(tmp);
	return (cmd);
}

static void			free_path_list(char **path_list)
{
	int				i;

	i = -1;
	while (path_list[++i])
		free(path_list[i]);
	free(path_list);
}

char				*search_path(char **argv, char **envp)
{
	char			*cmd;
	char			**path_list;

	path_list = find_path_env(envp);
	if (path_list == NULL)
		return (NULL);
	cmd = make_cmd(argv, path_list);
	free_path_list(path_list);
	return (cmd);
}
