/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:05:42 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/14 17:55:55 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_printfd(int fd)
{
	int		ret;
	char	buf[BUF_SIZE];
	char	*toprint;

	ret = read(fd, buf, BUF_SIZE);
	while (ret)
	{
		toprint = ft_strndup(buf, ret);
		ft_putstr(toprint);
		free(toprint);
		if (ret < BUF_SIZE)
			ret = 0;
		else
			ret = read(fd, buf, BUF_SIZE);
	}
}

void	ft_execmultired(char *cmd)
{
	char	**table;
	int		fd_entry;

	table = ft_strsplit(cmd, '>');
	fd_entry = ft_execinfiled(table[0]);
	if (ft_isdouble(cmd, '>'))
		ft_appendfile(ft_strtrim(table[1]), fd_entry);
	else
		ft_writefile(ft_strtrim(table[1]), fd_entry);
}
