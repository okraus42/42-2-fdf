/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:12:03 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:15:31 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fdf.h"

void	ft_update_map(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			map->mr[y][x].x = (map->mo[y][x].x) + (map->z * (x - map->w / 2));
			map->mr[y][x].y = (map->mo[y][x].y) + (map->z * (y - map->h / 2));
			map->mr[y][x].z = map->mo[y][x].z * 64.0 / map->q;
			ft_rotate_map(map->ax, &map->mr[y][x].y, &map->mr[y][x].z);
			ft_rotate_map(map->ay, &map->mr[y][x].x, &map->mr[y][x].z);
			ft_rotate_map(map->az, &map->mr[y][x].x, &map->mr[y][x].y);
			x++;
		}
		y++;
	}
}

void	ft_update_screen_isometric(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	ft_update_map(map);
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			map->ms[y][x].x = map->xs
				+ (map->mr[y][x].x - map->mr[y][x].y) * cos(M_PI / 6.0);
			map->ms[y][x].y = map->ys
				+ ((map->mr[y][x].x + map->mr[y][x].y) / 2.0)
				- map->mr[y][x].z;
			x++;
		}
		y++;
	}
}

void	ft_update_screen_cabinet(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	ft_update_map(map);
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			map->ms[y][x].x = map->xs
				+ (map->mr[y][x].x + map->mr[y][x].z / 4);
			map->ms[y][x].y = map->ys
				+ (map->mr[y][x].y + map->mr[y][x].z * sin(M_PI / 3.0) / 2.0);
			x++;
		}
		y++;
	}
}

void	ft_update_screen(t_map *map)
{
	if (map->p < 10)
		ft_update_screen_isometric(map);
	else if (map->p < 21)
		ft_update_screen_cabinet(map);
}
