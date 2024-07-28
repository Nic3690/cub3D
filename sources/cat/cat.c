/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:27:14 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 20:33:04 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    draw_face_cat(t_game *game)
{
    int scale;
    int x_start;
    int y_start;

    scale = 5;
    x_start = WIDTH - (WIDTH / 100) - 250;
    y_start = HEIGHT / 75;
    draw_cat_face(game, scale, x_start, y_start);
}

void    draw_cat_face(t_game *game, int scale, int x_start, int y_start)
{
    int x;
    int y;
    int img_x;
    int img_y;
    int color;

    x = 0;
    y = 0;
    while (y < game->tex->cat_face->h * scale)
    {
        x = 0;
        while (x < game->tex->cat_face->w * scale)
        {
            img_x = x / scale;
            img_y = y / scale;
            color = get_tex_color(game->tex->cat_face, img_x, img_y);
            if (color != (0xFF << 24))
                pixel_put(game, x_start + x, y_start + y, color);
            x++;
        }
        y++;
    }
}

void    check_cat_distance(t_cat *cat)
{
	if (cat->distance > cat->move_speed)
	{
		cat->dir_x /= cat->distance;
		cat->dir_y /=cat-> distance;
		cat->pos_x += cat->dir_x * cat->move_speed;
		cat->pos_y += cat->dir_y * cat->move_speed;
	}
	else
	{
		cat->pos_x = cat->target_x + 0.5;
		cat->pos_y = cat->target_y + 0.5;
	}
	if ((fabs(cat->pos_x - cat->target_x) < 0.5)
		&& (fabs(cat->pos_y - cat->target_y) < 0.5))
		cat->current_target++;
}

void	move_cat(t_game *game)
{
    t_cat	*cat;

	cat = game->cat;
    check_cat_visibility(game, cat);
    if (cat->current_target < cat->path_length && cat->visible)
    {
        cat->target_x = cat->path[cat->current_target].x + 0.5;
        cat->target_y = cat->path[cat->current_target].y + 0.5;
        cat->dir_x = cat->target_x - cat->pos_x;
        cat->dir_y = cat->target_y - cat->pos_y;
        cat->distance = sqrt(cat->dir_x * cat->dir_x
			+ cat->dir_y * cat->dir_y);
        check_cat_distance(cat);
    }
    if (fabs((int)cat->pos_x - game->door_x) <= 1
		&& fabs((int)cat->pos_y - game->door_y) <= 1)
        game->win_status = 3;
}

void    update_cat_textures(t_game *game)
{
    t_cat   *cat;
    
    cat = game->cat;
    calculate_cat_direction(cat);
    move_cat(game);
    update_cat_texture_state(game, cat);
    if (cat->death_timer > 0)
        set_death_cat_texture(game);
}
