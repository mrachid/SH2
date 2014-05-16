/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 18:25:57 by mrachid           #+#    #+#             */
/*   Updated: 2014/05/16 18:54:05 by mrachid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# define BUF_SIZE 512
# define SYMBOL ";,<>"
# define BLACK      ft_putstr("\033[30m")
# define RED        ft_putstr("\033[31m")
# define GREEN      ft_putstr("\033[32m")
# define YELLOW     ft_putstr("\033[33m")
# define BLUE       ft_putstr("\033[34m")
# define PURPLE     ft_putstr("\033[35m")
# define CYAN       ft_putstr("\033[36m")
# define GREY       ft_putstr("\033[37m")
# define HIGHLIGHT  ft_putstr("\033[1m")
# define UNDERLINE  ft_putstr("\033[4m")
# define CANCEL     ft_putstr("\033[0m")

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <libft.h>

void	ft_saveenv(char **env);
void	ft_exeinenv(char **arg);
void	ft_setmyenv(char **newenv, char **oldenv);
char	**get_env(void);
char	*get_key(char *key);
int		is_key(char const *s1, char const *key);
int		ft_tablelen(char **env);
char	*ft_topath(char *cmd, char *path);
int		ft_setenv(char const *name, char const *value, char *overwrite);
int		ft_unsetenv(char const *name);
int		ft_cd(char *path);
int		print_env(void);
char	*get_new_var_env(char const *name, char const *value, char *tmpenv);
char	*cd_tild(char *path, char const *home);
void	add_env(char const *name, char const *value);
int		del_env(char **tmpenv, char **newenv, char const *name);
void	ft_freetable(char **table);
char	*ft_strndup(char const *s1, size_t n);
void	ft_execmd(char const *cmd);
int		ft_issymbol(int c);
int		ft_checksymbolcmd(char *cmd);
int		ft_cmdcontaincar(char *cmd, char c);
void	ft_initsignal(void);
void	ft_sighandler(int sig);
void	ft_pipecmd(char *cmd, int fd_entry, int fd_exit);
int		ft_execpipe(char *cmd);
void	ft_printcmd(int pfd[]);
char	*ft_replacetab(char *s1);
char	*ft_strtrim(char const *s);
int		ft_isdouble(char const *s1, char c);
int		ft_execinfiled(char *cmd);
int		ft_writefile(char *name, int fdf);
int		ft_appendfile(char *name, int fdf);
void	ft_execwrite(char *cmd, int fd_entry);
int		ft_syntaxchecked(char *cmd);
int		verif_cmd(char *cmd);
char	*get_new_cmd(char *cmd);
void	ft_printfd(int fd);
void	ft_execmultired(char *cmd);
void	prompt(char **env);
int		recup_user(char **env, char *target);

#endif
