/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 11:35:39 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/28 11:41:47 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(t_pipex *pipex, char *str, int status)
{
	pipex_pip_freedom(pipex, pipex->pip);
	if (pipex->fd >= 0)
		close(pipex->fd);
	if (pipex->outfile)
	{
		pipex->fd = open(pipex->outfile, O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (pipex->fd >= 0)
			close(pipex->fd);
	}
	if (status == 0)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	else if (status == 1)
	{
		perror(str);
		exit(1);
	}
	else if (status == 2)
		exit(0);
	else if (status == 3)
		exit(1);
}

void	free_double_p(char **p)
{
	int	i;

	i = -1;
	if (p)
	{
		while (p[++i])
			free(p[i]);
		free(p);
	}
}

void	pipex_pip_freedom(t_pipex *pipex, int *pid)
{
	free_double_p(pipex->args1);
	free_double_p(pipex->args2);
	free_double_p(pipex->path);
	if (pipex->pathname1)
		free(pipex->pathname1);
	if (pipex->pathname2)
		free(pipex->pathname2);
	if (pid[0] > -1)
		close(pid[0]);
	if (pid[1] > -1)
		close(pid[1]);
}

void	do_child1(t_pipex *pipex, char *filed, int *pip)
{
	pipex->fd = open(filed, O_RDONLY, 0111);
	if (pipex->fd == -1)
		error(pipex, "open:", 1);
	dup2(pip[1], STDOUT_FILENO);
	dup2(pipex->fd, STDIN_FILENO);
	close(pip[0]);
	close(pip[1]);
	close(pipex->fd);
	free_double_p(pipex->args2);
	free_double_p(pipex->path);
	if (pipex->pathname2)
		free(pipex->pathname2);
	if (execve(pipex->pathname1, pipex->args1, pipex->envp) == -1)
		error(pipex, "execve:", 1);
}

void	do_child2(t_pipex *pipex, char *filed, int *pip)
{
	pipex->fd = open(filed, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->fd == -1)
		error(pipex, "open:", 1);
	dup2(pip[0], STDIN_FILENO);
	dup2(pipex->fd, STDOUT_FILENO);
	close(pip[0]);
	close(pip[1]);
	close(pipex->fd);
	free_double_p(pipex->args1);
	free_double_p(pipex->path);
	if (pipex->pathname1)
		free(pipex->pathname1);
	if (execve(pipex->pathname2, pipex->args2, pipex->envp) == -1)
		error(pipex, "execve:", 1);
}
