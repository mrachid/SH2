/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 17:46:00 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/14 23:22:08 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_execinfiled(char *cmd)
{
	int		fd;
	char	**table;
	int		pfd[2];

	table = ft_strsplit(cmd, '<');
	if (table[1] != NULL)
	{
		if ((fd = open(ft_strtrim(table[1]), O_RDWR)) == -1)
			return (ft_puts_error("ft_minishell: Error opening file\n"));
		if (pipe(pfd) == -1)
			ft_puts_error("Pipe Error\n");
		ft_pipecmd(table[0], fd, pfd[1]);
		ft_freetable(table);
		if (close(fd) == -1)
			return (ft_puts_error("ft_minishell: Error closing file\n"));
		return (pfd[0]);
	}
	else
		return (ft_puts_error("ft_minishell: syntax error near 'newline'\n"));
	return (-1);
}

int		ft_isdouble(char const *s1, char c)
{
	int		i;
	int		db;

	i = 0;
	db = 0;
	while (s1[i] != '\0' && db == 0)
	{
		if (s1[i + 1] != '\0')
		{
			if (s1[i] == c && s1[i + 1] == c)
				db = 1;
		}
		i++;
	}
	return (db);
}

void	ft_execwrite(char *cmd, int fd_entry)
{
	char	**table;
	int		pfd[2];

	table = ft_strsplit(cmd, '>');
	if (table[1] != NULL)
	{
		if (pipe(pfd) == -1)
			ft_puts_error("Pipe Error\n");
		ft_pipecmd(table[0], fd_entry, pfd[1]);
		if (ft_isdouble(cmd, '>'))
			ft_appendfile(ft_strtrim(table[1]), pfd[0]);
		else
			ft_writefile(ft_strtrim(table[1]), pfd[0]);
	}
	else
		ft_puts_error("ft_minishell: syntax error near 'newline'\n");
	ft_freetable(table);
}

int		ft_writefile(char *name, int fdf)
{
	int		fd;
	int		ret;
	char	buf[BUF_SIZE];
	char	*toprint;

	fd = creat(name, S_IRWXU);
	if (fd == -1)
		return (ft_puts_error("Error creating file\n"));
	ret = read(fdf, buf, BUF_SIZE);
	while (ret)
	{
		toprint = ft_strndup(buf, ret);
		ft_putstr_fd(toprint, fd);
		if (ret < BUF_SIZE)
			ret = 0;
		else
			ret = read(fdf, buf, BUF_SIZE);
	}
	if (close(fd) == -1)
		return (ft_puts_error("Error closing file\n"));
	return (1);
}

int		ft_appendfile(char *name, int fdf)
{
	int		fd;
	int		ret;
	char	buf[BUF_SIZE];
	char	*toprint;

	fd = open(name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd == -1)
		return (ft_puts_error("Error creating file\n"));
	ret = read(fdf, buf, BUF_SIZE);
	while (ret)
	{
		toprint = ft_strndup(buf, ret);
		ft_putstr_fd(toprint, fd);
		if (ret < BUF_SIZE)
			ret = 0;
		else
			ret = read(fdf, buf, BUF_SIZE);
	}
	if (close(fd) == -1)
		return (ft_puts_error("Error closing file\n"));
	return (1);
}
