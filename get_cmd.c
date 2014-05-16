/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 22:44:31 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/14 17:57:26 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*get_new_cmd(char *cmd)
{
	int		ret;
	char	buf[BUF_SIZE];
	char	*cmd2;

	write(1, "> ", 2);
	ret = 0;
	ret = read(0, buf, BUF_SIZE);
	while (buf[0] == '\n')
	{
		write(1, "> ", 2);
		ret = read(0, buf, BUF_SIZE);
	}
	cmd2 = (char*)malloc(sizeof(cmd2) * (ret + 1 + ft_strlen(cmd)));
	if (cmd2)
	{
		ft_strcpy(cmd2, cmd);
		ft_strncat(cmd2, buf, ret - 1);
	}
	return (cmd2);
}

int		verif_cmd(char *cmd)
{
	unsigned int	i;
	int				verif;

	verif = 1;
	i = ft_strlen(cmd);
	while (cmd[i - 1] == ' ' && i > 1)
	{
		cmd[i - 1] = '\0';
		i--;
	}
	if (i > 0)
	{
		if (cmd[i - 1] == '|' || cmd[i - 1] == '\\')
		{
			if (cmd[i - 1] == '\\')
				cmd[i - 1] = '\0';
			verif = 0;
		}
	}
	return (verif);
}
