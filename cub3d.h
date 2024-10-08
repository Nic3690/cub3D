/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:47:39 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 16:20:28 by nfurlani         ###   ########.fr       */
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

#define ROTATION_SPEED 0.15

#define FOOD_COLLISION_RADIUS 0.5

#define MINIMAP_SIZE 200
#define TILE_SIZE 300 / MAP_COLUMNS

#define MAX_PATH_LENGTH 127

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
    double		pos_x;
    double		pos_y;
    double		dist;
    t_image		*tex;
    int			move_along_y;
    int			move_along_x;
    double		sprite_x;
    double		sprite_y;
    int			draw_start_x;
    int			draw_end_x;
    int			draw_start_y;
    int			draw_end_y;
    int			e_width;
    int			e_height;
    double		transform_x;
    double		transform_y;
    int			tex_x;
    int			tex_y;
} t_entity;

typedef struct s_enemy
{
    double		pos_x;
    double		pos_y;
    int			map_x;
    int			map_y;
    double		dist;
    double		dir_x;
    double		dir_y;
    double		ray_dir_x;
    double		ray_dir_y;
    double		side_dist_x;
    double		side_dist_y;
    double		delta_x;
    double		delta_y;
    double		step_x;
    double		step_y;
    t_image		*texture;
    t_image		*texture2;
    t_image		*current_texture;
    t_image		*attack_texture;
    t_image		*dead_texture;
    double		last_switch_time;
    int			attacking;
    int			retreating;
    int			retreat_timer;
    int			type;
    int			enemy_health;
    int			death_timer;
    double		speed;
    int			frame;
    int			damage;
}   t_enemy;

typedef struct s_food
{
    double		pos_x;
    double		pos_y;
    double		dist_x;
    double		dist_y;
    int			type;
    double		dist;
    t_image		*texture;
    int			active;
}   t_food;

// new struct
typedef struct s_coord
{
    int			x;
    int			y;
}   t_coord;

// modified struct
typedef struct s_cat
{
    double		pos_x;
    double		pos_y;
    int 		map_x;
    int 		map_y;
    double		dir_x;
    double		dir_y;
    double		dist;
    double		ray_dir_x;
    double		ray_dir_y;
    double		side_dist_x;
    double		side_dist_y;
    double		delta_x;
    double		delta_y;
    double		step_x;
    double		step_y;
    int			visible;
    int			wait_timer;
    int			moving;
    double		target_x;
    double		target_y;
    double		move_speed;
    double		distance;
    t_image		*current_texture;
    t_image		*escape_texture;
    t_image		*escape_texture_2;
    t_image		*escape_texture_3;
    t_image		*escape_texture_4;
    t_image		*escape_texture_5;
    t_image		*escape_texture_6;
    t_image		*dead_texture;
	t_image		*dead_texture_2;
	t_image		*dead_texture_3;
	t_image		*dead_texture_4;
    int			health;
    int			death_timer;
    int         current_target;
    int         path_length;
    t_coord     *path;
}   t_cat;

typedef struct s_door
{
    int			pos_x;
    int			pos_y;
    double		dist;
    int			is_open;
    t_image		*closed_tex;
    t_image		*open_tex;
    t_image		*curr_tex;
}   t_door;

typedef struct s_texture
{
	int			x;
	int			y;
	double		tex_pos;
	double		step_x;
	double		step_y;
	double		wall_x;
    int   		tex_w;
    int   		tex_h;
	t_image		*north;
	t_image		*south;
	t_image		*west;
	t_image		*east;
	t_image		*floor;
	t_image		*sky;
    t_image		*paws;
    t_image		*blood_paws;
    t_image		*crow;
    t_image		*fly;
    t_image		*spider;
    t_image		*crow_open;
    t_image		*fly_open;
    t_image		*spider_2;
    t_image		*maya;
    t_image		*angry_maya;
    t_image		*maya_left;
    t_image		*maya_right;
    t_image		*fly_attack;
    t_image		*spider_attack;
    t_image		*crow_attack;
    t_image		*fly_dead;
    t_image		*spider_dead;
    t_image		*crow_dead;
    t_image		*food;
    t_image		*bone;
    t_image		*cat_dead;
	t_image		*cat_dead_2;
	t_image		*cat_dead_3;
	t_image		*cat_dead_4;
    t_image		*cat_escape;
    t_image		*cat_escape_2;
    t_image		*cat_escape_3;
    t_image		*cat_escape_4;
    t_image		*cat_escape_5;
    t_image		*cat_escape_6;
    t_image		*door_light;
    t_image		*cat_face;
    t_image		*open_door;
    t_image		*closed_door;
    t_image		*you_win;
    t_image		*you_die;
    t_image		*you_lose;
}	t_texture;

typedef struct s_draw
{
    int		draw_start;
    int		draw_end;
    int		line;
    int		tex_x;
    int		tex_y;
    int		color;
    double	wall_x;
    double	step;
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
    int         win_status;
}               t_game;

/*main.c*/
void    pixel_put(t_game *game, int x, int y, int color);
void    init_parameters_game(t_game *g);
void    init_game(t_game *game);

