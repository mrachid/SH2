/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 13:46:55 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/14 23:19:24 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		is_key(char const *s1, char const *key)
{
	char	*mem;

	mem = (char*)malloc(sizeof(mem) * 5);
	ft_strncpy(mem, s1, ft_strlen(key));
	if (ft_strcmp(mem, key) == 0)
		return (1);
	return (0);
}

char	*ft_topath(char *cmd, char *path)
{
	char	*val;

	val = (char*)malloc(sizeof(val) * (ft_strlen(cmd) + ft_strlen(path) + 2));
	ft_strcpy(val, path);
	ft_strncat(val, "/", 1);
	ft_strncat(val, cmd, ft_strlen(cmd));
	return (val);
}

int		ft_tablelen(char **env)
{
	int		i;

	i = 0;
	while (env[i] != (void*)0)
		i++;
	return (i);
}
