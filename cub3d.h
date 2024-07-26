/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:47:39 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/26 18:28:52 by nfurlani         ###   ########.fr       */
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
#define CATDOOR '8'
#define DOOR '9'

#define MAX_TEXTURES 6

#define WIDTH 1000
#define HEIGHT 750
#define MAP_COLUMNS 25
#define MAP_ROWS 13

#define ROTATION_SPEED 0.1

#define FOOD_COLLISION_RADIUS 0.5

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
    double  pos_x;
    double  pos_y;
    double  dist;
    t_image *tex;
    int move_along_y;
    int move_along_x;
    double     sprite_x;
    double     sprite_y;
    int     draw_start_x;
    int     draw_end_x;
    int     draw_start_y;
    int     draw_end_y;
    int     e_width;
    int     e_height;
    double  transform_x;
    double  transform_y;
    int     tex_x;
    int     tex_y;
} t_entity;

typedef struct s_enemy
{
    double  pos_x;
    double  pos_y;
    int     map_x;
    int     map_y;
    double  dist;
    double  dir_x;
    double  dir_y;
    double  ray_dir_x;
    double  ray_dir_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_x;
    double  delta_y;
    double  step_x;
    double  step_y;
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
    double  speed;
    int     frame;
    int     damage;
}   t_enemy;

typedef struct s_food
{
    double  pos_x;
    double  pos_y;
    double dir_x;
    double dir_y;
    double dist_x;
    double dist_y;
    int     type;
    double  dist;
    t_image *texture;
    int     active;
}   t_food;

typedef struct s_cat
{
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  dist;
    double  ray_dir_x;
    double  ray_dir_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_x;
    double  delta_y;
    double  step_x;
    double  step_y;
    int     visible;
    int     wait_timer;
    int     moving;
    double target_x;
    double target_y;
    double move_speed;
    double distance;
    t_image *current_texture;
    t_image *escape_texture;
    t_image *escape_texture_2;
    t_image *escape_texture_3;
    t_image *escape_texture_4;
    t_image *dead_texture;
    int     health;
    int     death_timer;
}   t_cat;

typedef struct s_door
{
    int     pos_x;
    int     pos_y;
    double  dist;
    int     is_open;
    t_image *closed_tex;
    t_image *open_tex;
    t_image *curr_tex;
}   t_door;

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
    t_image *cat_face;
    t_image *open_door;
    t_image *closed_door;
    t_image *you_win;
    t_image *you_lose;
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
    void	    *minimap;
	char	    *addr;
    int		    bits;
	int		    line;
	int		    endian;
	char	    *miniaddr;
    int		    minibits;
	int		    miniline;
	int		    miniendian;
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
    t_door      *doors;
    int         num_enemies;
    int         num_food;
    int         num_doors;
    double      *z_buffer;
    int         frame_count;
    int         face_state;
    int         face_timer;
    t_food      *food;
    t_cat       *cat;
    double      door_x;
    double      door_y;
    int         map_rows;
    int         map_cols;
    int         is_cat;
    int         show_minimap;
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
void	calculate_wall_distance(t_game *game, int type);
void	calculate_wall_side(t_game *g);
int		calculate_line_height(t_player *pg, int side);

/*rendering.c*/
void	render_ceiling_and_floor(t_game *g);
t_image	*check_sky_floor(t_game *game, t_image *image, int y, double *row_dist);
void	color_floor_and_sky(t_game *game, t_image *image, int y);
void	render_wall_column(t_game *game, int x, int side);
void	render(t_game *g);
void	render_doors(t_game *g);
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
void	ft_bzero(void *s, int n, char c);
char	*ft_strchr(const char *s, int c);
int     ft_strlen(char *string);
char	*ft_strdup(char *string);
char	*get_next_line(int fd);

/*keys.c*/
void	rotate_right(t_player *pg);
void	rotate_left(t_player *pg);
int		key_press(int keycode, t_game *g);

