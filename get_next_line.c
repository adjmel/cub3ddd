/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:51:17 by madjogou          #+#    #+#             */
/*   Updated: 2023/12/11 16:11:42 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_lenbuffern(char *buffer)
{
	size_t	lenbuffern;

	lenbuffern = 0;
	if (!buffer)
		return (0);
	while (buffer[lenbuffern] && buffer[lenbuffern] != '\n')
		lenbuffern++;
	if (buffer[lenbuffern] == '\n')
		lenbuffern++;
	return (lenbuffern);
}

char	*ft_copy_before(char *buffer)
{
	char	*extractvarstatic;
	size_t	lenbuffern;
	size_t	i;

	lenbuffern = ft_lenbuffern(buffer);
	i = 0;
	if (!*buffer)
		return (NULL);
	extractvarstatic = malloc(sizeof(char) * (lenbuffern + 1));
	if (!extractvarstatic)
		return (NULL);
	else
	{
		while (i < lenbuffern)
		{
			extractvarstatic[i] = buffer[i];
			i++;
		}
		extractvarstatic[i] = '\0';
		return (extractvarstatic);
	}
}

char	*ft_copy_after(char *buffer)
{
	char		*extrctvarstat;
	size_t		lenbuffern;
	size_t		i;

	lenbuffern = ft_lenbuffern(buffer);
	i = 0;
	if (!buffer[lenbuffern])
	{
		free(buffer);
		return (NULL);
	}
	extrctvarstat = malloc(sizeof(char) * (ft_strlen(buffer) - lenbuffern
				+ 1));
	if (!extrctvarstat)
		return (NULL);
	while (buffer[lenbuffern])
	{	
		extrctvarstat[i++] = buffer[lenbuffern++];
	}
	extrctvarstat[i] = '\0';
	free(buffer);
	return (extrctvarstat);
}

char	*ft_read_my_varstatic(int fd, char *varstatic)
{
	char		*buffer;
	size_t		numberbytesread;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	numberbytesread = 1;
	while (!ft_search_newline (varstatic) && numberbytesread != 0)
	{
		numberbytesread = read (fd, buffer, BUFFER_SIZE);
		if ((int)numberbytesread == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer [numberbytesread] = '\0';
		if (!varstatic)
			varstatic = ft_strdup(buffer);
		else
			varstatic = ft_strjoin(varstatic, buffer);
	}
	free(buffer);
	return (varstatic);
}

char	*get_next_line(int fd)
{
	static char	*varstatic;
	char		*extractionline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	varstatic = ft_read_my_varstatic (fd, varstatic);
	if (!varstatic)
		return (NULL);
	extractionline = ft_copy_before (varstatic);
	varstatic = ft_copy_after (varstatic);
	return (extractionline);
}