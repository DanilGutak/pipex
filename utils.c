/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:03:22 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/28 11:55:33 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	minus_quotes(char **args, t_pipex *pipex)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args[i] != NULL)
	{
		tmp = ft_strtrim(args[i], "\"'");
		if (tmp == NULL)
			error(pipex, "pipex: ft_strtrim failed", 0);
		free(args[i]);
		args[i] = tmp;
		i++;
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
	pipex->flag1 = 0;
	pipex->flag2 = 0;
	if (argc == 5)
		pipex->outfile = argv[4];
	else
		pipex->outfile = NULL;
}
