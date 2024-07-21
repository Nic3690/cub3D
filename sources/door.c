/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:49:38 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/21 22:18:59 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void open_close_door(t_game *g)
{
	int i;
	
	i = 0;
	while (i < g->num_doors)
	{
		if (abs(g->doors[i].pos_x - g->pg->map_x) < 1 && abs(g->doors[i].pos_y - g->pg->map_y) < 1)
		{
			if (g->doors[i].is_open == 0)
			{
				g->doors[i].is_open = 1;
				g->doors[i].curr_tex = g->doors[i].open_tex;
			}
			else
			{
				g->doors[i].is_open = 0;
				g->doors[i].curr_tex = g->doors[i].closed_tex;
			}
			break ;
		}
		i++;
	}
}