/*free.c*/
void	free_textures(t_game *g);
void	free_map(t_game *g);
void	free_game_objects(t_game *g);
void	free_graphics(t_game *g);
int		exit_game(t_game *g);

/*free_entities.c*/
void	free_floor_sky_walls_doors(t_game *g);
void	free_dog(t_game *g);
void	free_enemies(t_game *g);
void	free_cat(t_game *g);
void	free_text(t_game *g);

/*check_map.c*/
int		count_pg(t_game *g);
int		check_bottom_top(t_game *g);
int		check_bottom_top(t_game *g);
void	check_valid_map(t_game *game);

/*keys.c*/
int		key_press(int keycode, t_game *g);
int		mouse_move(int x, int y, t_game *g);

/*minimap.c*/
void    mini_pixel_put(t_game *game, int x, int y, int color);
void    draw_square(t_game *game, int x, int y, int color);
void    draw_mini_player(t_game *g);
void    draw_mini_cat(t_game *g);
void    draw_minimap(t_game *g);

/*utils.c*/
void	ft_bzero(void *s, int n, char c);
char	*ft_strchr(const char *s, int c);
int     ft_strlen(char *string);
char	*ft_strdup(char *string);
char    *ft_strcpy(char *dest, char *src);

/*utils2.c*/
int		ft_strncmp(char *s1, char *s2, int n);
void    *ft_calloc(int count, int size);
void	*ft_memset(void *b, int c, int len);

/************************** CAT FOLDER **************************/
/*cat.c*/
void    draw_face_cat(t_game *game);
void    draw_cat_face(t_game *game, int scale, int x_start, int y_start);
void    check_cat_distance(t_cat *cat);
void    move_cat(t_game *game);
void    update_cat_textures(t_game *game);

/*cat_direction.c*/
void    calculate_cat_direction(t_cat *cat);
void    update_cat_texture_state(t_game *g, t_cat *c);
void    update_cat_texture_near(t_game *g, t_cat *c);
void    update_cat_texture_far(t_game *g, t_cat *c);
void    set_death_cat_texture(t_game *game);

/*cat_path.c*/
void	get_next_coords(t_game *game, int *start_x, int *start_y);
void	add_path_coordinates(t_game *game);

/*visibility.c*/
void    init_ray(t_game *game, t_cat *cat);
void    calculate_step_and_side_dist(t_cat *cat);
int     perform_dda(t_game *game, t_cat *cat);
int     is_visible_cat(t_game *game);
void    check_cat_visibility(t_game *game, t_cat *cat);
/****************************************************************/

/******************************* ELEMENTS FOLDER ********************************/
/*food.c*/
void    check_food_collision(t_game *game);
void	dist_collision(t_game *game, t_food *f, int *i);

/*door.c*/
void open_close_door(t_game *g);

/*paws.c*/
void    draw_paws_image(t_game *game, t_image *attack_paws, int scale);
void    draw_paws_attack(t_game *game);

/*dog.c*/
void    draw_face(t_game *game);
void    update_face_state(t_game *game);
t_image *get_current_face_texture(t_game *game);
void    draw_scaled_face(t_game *game, t_image *current);
void    cycle_face_state(t_game *game);

/*health_bar.c*/
void    init_bar_params(int *y, int *height, int *color, int type);
void    draw_rectangle(t_game *game, int x, int width, int type);
void    draw_health_bar(t_game *game);
void    draw_health_bar_cat(t_game *game);
/********************************************************************************/

/************************** ENEMIES FOLDER ***************************/
/*enemies.c*/
void    update_enemy_textures(t_game *game);
void    move_and_attack(t_game *game, t_enemy *enemy, double attack_distance);
void    distance_between_enemies(t_game *game, int i, double min_dist_btw);
void    init_enemy_rays(t_game *game, t_enemy *enemy);
void    perform_enemy_dda(t_enemy *enemy);

/*enemies_utils.c*/
void    init_parameters(t_game *game, t_enemy *enemy, int *visible);
void    process_death_timer(t_game *game, t_enemy *enemy, int *i);
void    retreat_enemy(t_game *game, t_enemy *enemy);
void    check_textures(t_game *game, t_enemy *enemy);
int     is_visible(t_game *game, t_enemy *enemy);
/*********************************************************************/

/******************************* ENTITIES FOLDER ********************************/
/*add_entities.c*/
void    add_food(t_game *game, t_entity *entities, int *entity_count);
void    add_enemy(t_game *game, t_entity *entities, int *entity_count);
void    add_cat(t_game *game, t_entity *entities, int *entity_count);

/*draw_entities.c*/
int     calculate_tex_x(t_entity *entity, int stripe, int sprite_screen_x);
int     is_valid_stripe(t_game *game, t_entity *entity, int stripe);
void    draw_sprite_column(t_game *game, t_entity *entity, int stripe);
void    draw_sprite(t_game *game, t_entity *entity, int sprite_screen_x);

/*render_entities.c*/
void	calculate_sprite_transform(t_game *g, t_entity *e);
void	calculate_sprite_dimensions(t_entity *e, int *screen_x);
void	calculate_draw_limits(t_entity *e, int screen_x);
void    render_entity(t_game *game, t_entity *entity);

