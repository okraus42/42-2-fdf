/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colour3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:11:53 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:16:27 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fdf.h"

static unsigned int	ft_colour_3(int d[2], unsigned int c0, unsigned int c1,
	unsigned int rgb[4])
{
	unsigned int	r[4];

	if ((c0 & 0xFF000000) < (c1 & 0xFF000000))
		r[0] = ((rgb[0] * d[0]) / d[1] + ((c0 & 0xFF000000) >> 24)) << 24;
	else
		r[0] = (((c0 & 0xFF000000) >> 24) - (rgb[0] * d[0]) / d[1]) << 24;
	if ((c0 & 0xFF0000) < (c1 & 0xFF0000))
		r[1] = (rgb[1] * d[0] / d[1] + ((c0 & 0xFF0000) >> 16)) << 16;
	else
		r[1] = (((c0 & 0xFF0000) >> 16) - (rgb[1] * d[0] / d[1])) << 16;
	if ((c0 & 0xFF00) < (c1 & 0xFF00))
		r[2] = (rgb[2] * d[0] / d[1] + ((c0 & 0xFF00) >> 8)) << 8;
	else
		r[2] = (((c0 & 0xFF00) >> 8) - (rgb[2] * d[0] / d[1])) << 8;
	if ((c0 & 0xFF) < (c1 & 0xFF))
		r[3] = rgb[3] * d[0] / d[1] + (c0 & 0xFF);
	else
		r[3] = (c0 & 0xFF) - rgb[3] * d[0] / d[1];
	return (r[0] | r[1] | r[2] | r[3]);
}

static unsigned int	ft_colour_2(int d[2], unsigned int c0, unsigned int c1)
{
	unsigned int	rgb[4];

	if (!d[1])
		d[1] = 1;
	rgb[0] = (ft_uabsdif(c0 & 0xFF000000, c1 & 0xFF000000)) >> 24;
	rgb[1] = (ft_uabsdif(c0 & 0xFF0000, c1 & 0xFF0000)) >> 16;
	rgb[2] = (ft_uabsdif(c0 & 0xFF00, c1 & 0xFF00)) >> 8;
	rgb[3] = ft_uabsdif(c0 & 0xFF, c1 & 0xFF);
	return (ft_colour_3(d, c0, c1, rgb));
}

static unsigned int	ft_colour_1(int a, int b, unsigned int c0, unsigned int c1)
{
	int	d[2];

	d[0] = a;
	d[1] = b;
	return (ft_colour_2(d, c0, c1));
}

unsigned int	ft_colour(t_map *map, int i, int j)
{
	if (map->mo[i][j].z < 0)
	{
		return (ft_colour_1(ft_abs(map->min - map->mo[i][j].z),
			ft_abs(map->min), 0x000066FF, 0xCCFFFFFF));
	}
	else if (map->mo[i][j].z <= (1 * map->max / 8))
		return (ft_colour_1(ft_abs(map->mo[i][j].z),
			ft_abs(1 * map->max / 8), 0xCCFFFFFF, 0x006600FF));
	else if (map->mo[i][j].z <= (1 * map->max / 2))
		return (ft_colour_1(ft_abs(map->mo[i][j].z - 1 * map->max / 8),
			ft_abs(1 * map->max / 8 - 1 * map->max / 2),
			0x006600FF, 0xFFFFCCFF));
	else if (map->mo[i][j].z <= (7 * map->max / 8))
		return (ft_colour_1(ft_abs(map->mo[i][j].z - 1 * map->max / 2),
			ft_abs(1 * map->max / 2 - 7 * map->max / 8),
			0xFFFFCCFF, 0x663300FF));
	else
		return (ft_colour_1(ft_abs(map->mo[i][j].z - 7 * map->max / 8),
			ft_abs(map->max - 7 * map->max / 8), 0x663300FF, 0xFFFFFFFF));
}
