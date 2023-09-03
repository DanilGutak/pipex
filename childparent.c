/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 11:35:39 by dgutak            #+#    #+#             */
/*   Updated: 2023/08/30 13:21:55 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("Error:)");
	exit(EXIT_FAILURE);
}

void	do_child(t_pipex *pipex, char *filed, int *pip)
{
	int		fd;

	fd = open(filed, O_RDONLY, 0777);
	if (fd == -1)
		error();
	dup2(pip[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(pip[0]);
	ft_printf("kek\n");
	ft_printf("%s, %s, %s, %s\n ya child",pipex->pathname, pipex->args[0],pipex->args[1],pipex->envp[0]);
	if (execve(pipex->pathname, pipex->args, pipex->envp) == -1)
		error();
}

void	do_parent(t_pipex *pipex, char *filed, int *pip)
{
	int		fd;

	fd = open(filed, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		error();
	dup2(pip[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pip[1]);
	ft_printf("%s, %s, %s, %s\n ya parent",pipex->pathname, pipex->args[0],pipex->args[1],pipex->envp[0]);
	if (execve(pipex->pathname, pipex->args, pipex->envp) == -1)
		error();
}
