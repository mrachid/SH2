/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 11:16:25 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/16 19:05:55 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		recup_user(char **env, char *target)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(target);
	while (env[i])
	{
		if (ft_strncmp(target, env[i], len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	prompt(char **env)
{
	int		i;
	char	**name;

	i = recup_user(env, "USER");
	if (i != -1)
	{
		name = ft_strsplit(env[i], '=');
		if (name[1] != NULL)
		{
			BLUE;
			ft_putstr(name[1]);
			CANCEL;
			GREEN;
			write(1, " ~> ", ft_strlen(" ~> "));
			CANCEL;
			return ;
		}
	}
}

char	*ft_replacetab(char *s1)
{
	int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '\t')
			s1[i] = ' ';
		i++;
	}
	return (s1);
}

void	ft_freetable(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != (void*)0)
	{
		free(tab[i]);
		i++;
	}
}

char	*ft_strndup(char const *s1, size_t n)
{
	char	*str;

	str = (char*)malloc(sizeof(str) * n);
	if (str)
		ft_strncpy(str, s1, n);
	return (str);
}
