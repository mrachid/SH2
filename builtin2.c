/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 16:37:32 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/14 18:12:32 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	add_env(char const *name, char const *value)
{
	int		i;
	int		len;
	char	**env;
	char	**newenv;

	i = 0;
	env = get_env();
	len = ft_tablelen(env);
	newenv = (char**)malloc(sizeof(newenv) * (len + 2));
	while (env[i] != (void*)0)
	{
		newenv[i] = env[i];
		i++;
	}
	newenv[i] = get_new_var_env(name, value, (void*)0);
	newenv[i + 1] = (void*)0;
	ft_setmyenv(newenv, env);
}

int		del_env(char **tmpenv, char **newenv, char const *name)
{
	int		i;
	int		j;
	int		find;

	i = 0;
	j = 0;
	find = 0;
	while (tmpenv[i] != (void*)0)
	{
		if (!is_key(tmpenv[i], name))
		{
			newenv[j] = tmpenv[i];
			j++;
		}
		else
		{
			find = 1;
			free(tmpenv[i]);
		}
		i++;
	}
	return (find);
}

char	*get_new_var_env(char const *name, char const *value, char *tmpenv)
{
	char	*tmp;

	tmp = (char*)malloc(sizeof(tmp) * (ft_strlen(name) + ft_strlen(value) + 2));
	if (tmp)
	{
		ft_strcpy(tmp, name);
		ft_strncat(tmp, "=", 1);
		ft_strncat(tmp, value, ft_strlen(value));
	}
	if (tmpenv)
		free(tmpenv);
	return (tmp);
}

char	*cd_tild(char *p, char const *h)
{
	char	*newp;

	if (h == (void*)0)
		return (p);
	if (p == (void*)0)
		return ((char*)h);
	else
	{
		newp = (char*)malloc(sizeof(newp) * (ft_strlen(p) + ft_strlen(h)));
		ft_strcpy(newp, h);
		ft_strncat(newp, p + 1, ft_strlen(p) - 1);
		return (newp);
	}
}
