/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:12:42 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/20 19:06:49 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_bzero(void *s, int n, char c)
{
	int	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	((char *)s)[i] = '\0';
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (0);
}

int	ft_strlen(char *string)
{
	int	count;

	count = 0;
	while (string[count])
		count++;
	return (count);
}

char	*ft_strdup(char *string)
{
	int		i;
	int		size;
	char	*duplicate;

	i = 0;
	size = ft_strlen(string);
	duplicate = malloc(sizeof(char) * (size) + 1);
	if (!duplicate)
		return (0);
	while (string[i] && string[i] != '\n')
	{
		duplicate[i] = string[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*get_next_line(int fd)
{
	char	buffer;
	char	line[5000];
	int		b;
	int		i;

	if (fd < 0)
		return (NULL);
	i = 0;
	b = read(fd, &buffer, 1);
	while (b > 0)
	{
		line[i++] = buffer;
		if (buffer == '\n')
			break ;
		b = read(fd, &buffer, 1);
	}
	line[i] = '\0';
	if (b <= 0 || i < 2)
		return (NULL);
	return (ft_strdup(line));
}