/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:58:53 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/28 12:03:48 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>

typedef struct s_pipex
{
	char	**path;
	char	*pathname1;
	char	*pathname2;
	char	**envp;
	char	**args1;
	char	**args2;
	char	*cmd;
	int		pip[2];
	int		fd;
	char	*outfile;
	int		flag1;
	int		flag2;

}			t_pipex;
void		pipex_pip_freedom(t_pipex *pipex, int *pid);
void		free_double_p(char **p);
void		minus_quotes(char **args, t_pipex *pipex);
void		do_child1(t_pipex *pipex, char *filed, int *pip);
void		do_child2(t_pipex *pipex, char *filed, int *pip);
int			freemem(char **result, int i);
int			check_quotes(int in_quotes, char s, int *temp);
int			charset_check(const char c, char charset);
void		do_parent(t_pipex *pipex, char *filed, int *pip);
void		error(t_pipex *pipex, char *str, int status);
void		execute(char *argv, char **envp);
char		**split_args(char const *s, char c);
void		pipex_pip_freedom(t_pipex *pipex, int *pid);
void		p_init(t_pipex *pipex, char **argv, int argc);
#endif