/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 14:10:38 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/14 17:42:02 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_pipecmd(char *cmd, int fd_entry, int fd_exit)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		ft_puts_error("Fork error\n");
	else if (pid == 0)
	{
		dup2(fd_entry, 0);
		dup2(fd_exit, 1);
		close(fd_entry);
		close(fd_exit);
		ft_execmd(cmd);
		exit(1);
	}
	else
		close(fd_exit);
}

void	ft_printcmd(int pfd[])
{
	int		ret;
	char	buf[BUF_SIZE];
	char	*toprint;

	ret = read(pfd[0], buf, BUF_SIZE);
	while (ret)
	{
		toprint = ft_strndup(buf, ret);
		ft_putstr(toprint);
		free(toprint);
		if (ret < BUF_SIZE)
			ret = 0;
		else
			ret = read(pfd[0], buf, BUF_SIZE);
	}
}

int		ft_pipeentry(char *cmd, int fd_entry)
{
	int		pfd3[2];

	if (pipe(pfd3) == -1)
		ft_puts_error("ft_minishell: Pipe error\n");
	ft_pipecmd(cmd, fd_entry, pfd3[1]);
	close(fd_entry);
	close(pfd3[1]);
	return (pfd3[0]);
}

int		ft_selectcmd(char *cmd, int fd_entry)
{
	int		fd;

	if (fd_entry != -1)
	{
		if (ft_cmdcontaincar(cmd, '<'))
			return (fd = ft_execinfiled(cmd));
		else if (ft_cmdcontaincar(cmd, '>'))
			ft_execwrite(cmd, fd_entry);
		else
			return (ft_pipeentry(cmd, fd_entry));
	}
	return (-1);
}

int		ft_execpipe(char *cmd)
{
	int		j;
	int		pfd[2];
	int		fd_entry;
	char	**table;

	j = 1;
	table = ft_strsplit(cmd, '|');
	if (pipe(pfd) == -1)
		ft_puts_error("ft_minishell: Pipe Error\n");
	if (ft_cmdcontaincar(table[0], '<'))
		fd_entry = ft_execinfiled(table[0]);
	else
	{
		ft_pipecmd(table[0], 0, pfd[1]);
		close(pfd[1]);
		fd_entry = pfd[0];
	}
	while (table[j] != NULL)
	{
		fd_entry = ft_selectcmd(table[j], fd_entry);
		j++;
	}
	ft_freetable(table);
	return (fd_entry);
}
