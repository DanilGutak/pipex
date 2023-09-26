/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:43:00 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/22 11:44:05 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	charset_check(const char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

int	check_quotes(int in_quotes, char s, int *temp)
{
	if ((s == '\"' || s == '\'') && !in_quotes)
	{
		in_quotes = 1;
		*temp = s;
	}
	else if (s == *temp)
		in_quotes = 0;
	return (in_quotes);
}

int	freemem(char **result, int i)
{
	while (--i >= 0)
		free(result[i]);
	free(result);
	return (-1);
}
