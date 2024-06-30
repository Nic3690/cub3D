/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:47:39 by nfurlani          #+#    #+#             */
/*   Updated: 2024/06/30 15:50:12 by nfurlani         ###   ########.fr       */
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
    int         width;
    int         height;
}               t_image;

typedef struct s_texture
{
	char	*sprite_north;
	char	*sprite_south;
	char	*sprite_west;
	char	*sprite_east;
	char	*sprite_floor;
	char	*sprite_sky;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
	double	wall_x;
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
    double      side_dist_x;
    double      side_dist_y;
    double      delta_dist_x;
    double      delta_dist_y;
    int         map_x;
    int         map_y;
    int         step_x;
    int         step_y;
    double      ray_dir_x;
    double      ray_dir_y;
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
    t_player    *player;
    t_data      *data;
    t_image     *image;
    t_texture   *texture;
}               t_game;

/*main.c*/
void my_mlx_pixel_put(t_game *game, int x, int y, int color);
void init_game(t_game *game);
int load_texture(t_game *game, t_image *texture_image, const char *path);
int load_wall_textures(t_game *game, const char **paths);

/*raycasting.c*/
void calculate_ray_direction(t_game *game, int x, double *ray_dir_x, double *ray_dir_y);
void identify_map_cell(t_player *player, double ray_dir_x, double ray_dir_y, int *map_x, int *map_y);
void calculate_wall_distance(t_game *game, double ray_dir_x, double ray_dir_y, int *map_x, int *map_y, int *side, double *wall_dist);
int calculate_line_height(t_player *player, int side);
int get_texture_pixel_color(t_image *image, int tex_x, int tex_y);
void render_wall_column(t_game *game, int x, int line_height, int draw_start, int draw_end, int side, double wall_x);
int render_game(t_game *game);

/*map.c*/
void load_map(t_game *game, const char *filename);

#endif