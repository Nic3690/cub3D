/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:47:39 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/01 15:27:44 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define TEXTURE

#define TEXTURE_SKY         0
#define TEXTURE_GRASS       1
#define TEXTURE_SIDE_RIGHT  2
#define TEXTURE_SIDE_LEFT   3
#define TEXTURE_FENCE_LIGHT 4
#define TEXTURE_FENCE_DARK  5

#define MAX_TEXTURES 6

#define WIDTH 1000
#define HEIGHT 750
#define MAP_COLUMNS 25
#define MAP_ROWS 13

# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <float.h>
# include <fcntl.h>

typedef struct  s_image
{
    void        *img;
    char        *addr;
    int         bits;
    int         line;
    int         endian;
    int         w;
    int         h;
}               t_image;

typedef struct s_texture
{
	char	*sprite_north;
	char	*sprite_south;
	char	*sprite_west;
	char	*sprite_east;
	char	*sprite_floor;
	char	*sprite_sky;
	int		x;
	int		y;
	double	tex_pos;
	double	step_x;
	double	step_y;
	double	wall_x;
    int     tex_w;
    int     tex_h;
	t_image	*north;
	t_image	*south;
	t_image	*west;
	t_image	*east;
	t_image	*floor;
	t_image	*sky;
}	t_texture;

typedef struct  s_player
{
    double      pos_x;
    double      pos_y;
    double      dir_x;
    double      dir_y;
    double      plane_x;
    double      plane_y;
    int         side;
    double      side_x;
    double      side_y;
    double      delta_x;
    double      delta_y;
    int         map_x;
    int         map_y;
    int         step_x;
    int         step_y;
    double      ray_x;
    double      ray_y;
    double      ray_x0;
    double      ray_y0;
    double      ray_x1;
    double      ray_y1;
    double      fx;
    double      fy;
    double      wall_dist;
}               t_player;

typedef struct s_data
{
    int *textures[MAX_TEXTURES];
    int texture_width[MAX_TEXTURES];
    int texture_height[MAX_TEXTURES];
    int num_textures;
} t_data;

typedef struct  s_game
{
    void        *mlx;
    void        *win;
    void	    *img;
	char	    *addr;
    int		    bits;
	int		    line;
	int		    endian;
    char        **map;
    int         map_width;
    int         map_height;
    t_player    *pg;
    t_data      *data;
    t_image     *image;
    t_texture   *tex;
}               t_game;

/*main.c*/
void pixel_put(t_game *game, int x, int y, int color);
void init_game(t_game *game);
int load_texture(t_game *game, t_image *texture_image, const char *path);
int load_wall_textures(t_game *game, const char **paths);

/*raycasting.c*/
void    color_floor_and_sky(t_game *game, t_image *image, int y);
t_image *check_sky_floor(t_game *game, t_image *image, int y, double *row_dist);
void calculate_ray_direction(t_game *game, int x);
void identify_cell(t_player *pg);
void calculate_wall_distance(t_game *game);
int calculate_line_height(t_player *pg, int side);
int get_tex_color(t_image *image, int tex_x, int tex_y);
void render_wall_column(t_game *game, int x, int line_height, int draw_start, int draw_end, int side, double wall_x);
void	drawing(t_game *game, int x);
int render_game(t_game *game);

/*map.c*/
void load_map(t_game *game, const char *filename);

#endif