/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_for_minishell2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:17 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:29:02 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			has_newline(char *backup)
{
	int		i;

	i = 0;
	if (!backup)
		return (-1);
	while (backup[i])
	{
		if (backup[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void		cut_with_newline(char **backup)
{
	int		i;
	char	*tmp;

	tmp = *backup;
	i = 0;
	while ((*backup)[i] != '\n')
		i++;
	(*backup)[i] = '\0';
	if (ft_strlen(&(*backup)[i + 1]) > 0)
		*backup = ft_strdup(&(*backup)[i + 1]);
	else
		*backup = NULL;
	free(tmp);
}

char		*ft_strjoin_free(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*arr;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	arr = malloc(len1 + len2 + 1);
	if (arr == NULL)
		return (0);
	while (s1[i])
	{
		arr[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		arr[len1 + i] = s2[i];
		i++;
	}
	arr[len1 + i] = 0;
	free(s1);
	return (arr);
}
