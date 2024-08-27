/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:29:19 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 15:23:06 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_bar_params(int *y, int *height, int *color, int type)
{
	*y = HEIGHT / 9;
	*height = HEIGHT / 60;
	if (type == 0)
	{
		*y -= 2;
		*height += 4;
		*color = 0x555555;
	}
	else
		*color = 0xFF0000;
}

void	draw_rectangle(t_game *game, int x, int width, int type)
{
	int		y;
	int		height;
	int		color;
	int		original;
	char	*dst;

	init_bar_params(&y, &height, &color, type);
	original = width;
	while (height)
	{
		width = original;
		while (width)
		{
			dst = game->addr + ((y + height) * game->line
					+ (x + width) * (game->bits / 8));
			*(unsigned int *)dst = color;
			width--;
		}
		height--;
	}
}

void	draw_health_bar(t_game *game)
{
	int	x;
	int	width;
	int	health_width;

	x = WIDTH / 13;
	width = 3 * WIDTH / 10;
	draw_rectangle(game, x - 2, width + 4, 0);
	if (game->pg->health <= 0)
		return ;
	health_width = (game->pg->health * width) / 100;
	draw_rectangle(game, x, health_width, 1);
}

void	draw_health_bar_cat(t_game *game)
{
	int	x;
	int	width;
	int	health_width;

	x = WIDTH - (3 * WIDTH / 10) - (WIDTH / 13);
	width = 3 * WIDTH / 10;
	draw_rectangle(game, x - 2, width + 4, 0);
	health_width = (game->cat->health * width) / 500;
	draw_rectangle(game, x + (width - health_width), health_width, 1);
}
