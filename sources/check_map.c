/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:07:33 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 22:05:38 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_pg(t_game *g)
	{
	int	i;
	int	j;
	int	count_pg;

	i = 0;
	j = 0;
	count_pg = 0;
	while (i < g->map_rows)
	{
		j = 0;
		while (j < g->map_cols)
		{
			if (g->map[i][j] == 'N' || g->map[i][j] == 'S' || 
				g->map[i][j] == 'E' || g->map[i][j] == 'W') {
				count_pg++;
			}
			j++;
		}
		i++;
	}
	if (count_pg != 1)
		return (0);
	return (1);
}

int	check_left_right(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < g->map_rows)
	{
		j = 0;
		while (g->map[i][j] == ' ')
			j++;
		if (g->map[i][j] != '1' && g->map[i][j] != '8')
			return (0);
		i++;
	}
	i = 0;
	while (i < g->map_rows)
	{
		j = g->map_cols - 1;
		while (g->map[i][j] == ' ' || !g->map[i][j])
			j--;
		if (g->map[i][j] != '1' && g->map[i][j] != '8')
			return (0);
		i++;
	}
	return (1);
}

int	check_bottom_top(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < g->map_cols)
	{
		i = 0;
		while (g->map[i][j] == ' ')
			i++;
		if (g->map[i][j] != '1' && g->map[i][j] != '8')
			return (0);
		j++;
	}
	j = 0;
	while (j < g->map_cols)
	{
		i = g->map_rows - 1;
		while (g->map[i][j] == ' ' || !g->map[i][j])
			i--;
		if (g->map[i][j] != '1' && g->map[i][j] != '8')
			return (0);
		j++;
	}
	return (1);
}

void	check_valid_map(t_game *g)
{
	if (!check_left_right(g) || !check_bottom_top(g))
	{
		printf ("Error\nInvalid map\n");
		exit_game(g);
	}
}