/*entity.c*/
void    sort_entities_by_distance(t_entity *entities, int *entity_count);
void    entity_distances(t_game *game, t_entity *entities, int *entity_count);

/*attack.c*/
void    start_attack(t_game *game);
void    update_attack_status(t_game *game);
void    attack_enemy(t_game *g, t_enemy *e, int a_damage, double a_distance);
void    attack_cat(t_game *game, int attack_damage, double attack_distance);
void    player_attack(t_game *game);
/********************************************************************************/

/************************** MAP FOLDER **************************/
/*map.c*/
void    set_player_direction_ns(t_game *game, char dir);
void    set_player_direction_we(t_game *game, char dir);
void    get_rows_and_cols(t_game *game, int fd, char **buffer);
void    copy_map(t_game *game, char **buffer);

/*position.c*/
void    handle_player_position(t_game *game, int x, int y);
void    handle_door_position(t_game *game, int x, int y);
void    set_enemy_position(t_game *game, int x, int y, int index);

/*init_textures.c*/
void	read_texture_paths(t_game *game, int fd);
void	load_textures_and_map(t_game *game, char *filename);
void	validate_and_sort_path(char **path, char **sorted, int index);
void	sort_paths(char **path);
int		check_valid_path(char **path);

/*init_entities.c*/
void    increment_entity_counts(t_game *game, int x, int y);
void    scan_map_for_entities(t_game *game);
void    allocate_entities(t_game *game);

/*check_parameters.c*/
void    check_doors(t_game *game, int x, int y, int *index);
void    check_food(t_game *game, int x, int y, int *index);
void    check_and_set_enemy(t_game *game, int x, int y, int *index);

/*init_parameters.c*/
void    init_food(t_game *game);
void    init_doors(t_game *game);
void    init_enemies(t_game *game);
void    init_cat(t_game *game);
void    init_map(t_game *game, int fd);

/*enemies_properties.c*/
void    set_fly_properties(t_game *game, int index);
void    set_spider_properties(t_game *game, int index);
void    set_crow_properties(t_game *game, int index);
void    set_cat_properties(t_game *game, int x, int y);

/*get_next_line.c*/
char	*get_next_line(int fd);
/****************************************************************/

/************************** MOVEMENT FOLDER **************************/
/*collision.c*/
int is_enemy_at(t_game *game, double x, double y);
int is_food(t_game *game, double x, double y);
int is_door_open(t_game *game, double x, double y);
int is_cat_at(t_game *game, double x, double y);

/*movement.c*/
void move_forward(t_game *game);
void move_backward(t_game *game);
void move_left(t_game *game);
void move_right(t_game *game);

/*rotation.c*/
void	rotate_right(t_player *pg);
void	rotate_left(t_player *pg);
/**********************************************************************/

/************************** RAYCASTING FOLDER **************************/
/*raycasting.c*/
void	calculate_ray_direction(t_game *game, int x);
void	identify_cell(t_player *pg);
void	init_side(t_game *g);

/*calculate_ray.c*/
void	calculate_deltas(t_player *pg);
void	calculate_steps(t_player *pg);
void	calculate_wall_distance(t_game *g, int type);
void	calculate_wall_side(t_game *g);
int		calculate_line_height(t_player *pg, int side);
/***********************************************************************/

/************************** RENDERING FOLDER **************************/
/*rendering.c*/
void	render(t_game *g);
int     calculate_entity_count(t_game *game);
void    status_and_minimap(t_game *g);
void	render_entities(t_game *game, t_entity *entities, int entity_count);
int 	render_game(t_game *game);

/*floor_sky.c*/
void	render_ceiling_and_floor(t_game *g);
t_image	*check_sky_floor(t_game *game, t_image *image, int y, double *row_dist);
void	color_floor_and_sky(t_game *game, t_image *image, int y);

/*doors_walls.c*/
void	render_wall_column(t_game *game, int x, int side);
t_image *select_wall_texture(t_game *g, int side);
void    check_door_texture(t_game *g, t_image **image);
void	render_doors(t_game *g);

/*drawing.c*/
int		get_tex_color(t_image *image, int tex_x, int tex_y);
void	drawing(t_game *g, t_image *image, double tex_pos, int x);
void	drawing_colums(t_game *game, int x);
void    draw_win_lose(t_game *game, t_image *texture);
void	draw_game_elements(t_game *game);
/***********************************************************************/

/*************************** TEXTURES FOLDER ***************************/
/*load_textures.c*/
void	load_wall_sky_doors_tex(t_game *game);
void	load_dog_tex(t_game *game);
int     load_all_textures(t_game *game);
int     load_texture(t_game *game, t_image *texture_image, const char *path);
void	load_enemies_tex(t_game *game);

/*load_enemy_textures.c*/
void    check_malloc(t_game *g);
void	load_cat_tex(t_game *game);
void	load_crow_tex(t_game *game);
void	load_fly_tex(t_game *game);
void	load_spider_tex(t_game *game);
/***********************************************************************/

#endif