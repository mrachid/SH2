/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_symbols.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:04:14 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/14 18:31:26 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_issymbol(int c)
{
	int		i;
	int		is;

	i = 0;
	is = 0;
	while (i < 4 && is == 0)
	{
		if (c == SYMBOL[i])
			is = 1;
		i++;
	}
	return (is);
}

int		ft_checksymbolcmd(char *cmd)
{
	unsigned int	i;
	int				isok;

	i = 0;
	isok = 1;
	while (cmd[i] != '\0' && isok == 1)
	{
		if (ft_issymbol(cmd[i]) && cmd[i + 1] != '\0')
		{
			if ((ft_issymbol(cmd[i + 1]) || ft_issymbol(cmd[i + 2]))
				&& !(cmd[i] == '>' && cmd[i + 1] == '>'))
			{
				ft_puts_error("ft_minishell: syntax error near '\n");
				if (ft_issymbol(cmd[i + 1]))
					ft_putch_error(cmd[i + 1]);
				else
					ft_putch_error(cmd[i + 2]);
				ft_putch_error('\n');
				isok = 0;
			}
		}
		i++;
	}
	return (isok);
}

int		ft_cmdcontaincar(char *cmd, char c)
{
	int		i;
	int		find;

	i = 0;
	find = 0;
	while (cmd[i] != '\0' && find == 0)
	{
		if (cmd[i] == c)
			find = 1;
		i++;
	}
	return (find);
}

int		ft_syntaxchecked(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i] != '\0' && cmd[i] == ' ')
		i++;
	if (cmd[i] == '|')
	{
		ft_puts_error("ft_minishell: syntax error near '|'\n");
		*cmd = '\0';
		return (0);
	}
	return (1);
}
