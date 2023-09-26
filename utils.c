/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:03:22 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/26 13:31:57 by dgutak           ###   ########.fr       */
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
			error(pipex,"pipex: ft_strtrim failed", 0);
		free(args[i]);
		args[i] = tmp;
		i++;
	}
}
