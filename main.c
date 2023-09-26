/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:03:27 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/26 15:13:48 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**read_path(char **envp, char *temp, t_pipex *pipex, int i)
{
	char	**ret;
	char	*find;

	pipex->envp = envp;
	while (envp[++i])
	{
		find = ft_strstr(envp[i], "PATH=");
		if (find != NULL)
			break ;
	}
	if (envp[i] == NULL)
		error(pipex, "pipex: did not find PATH in the enviroment", 0);
	ret = ft_split(find, ':');
	if (!ret)
		error(pipex, "pipex: ft_split failed", 0);	
	i = -1;
	while (ret[++i])
	{
		temp = ret[i];
		ret[i] = ft_strjoin(ret[i], "/");
		free(temp);
		if (!ret[i])
			(free_double_p(ret), error(pipex, "pipex: ft_strjoin failed", 0));
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
		if (!ret)
			error(pipex, "pipex: ft_strjoin failed", 0);
		if (access(ret, 0) == 0)
			return (ret);
		free(ret);
		i++;
	}
	error(pipex, "pipex: command not found", 0);
	return (NULL);
}

void	read_cmd(char **argv, int j, t_pipex *pipex)
{
	if (j == 2)
	{
		pipex->args1 = split_args(argv[j], ' ');
		if (!pipex->args1)
			error(pipex, "pipex: split_args failed", 0);
		minus_quotes(pipex->args1, pipex);
		pipex->cmd = pipex->args1[0];
		pipex->pathname1 = find_path(pipex);
	}
	else
	{
		pipex->args2 = split_args(argv[j], ' ');
		if (!pipex->args2)
			error(pipex, "pipex: split_args failed", 0);
		minus_quotes(pipex->args2, pipex);
		pipex->cmd = pipex->args2[0];
		pipex->pathname2 = find_path(pipex);
	}
}

void	p_init(t_pipex *pipex, char **argv, int argc)
{
	pipex->path = NULL;
	pipex->pathname1 = NULL;
	pipex->pathname2 = NULL;
	pipex->args1 = NULL;
	pipex->args2 = NULL;
	pipex->pip[1] = -1;
	pipex->pip[0] = -1;
	pipex->fd = -228;
	if (argc == 5)
		pipex->outfile = argv[4];
	else
		pipex->outfile = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	process1;
	pid_t	process2;

	p_init(&pipex, argv, argc);
	if (argc != 5)
		error(&pipex, "pipex: invalid number of arguments", 0);
	pipex.path = read_path(envp, NULL, &pipex, -1);
	if (pipe(pipex.pip) == -1)
		error(&pipex, "pipe:", 1);
	read_cmd(argv, 2, &pipex);
	read_cmd(argv, 3, &pipex);
	process1 = fork();
	if (process1 < 0)
		error(&pipex, "fork: ", 1);
	if (!process1)
		do_child1(&pipex, argv[1], pipex.pip);
	waitpid(process1, NULL, 0);
	process2 = fork();
	if (process2 < 0)
		error(&pipex, "fork: ", 1);
	if (!process2)
		do_child2(&pipex, pipex.outfile, pipex.pip);
	error(&pipex, NULL, 2);
}
