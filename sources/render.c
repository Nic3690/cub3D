// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   render.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/06/30 17:40:58 by nfurlani          #+#    #+#             */
// /*   Updated: 2024/06/30 17:53:53 by nfurlani         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// void render_ceiling_and_floor(t_game *game)
// {
//     t_image *sky_texture;
//     t_image *floor_texture;
//     int y;
//     int x;

//     initialize_variables(game, &sky_texture, &floor_texture, &y, &x);

//     while (y < HEIGHT)
//     {
//         int check_top;
//         int p;
//         double pos_z;
//         double row_distance;
//         double ray_dir_x0, ray_dir_y0, ray_dir_x1, ray_dir_y1;
//         double floor_step_x, floor_step_y;
//         double floor_x, floor_y;

//         calculate_floor_and_ceiling(y, &check_top, &pos_z, &row_distance, &p, HEIGHT);
//         set_ray_directions(game, &ray_dir_x0, &ray_dir_y0, &ray_dir_x1, &ray_dir_y1);
//         calculate_steps_and_initial_position(row_distance, ray_dir_x0, ray_dir_y0, ray_dir_x1, ray_dir_y1, &floor_step_x, &floor_step_y, &floor_x, &floor_y, game);

//         t_image *texture = check_top ? sky_texture : floor_texture;
//         render_line(game, y, floor_x, floor_y, floor_step_x, floor_step_y, check_top, texture);

//         y++;
//     }
// }

// void initialize_variables(t_game *game, t_image **sky_texture, t_image **floor_texture, int *y, int *x)
// {
//     *sky_texture = game->texture->sky;
//     *floor_texture = game->texture->floor;
//     *y = 0;
//     *x = 0;
// }

// void set_ray_directions(t_game *game, double *ray_dir_x0, double *ray_dir_y0, double *ray_dir_x1, double *ray_dir_y1)
// {
//     *ray_dir_x0 = game->player->dir_x - game->player->plane_x;
//     *ray_dir_y0 = game->player->dir_y - game->player->plane_y;
//     *ray_dir_x1 = game->player->dir_x + game->player->plane_x;
//     *ray_dir_y1 = game->player->dir_y + game->player->plane_y;
// }

// void calculate_floor_and_ceiling(int y, int *check_top, double *pos_z, double *row_distance, int *p, int height)
// {
//     *check_top = (y < height / 2);
//     *p = *check_top ? y : height - y - 1;
//     *pos_z = 0.5 * height;
//     *row_distance = *pos_z / (*p - height / 2);
// }

// void calculate_steps_and_initial_position(double row_distance, double ray_dir_x0, double ray_dir_y0, double ray_dir_x1, double ray_dir_y1, double *floor_step_x, double *floor_step_y, double *floor_x, double *floor_y, t_game *game)
// {
//     *floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WIDTH;
//     *floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WIDTH;
//     *floor_x = game->player->pos_x + row_distance * ray_dir_x0;
//     *floor_y = game->player->pos_y + row_distance * ray_dir_y0;
// }

// void render_line(t_game *game, int y, double floor_x, double floor_y, double floor_step_x, double floor_step_y, int check_top, t_image *texture)
// {
//     int texture_height = texture->height;
//     int texture_width = texture->width;
//     int x = 0;

//     while (x < WIDTH)
//     {
//         int tex_x = (int)(texture_width * (floor_x - (int)floor_x)) & (texture_width - 1);
//         int tex_y = (int)(texture_height * (floor_y - (int)floor_y)) & (texture_height - 1);
//         floor_x += floor_step_x;
//         floor_y += floor_step_y;

//         int color = get_texture_pixel_color(texture, tex_x, tex_y);
//         my_mlx_pixel_put(game, x, y, color);  // check_top ? color : color è ridondante, usa solo color
//         x++;
//     }
// }