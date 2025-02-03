#ifndef PIPEX_H
    #define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
static char	*substr(char *s, int index, char c, char **big);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);

#endif