/*enemies.c*/
void    update_enemy_textures(t_game *game);
void    move_and_attack_enemy(t_game *game, t_enemy *enemy, double attack_distance);
void    distance_between_enemies(t_game *game, int i, double min_dist_btw);
void    init_enemy_rays(t_game *game, t_enemy *enemy);
void    perform_enemy_dda(t_enemy *enemy);

/*enemies_utils.c*/
void    init_parameters(t_game *game, t_enemy *enemy, int *visible);
void    process_death_timer(t_game *game, t_enemy *enemy, int *i);
void    retreat_enemy(t_enemy *enemy);
void    check_textures(t_game *game, t_enemy *enemy);
int     is_visible(t_game *game, t_enemy *enemy);

/*maya.c*/
void draw_face(t_game *game);
void update_face_state(t_game *game);

/*health_bar.c*/
void draw_rectangle(t_game *game, int x, int y, int width, int height, int color);
void draw_health_bar(t_game *game, int x, int y, int width, int height);
void draw_health_bar_cat(t_game *game, int x, int y, int width, int height);

/*attack.c*/
void start_attack(t_game *game);
void update_attack_status(t_game *game);
void attack_enemy(t_game *game, t_enemy *enemy, int attack_damage, double attack_distance);
void attack_cat(t_game *game, int attack_damage, double attack_distance);
void player_attack(t_game *game);

/*check_collision*/
int is_enemy_at(t_game *game, double x, double y);
int is_food(t_game *game, double x, double y);
int is_door_open(t_game *game, double x, double y);

/*collision.c*/
void move_forward(t_game *game);
void move_backward(t_game *game);
void move_left(t_game *game);
void move_right(t_game *game);

/*add_entities*/
void    add_food(t_game *game, t_entity *entities, int *entity_count);
void    add_enemy(t_game *game, t_entity *entities, int *entity_count);
void    add_cat(t_game *game, t_entity *entities, int *entity_count);

/*draw_entities*/
int     calculate_tex_x(t_entity *entity, int stripe, int sprite_screen_x);
int     is_valid_stripe(t_game *game, t_entity *entity, int stripe);
void    draw_sprite_column(t_game *game, t_entity *entity, int stripe);
void    draw_sprite(t_game *game, t_entity *entity, int sprite_screen_x);

/*render_entities*/
void	calculate_sprite_transform(t_game *g, t_entity *e);
void	calculate_sprite_dimensions(t_entity *e, int *screen_x);
void	calculate_draw_limits(t_entity *e, int screen_x);
void    render_entity(t_game *game, t_entity *entity);

/*entity*/
void    sort_entities_by_distance(t_entity *entities, int *entity_count);
void    entity_distances(t_game *game, t_entity *entities, int *entity_count);

/*food.c*/
void    update_food_textures(t_game *game);
void    remove_food(t_game *game, int index);
void    check_food_collision(t_game *game);

/*door.c*/
void open_close_door(t_game *g);

/*minimap.c*/
void draw_minimap(t_game *game);

/*paws.c*/
void draw_paws_image(t_game *game, t_image *attack_paws, int scale);
void draw_paws_attack(t_game *game);

/*cat.c*/
void move_cat(t_game *game);
void calculate_cat_direction(t_cat *cat);
void check_cat_visibility(t_game *game, t_cat *cat);
void update_cat_texture_state(t_game *game, t_cat *cat);
void update_cat_textures(t_game *game);

/*draw_cat.c*/
void draw_face_cat(t_game *game);

/*visibility.c*/
void init_ray(t_cat *cat, double x0, double y0, double x1, double y1);
void calculate_step_and_side_dist(t_cat *cat, double x0, double y0, int map_x, int map_y);
int perform_dda(t_game *game, t_cat *cat, int map_x, int map_y, double x1, double y1);
int is_visible_cat(t_game *game, double x0, double y0, double x1, double y1);

/*cat_collision.c*/
int is_wall(t_game *game, double x, double y);
int is_near_wall(t_game *game, double x, double y, double margin);
void handle_cat_collision(t_game *game);

void draw_win_lose(t_game *game, t_image *texture);

#endif