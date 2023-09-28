/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:03:27 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/28 11:55:19 by dgutak           ###   ########.fr       */
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
		if (!pipex->pathname1)
			pipex->flag1 = 1;
	}
	else
	{
		pipex->args2 = split_args(argv[j], ' ');
		if (!pipex->args2)
			error(pipex, "pipex: split_args failed", 0);
		minus_quotes(pipex->args2, pipex);
		pipex->cmd = pipex->args2[0];
		pipex->pathname2 = find_path(pipex);
		if (!pipex->pathname2)
			pipex->flag2 = 1;
	}
}

void	run_children(t_pipex *pipex, char **argv)
{
	pid_t	process1;
	pid_t	process2;

	process1 = fork();
	if (process1 < 0)
		error(pipex, "fork: ", 1);
	if (!process1)
	{
		if (pipex->flag1 == 0)
			do_child1(pipex, argv[1], pipex->pip);
		error(pipex, "", 3);
	}
	waitpid(process1, NULL, 0);
	process2 = fork();
	if (process2 < 0)
		error(pipex, "fork: ", 1);
	if (!process2)
	{
		if (pipex->flag2 == 0)
			do_child2(pipex, pipex->outfile, pipex->pip);
		error(pipex, "", 3);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	p_init(&pipex, argv, argc);
	if (argc != 5)
		error(&pipex, "pipex: invalid number of arguments", 0);
	pipex.path = read_path(envp, NULL, &pipex, -1);
	if (pipe(pipex.pip) == -1)
		error(&pipex, "pipe:", 1);
	read_cmd(argv, 2, &pipex);
	read_cmd(argv, 3, &pipex);
	run_children(&pipex, argv);
	if (pipex.flag2 != 0 || pipex.flag1 != 0)
		error(&pipex, "pipex: command not found", 0);
	error(&pipex, NULL, 2);
}
