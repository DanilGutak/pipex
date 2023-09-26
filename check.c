/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:43:04 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/22 14:35:34 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "pipex.h"

static int	len_word(char const *str, char charset, int in_quotes)
{
	int	len;
	int	temp;

	len = 0;
	temp = 0;
	while (*str && !(charset_check(*str, charset) && !in_quotes))
	{
		if (*str == '\\' && (*(str + 1) == '\'' || *(str + 1) == '\"'))
		{
			str = str + 2;
			len = len + 2;
			continue ;
		}
		if ((*str == '\"' || *str == '\'') && !in_quotes)
		{
			in_quotes = 1;
			temp = *str;
		}
		else if (*str == temp)
			in_quotes = 0;
		len++;
		str++;
	}
	return (len);
}

int	check_word(int in_word, int in_quotes, int *count, const char *c)
{
	if (!charset_check(*c, ' ') && !in_word && !in_quotes)
	{
		*count = *count + 1;
		return (1);
	}
	else if (charset_check(*c, ' ') && !in_quotes)
		return (0);
	return (in_word);
}

static int	count_words(const char *str)
{
	int		count;
	int		in_word;
	int		in_quotes;
	char	temp;

	count = 0;
	in_word = 0;
	in_quotes = 0;
	temp = 0;
	while (*str)
	{
		if (*str == '\\' && (*(str + 1) == '\'' || *(str + 1) == '\"'))
			str = str + 2;
		in_word = check_word(in_word, in_quotes, &count, str);
		if ((*str == '\"' || *str == '\'') && !in_quotes)
		{
			in_quotes = 1;
			temp = *str;
		}
		else if (*str == temp)
			in_quotes = 0;
		str++;
	}
	return (count);
}

int	fill_word(char const *s, char c, char **result, int i)
{
	int		in_quotes;
	int		temp;
	int		j;

	in_quotes = 0;
	j = 0;
	temp = 0;
	result[i] = (char *)malloc(sizeof(char) * (len_word(s, c, 0) + 1));
	if (!result[i])
		return (freemem(result, i));
	while (*s && !(charset_check(*s, c) && !in_quotes))
	{
		if (*s == '\\' && (*(s + 1) == '\'' || *(s + 1) == '\"'))
		{
			result[i][j++] = *s++;
			result[i][j++] = *s++;
			continue ;
		}
		in_quotes = check_quotes(in_quotes, *s, &temp);
		result[i][j++] = *s++;
	}
	result[i][j] = '\0';
	return (j);
}

char	**split_args(char const *s, char c)
{
	int		i;
	int		j;
	char	**result;
	int		word_count;

	i = -1;
	word_count = count_words(s);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	while (++i < word_count)
	{
		while (charset_check(*s, c))
			s++;
		j = fill_word(s, c, result, i);
		if (j == -1)
			return (NULL);
		s = s + j + 1;
	}
	result[i] = 0;
	return (result);
}
/* int main(void)
{
    char **res;

    // Test case 7: Input with mixed quotes and spaces
    res = split_args("awk '{count++} END {print count}'", ' ');
    printf("%s\n%s\n%s\n", res[0], res[1], res[2]);
    freemem(res, 3);

    return (0);
} */
