/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:44:48 by madjogou          #+#    #+#             */
/*   Updated: 2023/12/11 16:11:37 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0 ;
	while (s[i])
		i++;
	return (i);
}

int	ft_search_newline(char *varstatic)
{
	int	i;

	if (!varstatic)
		return (0);
	i = 0;
	while (varstatic[i])
	{
		if (varstatic[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	size_t		i;
	char		*dest;
	char		*s;

	s = (char *)s1;
	i = 0;
	while (s[i])
		i++;
	dest = malloc(sizeof(char) * i + 1);
	i = 0;
	if (dest == NULL)
		return (0);
	else
	{
		while (s[i])
		{
			dest[i] = s[i];
			i++;
		}
		dest[i] = '\0';
		return (dest);
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*newstringofss;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	newstringofss = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstringofss)
		return (NULL);
	while (s1[i])
	{
		newstringofss[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		newstringofss[j + i] = s2[j];
		j++;
	}
	newstringofss[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (newstringofss);
}