/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:26:52 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/14 14:15:17 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_initsignal(void)
{
	signal(SIGQUIT, ft_sighandler);
	signal(SIGINT, ft_sighandler);
	signal(SIGCONT, ft_sighandler);
}

void	ft_sighandler(int sig)
{
	if (sig == SIGQUIT || sig == SIGINT)
	{
		write(2, "\n", 1);
		exit(0);
	}
	if (sig == SIGCONT)
	{
		write(2, "Exit for security\n", 20);
		exit(0);
	}
}
