/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:57:20 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/27 12:23:59 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_tex_color(t_image *image, int tex_x, int tex_y)
{
    int *texture;

	texture = (int *)image->addr;
    return (texture[tex_y * image->w + tex_x]);
}

void	drawing(t_game *g, t_image *image, double tex_pos, int x)
{
	int	y;
	int	color;

	y = g->draw->draw_start;
	while (y < g->draw->draw_end)
	{
		g->draw->tex_y = (int)tex_pos & (g->tex->tex_h - 1);
        tex_pos += g->draw->step;
        color = get_tex_color(image, g->draw->tex_x, g->draw->tex_y);
		if (color != (0xFF << 24))
			pixel_put(g, x, y, color);
		y++;
	}
}

void	drawing_colums(t_game *g, int x)
{
	t_draw	*draw;

	draw = malloc (sizeof(t_draw));
	if (!draw)
		return ;
	draw->line = (int)(HEIGHT / g->pg->wall_dist);
	draw->draw_start = -draw->line / 2 + HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line / 2 + HEIGHT / 2;
	if (draw->draw_end >= HEIGHT)
		draw->draw_end = HEIGHT - 1;
	if (g->pg->side == 0)
		draw->wall_x = g->pg->pos_y + g->pg->wall_dist * g->pg->ray_y;
	else
		draw->wall_x = g->pg->pos_x + g->pg->wall_dist * g->pg->ray_x;
	draw->wall_x -= floor(draw->wall_x);
	g->draw = draw;
	render_wall_column(g, x, g->pg->side);
	free(draw);
}

void draw_win_lose(t_game *game, t_image *texture)
{
    int x, y;
    int img_x, img_y;
    int scale = 10;

    int screen_x_start = (WIDTH - (texture->w * scale)) / 2;
    int screen_y_start = (HEIGHT - (texture->h * scale)) / 2;
    for (y = 0; y < texture->h * scale; y++)
    {
        for (x = 0; x < texture->w * scale; x++)
        {
            img_x = x / scale;
            img_y = y / scale;
            int color = get_tex_color(texture, img_x, img_y);
            if (color != (0xFF << 24))
                pixel_put(game, screen_x_start + x, screen_y_start + y, color);
        }
    }
}
