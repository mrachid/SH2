/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 14:18:59 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/14 17:49:42 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		check_cmd(char **arg)
{
	if (*arg == (void*)0)
		return (0);
	else if (ft_strcmp(arg[0], "exit") == 0)
		exit(1);
	else if (ft_strcmp(arg[0], "env") == 0)
		return (print_env());
	else if (ft_strcmp(arg[0], "cd") == 0)
		return (ft_cd(arg[1]));
	else if (ft_strcmp(arg[0], "unsetenv") == 0)
		return (ft_unsetenv(arg[1]));
	else if (ft_strcmp(arg[0], "setenv") == 0)
		return (ft_setenv(arg[1], arg[2], arg[3]));
	return (1);
}

void	ft_execmd(char const *cmd)
{
	pid_t		pid;
	char		**arg;

	arg = ft_strsplit(cmd, ' ');
	if (check_cmd(arg))
	{
		pid = fork();
		if (pid == 0)
		{
			ft_exeinenv(arg);
			RED;
			ft_putstr_fd("ft_minishell2: ", 2);
			ft_putstr_fd(arg[0], 2);
			ft_putendl_fd(": command not found", 2);
			CANCEL;
			_exit(1);
		}
		else if (pid < 0)
			ft_putendl_fd("Fork Error", 2);
		else
		{
			waitpid(pid, 0, 0);
			ft_freetable(arg);
		}
	}
}

int		choose_cmd(char *cmd)
{
	int		fd;

	if (ft_cmdcontaincar(cmd, '|'))
	{
		if ((fd = ft_execpipe(cmd)) != -1)
			ft_printfd(fd);
		close(fd);
	}
	else if (ft_cmdcontaincar(cmd, '<') && ft_cmdcontaincar(cmd, '>'))
		ft_execmultired(cmd);
	else if (ft_cmdcontaincar(cmd, '<'))
	{
		if ((fd = ft_execinfiled(cmd)) != -1)
			ft_printfd(fd);
		close(fd);
	}
	else if (ft_cmdcontaincar(cmd, '>'))
		ft_execwrite(cmd, 0);
	else
		ft_execmd(cmd);
	return (-1);
}

int		exec_shell(char **env)
{
	int		ret;
	char	buf[BUF_SIZE];
	char	*cmd;
	char	**list_cmd;
	int		i;

	i = 0;
	prompt(env);
	ret = read(0, buf, BUF_SIZE);
	if (ret == 0 || buf[0] == '\n')
		return (0);
	cmd = (char*)malloc(sizeof(cmd) * (ret + 1));
	if (cmd)
		ft_strncpy(cmd, buf, ret - 1);
	while (ft_syntaxchecked(cmd) && !verif_cmd(cmd))
		cmd = get_new_cmd(cmd);
	list_cmd = ft_strsplit(ft_replacetab(cmd), ';');
	while (list_cmd[i] != NULL && ft_checksymbolcmd(cmd))
	{
		choose_cmd(list_cmd[i]);
		i++;
	}
	free(cmd);
	ft_freetable(list_cmd);
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	if (argc > 1)
		argv++;
	ft_saveenv(env);
	ft_initsignal();
	while (1)
		exec_shell(env);
	return (0);
}
