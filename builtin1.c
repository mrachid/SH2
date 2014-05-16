/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 09:23:15 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/16 19:03:52 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_cd(char *path)
{
	int		ret;
	char	buf[BUF_SIZE];
	char	*oldpwd;

	if (path == (void*)0 || *path == '~')
		path = cd_tild(path, get_key("HOME"));
	if (path != (void*)0 && *path == '-')
		path = get_key("OLDPWD");
	if (path == (void*)0)
		return (ft_puts_error("ft_minishell: cd: ENV Error") + 1);
	oldpwd = ft_strdup(getcwd(buf, BUF_SIZE));
	ret = chdir(path);
	if (ret == -1)
	{
		ft_puts_error("ft_minishell: cd: ");
		ft_puts_error(path);
		ft_puts_error(": Error\n");
		return (0);
	}
	ft_setenv("PWD", getcwd(buf, BUF_SIZE), "1");
	ft_setenv("OLDPWD", oldpwd, "1");
	free(oldpwd);
	return (0);
}

int		ft_setenv(char const *name, char const *value, char *overwrite)
{
	int		i;
	int		find;
	char	**tmpenv;

	if (name == (void*)0 || value == (void*)0)
		return (ft_puts_error("Usage: setenv <name> <value>\n"));
	i = 0;
	find = 0;
	tmpenv = get_env();
	while (tmpenv[i] != (void*)0 && find == 0)
	{
		if (is_key(tmpenv[i], name))
		{
			if (overwrite == (void*)0 || overwrite[0] == '1')
				tmpenv[i] = get_new_var_env(name, value, tmpenv[i]);
			find = 1;
		}
		i++;
	}
	if (find == 0)
		add_env(name, value);
	return (0);
}

int		ft_unsetenv(char const *name)
{
	int		find;
	char	**tmpenv;
	char	**newenv;

	if (name == (void*)0)
		return (ft_puts_error("Usage: unsetenv <name>\n"));
	find = 0;
	tmpenv = get_env();
	newenv = (char**)malloc(sizeof(newenv) * ft_tablelen(tmpenv));
	find = del_env(tmpenv, newenv, name);
	if (find == 0)
	{
		BLUE;
		ft_puts_error("unsetenv: ");
		ft_puts_error(name);
		ft_puts_error(": doesn't exist\n");
		CANCEL;
	}
	else
		ft_setmyenv(newenv, tmpenv);
	return (0);
}

int		print_env(void)
{
	int		i;
	char	**env;

	i = 0;
	env = get_env();
	if (env[i] == (void*)0)
	{
		BLUE;
		return (ft_puts_error("ft_minishell: env > Error: env UNDEFINED\n"));
		CANCEL;
	}
	while (env[i] != (void*)0)
	{
		ft_putstr(env[i]);
		ft_putstr("\n");
		i++;
	}
	return (0);
}
