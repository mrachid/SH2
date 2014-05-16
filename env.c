/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 19:03:43 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/14 19:01:12 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**act_env;

char	*get_key(char *key)
{
	int		i;
	int		find;
	char	*path;

	i = 0;
	find = 0;
	path = NULL;
	while (act_env[i] != (void*)0 && find == 0)
	{
		if (is_key(act_env[i], key))
		{
			path = act_env[i];
			path = path + ft_strlen(key) + 1;
			find = 1;
		}
		i++;
	}
	if (find == 0)
		ft_putendl_fd("ft_minishell: Warning: PATH UNDEFINED\n", 2);
	return (path);
}

void	ft_exeinenv(char **arg)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	execve(arg[0], arg, act_env);
	path = get_key("PATH");
	paths = ft_strsplit(path, ':');
	while (paths[i] != (void*)0)
	{
		execve(ft_topath(arg[0], paths[i]), arg, act_env);
		i++;
	}
	if (errno == EACCES)
	{
		RED;
		ft_putendl_fd("ft_minishell1: ", 2);
		ft_putendl_fd(arg[0], 2);
		ft_putendl_fd(" permission denied", 2);
		CANCEL;
	}
}

char	**get_env(void)
{
	return (act_env);
}

void	ft_setmyenv(char **newenv, char **oldenv)
{
	free(oldenv);
	act_env = newenv;
}

void	ft_saveenv(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	if (act_env == (void*)0)
		act_env = (char**)malloc(sizeof(act_env) * (ft_tablelen(env) + 1));
	while (env[i] != (void*)0)
	{
		tmp = (char*)malloc(sizeof(tmp) * ft_strlen(env[i]));
		ft_strcpy(tmp, env[i]);
		act_env[i] = tmp;
		i++;
	}
	act_env[i] = (void*)0;
}
