/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:01:15 by rpassos-          #+#    #+#             */
/*   Updated: 2025/02/11 19:01:16 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	count_words(char *s, char c)
{
	int	index;
	int	counter;
	int	check;

	counter = 0;
	check = 0;
	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == c)
			check = 0;
		else if (s[index] != c && check == 0)
		{
			check = 1;
			counter++;
		}
		index++;
	}
	return (counter);
}

void	free_big(char **big)
{
	int	index;

	index = 0;
	while (big[index] != NULL)
	{
		free(big[index]);
		index++;
	}
	free(big);
}

char	*substr(char *s, int index, char c, char **big)
{
	char	*sub;
	int		subindex;
	int		size;

	size = 0;
	subindex = index;
	while (!(s[index] == c || s[index] == '\0'))
	{
		size++;
		index++;
	}
	sub = (char *)malloc(sizeof(char) * size + 1);
	if (!sub)
	{
		free_big(big);
		return (NULL);
	}
	index = subindex;
	subindex = 0;
	while (subindex < size)
		sub[subindex++] = s[index++];
	sub[subindex] = '\0';
	return (sub);
}

char	**ft_split(char const *s, char c)
{
	char	**big;
	int		bigindex;
	int		index;

	if (!s)
		return (NULL);
	bigindex = 0;
	index = 0;
	big = (char **)malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
	if (!big)
		return (NULL);
	while (s[index] != '\0')
	{
		if (s[index] != c)
		{
			big[bigindex++] = substr((char *)s, index, c, big);
			while (!(s[index] == c || s[index] == '\0'))
				index++;
		}
		if (s[index] == '\0')
			break ;
		index++;
	}
	big[bigindex] = NULL;
	return (big);
}

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter] != '\0')
		counter++;
	return (counter);
}
