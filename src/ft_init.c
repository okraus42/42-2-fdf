/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:12:05 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:17:20 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fdf.h"

void	ft_init_row(t_map *map, int i)
{
	int			j;

	j = 0;
	map->mr[i] = malloc((map->w) * sizeof(t_point));
	while (j < map->w)
	{
		map->mr[i][j].y = (map->mo[i][j].y) + (map->z * (i - map->h / 2));
		map->mr[i][j].x = (map->mo[i][j].x) + (map->z * (j - map->w / 2));
		map->mr[i][j].z = map->mo[i][j].z;
		map->mr[i][j].c = map->mo[i][j].c;
		if (map->mo[i][j].z > map->max)
			map->max = map->mo[i][j].z;
		if (map->mo[i][j].z < map->min)
			map->min = map->mo[i][j].z;
		j++;
	}
}

void	ft_init_coord(t_map *map)
{
	int		i;

	i = 0;
	map->max = map->mo[0][0].z;
	map->min = map->mo[0][0].z;
	map->mr = malloc((map->h + 1) * sizeof(t_point *));
	while (i < map->h)
	{
		ft_init_row(map, i);
		i++;
	}
	map->mr[map->h] = NULL;
}

void	ft_init_map(t_map *map)
{
	map->m = NULL;
	map->mo = NULL;
	map->mr = NULL;
	map->ms = NULL;
	map->w = 0;
	map->h = 0;
	map->d = 0;
	map->p = 0;
	map->x = 0;
	map->y = 0;
	map->z = 4;
	map->q = 64;
	map->xs = 500;
	map->ys = 400;
	map->ax = 0;
	map->ay = 0;
	map->az = 0;
}
