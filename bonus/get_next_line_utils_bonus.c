/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:08:06 by rpassos-          #+#    #+#             */
/*   Updated: 2024/11/06 18:08:08 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		size;
	int		i;
	int		j;
	char	*str;

	if (!s1)
		s1 = "";
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	int		substrsize;
	int		index;

	if (!s)
		return (NULL);
	substrsize = len;
	if (len > ft_strlen((char *)s) - start)
		substrsize = ft_strlen((char *)s) - start;
	if (len == 0 || start > ft_strlen((char *)s))
	{
		substr = (char *)malloc(sizeof(char));
		if (substr == NULL)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	index = 0;
	substr = (char *)malloc(sizeof(char) * (substrsize + 1));
	if (substr == NULL)
		return (NULL);
	while (substrsize-- > 0 && s[start] != '\0')
		substr[index++] = s[start++];
	substr[index] = '\0';
	return (substr);
}

char	*ft_strchr(const char *s, int c)
{
	char	letter;

	letter = c;
	if (!c)
		return ((char *)s + ft_strlen((char *)s));
	while (1)
	{
		if (*s == letter)
			return ((char *)s);
		else if (*s == '\0' && c != '\0')
			return (NULL);
		else if (*s == '\0')
			return ((char *)s);
		s++;
	}
}

char	*ft_strdup(char *str)
{
	int		size;
	int		index;
	char	*dest;

	if (!str)
		return (NULL);
	size = ft_strlen(str);
	index = 0;
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (dest == NULL)
		return (NULL);
	while (str[index])
	{
		dest[index] = str[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
