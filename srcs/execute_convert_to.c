/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_convert_to.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:06 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/11 21:19:33 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*refine_str(char *str)
{
	int		i;
	int		j;
	char	*argv;

	i = 0;
	j = 0;
	argv = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (argv == NULL)
		print_errno_exit(1);
	while (str[j])
	{
		if (str[j] == ESCAPE)
			j++;
		argv[i] = str[j];
		i++;
		j++;
	}
	argv[i] = str[j];
	free(str);
	return (argv);
}

char		**convert_to_argv(t_list *tmp)
{
	char	**argv;
	t_list	*tmp2;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(tmp);
	argv = malloc(sizeof(char *) * (size + 1));
	if (argv == NULL)
		return (NULL);
	argv[size] = NULL;
	while (tmp)
	{
		argv[i] = refine_str(tmp->content);
		tmp->content = NULL;
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
		i++;
	}
	return (argv);
}

char		**convert_to_envp(t_list *tmp)
{
	char	**envp;
	char	*tmp_str;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(tmp);
	envp = malloc(sizeof(char *) * (size + 1));
	if (envp == NULL)
		return (NULL);
	while (tmp)
	{
		if (((t_env *)tmp->content)->value)
		{
			tmp_str = ft_strjoin(((t_env *)tmp->content)->key, "=");
			envp[i] = ft_strjoin(tmp_str, ((t_env *)tmp->content)->value);
			free(tmp_str);
			i++;
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
