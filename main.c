/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:03:27 by dgutak            #+#    #+#             */
/*   Updated: 2023/08/05 12:55:16 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**read_path(char **envp)
{
	char	**ret;
	char	*find;
	int		i;

	i = -1;
	while (envp[++i])
	{
		find = ft_strstr(envp[i], "PATH=");
		if (find != NULL)
			break ;
	}
	if (envp[i] == NULL)
		error();
	ret = ft_split(find, ':');
	i = -1;
	while (ret[++i])
	{
		ret[i] = ft_strjoin(ret[i], "/");
	}
	return (ret);
}

char	*find_path(t_pipex *pipex)
{
	char	*ret;
	int		i;

	i = 0;
	while (pipex->path[i])
	{
		ret = ft_strjoin(pipex->path[i], pipex->cmd);
		if (access(ret, 0) == 0)
			return (ret);
		free(ret);
		i++;
	}
	error();
	return (NULL);
}

int	read_cmd(char **argv, int j, t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->args = ft_split(argv[j], ' ');
	if (!(pipex->args && pipex->args[0]))
		error();
	pipex->cmd = pipex->args[0];
	while (pipex->args[i + 1])
	{
		pipex->args[i] = pipex->args[i + 1];
		i++;
	}
	pipex->args[i] = NULL;
	pipex->pathname = find_path(pipex);
	if (pipex->pathname == NULL)
		error();
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		pip[2];
	t_pipex	pipex;
	pid_t	parent;

	if (argc != 5)
		error();
	pipex.path = read_path(envp);
	pipex.envp = envp;
	pipe(pip);
	parent = fork();
	if (parent < 0)
		error();
	if (!parent)
	{
		if (read_cmd(argv, 2, &pipex) != 0)
			error();
		do_child(&pipex, argv[1], pip);
	}
	else
	{
		waitpid(parent, NULL, 0);
		if (read_cmd(argv, 3, &pipex) != 0)
			error();
		do_parent(&pipex, argv[4], pip);
	}
}
