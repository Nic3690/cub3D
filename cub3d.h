/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:47:39 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/20 18:47:46 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define TEXTURE

#define NORTH 'N'
#define SOUTH 'S'
#define WEST 'W'
#define EAST 'E'
#define FOOD '2'
#define BONE '3'
#define CAT '4'
#define CROW '5'
#define FLY '6'
#define SPIDER '7'
#define DOOR '8'

#define MAX_TEXTURES 6

#define WIDTH 1000
#define HEIGHT 750
#define MAP_COLUMNS 25
#define MAP_ROWS 13

#define ROTATION_SPEED 0.1

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

typedef struct s_entity
{
    double pos_x;
    double pos_y;
    double dist;
    t_image *texture;
} t_entity;

typedef struct s_enemy
{
    double  pos_x;
    double  pos_y;
    double  dist;
    t_image *texture;
    t_image *texture2;
    t_image *current_texture;
    t_image *attack_texture;
    t_image *dead_texture;
    double  last_switch_time;
    int     attacking;
    int     retreating;
    int     retreat_timer;
    int     type;
    int     enemy_health;
    int     death_timer;
}   t_enemy;

typedef struct s_food
{
    double  pos_x;
    double  pos_y;
    int     type;
    double  dist;
    t_image *texture;
    int     active;
}   t_food;

typedef struct s_cat
{
    double  pos_x;
    double  pos_y;
    double  dist;
    int visible;
    int wait_timer;
    int moving;
    double target_x;
    double target_y;
    t_image *current_texture;
    t_image *escape_texture;
    t_image *escape_texture_2;
    t_image *escape_texture_3;
    t_image *escape_texture_4;
    t_image *dead_texture;
    int     health;
    int     death_timer;
}   t_cat;

typedef struct s_texture
{
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
    t_image *paws;
    t_image *blood_paws;
    t_image *crow;
    t_image *fly;
    t_image *spider;
    t_image *crow_open;
    t_image *fly_open;
    t_image *spider_2;
    t_image *maya;
    t_image *angry_maya;
    t_image *maya_left;
    t_image *maya_right;
    t_image *fly_attack;
    t_image *spider_attack;
    t_image *crow_attack;
    t_image *fly_dead;
    t_image *spider_dead;
    t_image *crow_dead;
    t_image *food;
    t_image *bone;
    t_image *cat_dead;
    t_image *cat_escape;
    t_image *cat_escape_2;
    t_image *cat_escape_3;
    t_image *cat_escape_4;
    t_image *door_light;
    t_image *door_dark;
}	t_texture;

typedef struct s_draw
{
    int		draw_start;
    int		draw_end;
    int		line;
    int		tex_x;
    int		tex_y;
    int		color;
    double  wall_x;
    double  step;
}	t_draw;

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
    double      move_speed;
    int         health;
    int         attack;
    int         attack_time;
    int         attack_cooldown;
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
    char        **texture_paths;
    t_player    *pg;
    t_data      *data;
    t_image     *image;
    t_texture   *tex;
    t_draw      *draw;
    t_enemy     *enemies;
    int         num_enemies;
    double      *z_buffer;
    int         frame_count;
    int         face_state;
    int         face_timer;
    int         num_food;
    t_food      *food;
    t_cat       *cat;
    double      door_x;
    double      door_y;
}               t_game;

/*main.c*/
void    exit_game(t_game *g);
void pixel_put(t_game *game, int x, int y, int color);
void init_game(t_game *game);
int load_texture(t_game *game, t_image *texture_image, const char *path);
int load_wall_textures(t_game *game);

/*raycasting.c*/
void	calculate_ray_direction(t_game *game, int x);
void	identify_cell(t_player *pg);
void	calculate_wall_distance(t_game *game);
void	calculate_wall_side(t_game *g);
int		calculate_line_height(t_player *pg, int side);

/*rendering.c*/
void	render_ceiling_and_floor(t_game *g);
t_image	*check_sky_floor(t_game *game, t_image *image, int y, double *row_dist);
void	color_floor_and_sky(t_game *game, t_image *image, int y);
void	render_wall_column(t_game *game, int x, t_draw *draw, int side);
int		render_game(t_game *game);

/*drawing.c*/
int		get_tex_color(t_image *image, int tex_x, int tex_y);
void	drawing(t_game *g, t_image *image, double tex_pos, int x);
void	drawing_colums(t_game *game, int x);

/*map.c*/
void    set_player_direction(t_game *game, char dir);
void    init_paths(t_game *game, char *filename);
void	init_map(t_game *game, int fd);

/*get_next_line.c*/
char	*ft_strchr(const char *s, int c);
int     ft_strlen(char *string);
char	*ft_strdup(char *string);
char	*get_next_line(int fd);

/*keys.c*/
void	rotate_right(t_player *pg);
void	rotate_left(t_player *pg);
int		key_press(int keycode, t_game *g);

/*enemies.c*/
void update_enemy_textures(t_game *game);
int is_visible(t_game *game, double x0, double y0, double x1, double y1);

/*maya.c*/
void draw_face(t_game *game);
void update_face_state(t_game *game);

/*health_bar.c*/
void draw_rectangle(t_game *game, int x, int y, int width, int height, int color);
void draw_health_bar(t_game *game, int x, int y, int width, int height);

/*attack.c*/
void start_attack(t_game *game);
void draw_paws_attack(t_game *game);
void player_attack(t_game *game);

/*collision.c*/
int is_enemy_at(t_game *game, double x, double y);
void move_forward(t_game *game);
void move_backward(t_game *game);
void move_left(t_game *game);
void move_right(t_game *game);

/*food.c*/
void update_food_textures(t_game *game);
void    check_food_collision(t_game *game);

/*cat.c*/
void update_cat_textures(t_game *game);
int is_visible_cat(t_game *game, double x0, double y0, double x1, double y1);

/*door.c*/
void render_door_sprite(t_game *game);

/*entity.c*/
void calculate_entity_distances(t_game *game, t_entity *entities, int *entity_count);
void render_entity(t_game *game, t_entity *entity);

#endif