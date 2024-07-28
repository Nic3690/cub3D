/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_sky.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:50:08 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 20:42:36 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_ceiling_and_floor(t_game *g)
{
	int     y;
	t_image *image;
	double  row_dist;

	y = 0;
	image = NULL;
	row_dist = 0;
	while (y < HEIGHT)
	{
		image = check_sky_floor(g, image, y, &row_dist);
		g->pg->ray_x0 = g->pg->dir_x - g->pg->plane_x;
		g->pg->ray_y0 = g->pg->dir_y - g->pg->plane_y;
		g->pg->ray_x1 = g->pg->dir_x + g->pg->plane_x;
		g->pg->ray_y1 = g->pg->dir_y + g->pg->plane_y;
		g->tex->step_x = row_dist * (g->pg->ray_x1 - g->pg->ray_x0) / WIDTH;
		g->tex->step_y = row_dist * (g->pg->ray_y1 - g->pg->ray_y0) / WIDTH;
		g->pg->fx = g->pg->pos_x + row_dist * g->pg->ray_x0;
		g->pg->fy = g->pg->pos_y + row_dist * g->pg->ray_y0;
		color_floor_and_sky(g, image, y);
		y++;
	}
}

t_image	*check_sky_floor(t_game *g, t_image *image, int y, double *row_dist)
{
	int half;

	half = 0;
	if (y < HEIGHT / 2)
	{
		image = g->tex->sky;
		half = y;
	}
	else
	{
		image = g->tex->floor;
		half = HEIGHT - y - 1;
	}
	*row_dist = 0.5 * HEIGHT / (half - HEIGHT / 2);
	return (image);
}

void	color_floor_and_sky(t_game *g, t_image *img, int y)
{
	int x;

	x = -1;
	while (x++ < WIDTH)
	{
		g->tex->x = (int)(img->w * (g->pg->fx - (int)g->pg->fx))
			& (img->w - 1);
		g->tex->y = (int)(img->h * (g->pg->fy - (int)g->pg->fy))
			& (img->h - 1);
		g->pg->fx += g->tex->step_x;
		g->pg->fy += g->tex->step_y;
		pixel_put(g, x, y, get_tex_color(img, g->tex->x, g->tex->y));
	}
}
