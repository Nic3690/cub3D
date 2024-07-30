/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:41:50 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/30 12:18:00 by nfurlani         ###   ########.fr       */
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
	if (string[size - 1] == '\n')
		size--;
	duplicate = ft_calloc(size + 1, sizeof(char));
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

char    *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
