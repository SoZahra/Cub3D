/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:34:26 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/15 16:31:31 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int init_doors(t_data *data)
{
    int count = 0;
    int i, j;

    for (i = 0; i < data->map_height; i++)
        for (j = 0; j < data->map_width; j++)
            if (data->map[i][j] == 'D')
                count++;
    data->doors = malloc(sizeof(t_door) * count);
    if (!data->doors)
        return (0);
    count = 0;
    for (i = 0; i < data->map_height; i++)
    {
        for (j = 0; j < data->map_width; j++)
        {
            if (data->map[i][j] == 'D')
            {
                data->doors[count].x = j;
                data->doors[count].y = i;
                data->doors[count].is_open = 0;
                data->doors[count].animation = 0.0;
                count++;
            }
        }
    }
    data->num_doors = count;
    return (1);
}

void handle_door(t_data *data)
{
    int player_x = (int)data->player.pos_x;
    int player_y = (int)data->player.pos_y;

    for (int i = 0; i < data->num_doors; i++)
    {
        if (abs(player_x - data->doors[i].x) <= 1 &&
            abs(player_y - data->doors[i].y) <= 1)
        {
            if (data->keys.e)
            {
                data->doors[i].is_open = !data->doors[i].is_open;
            }
        }
    }
}

void update_doors(t_data *data)
{
    for (int i = 0; i < data->num_doors; i++)
    {
        if (data->doors[i].is_open && data->doors[i].animation < 1.0)
            data->doors[i].animation += 0.05;
        else if (!data->doors[i].is_open && data->doors[i].animation > 0.0)
            data->doors[i].animation -= 0.05;
    }
}
