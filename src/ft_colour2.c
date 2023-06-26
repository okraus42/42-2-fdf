/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colour2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:11:49 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:15:04 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fdf.h"

void	ft_black(t_max *max)
{
	int	x;
	int	y;

	y = 0;
	while (y < 900)
	{
		x = 0;
		while (x < 1600)
		{
			mlx_put_pixel(max->img, x, y, 0xFF);
			x++;
		}
		y++;
	}
}

void	ft_colourize(void *param)
{
	t_max	*max;
	t_map	*m;
	int		i;
	int		j;

	max = param;
	m = max->map;
	i = 0;
	ft_black(max);
	ft_update_screen(max->map);
	while (i < m->h)
	{
		j = 0;
		while (j < m->w)
		{
			ft_place_line(max, i, j);
			if (m->ms[i][j].x > 0 && m->ms[i][j].x < 1600
				&& m->ms[i][j].y > 0 && m->ms[i][j].y < 900)
				mlx_put_pixel(max->img, m->ms[i][j].x,
					m->ms[i][j].y, m->ms[i][j].c);
			j++;
		}
		i++;
	}
}

int	ft_get_color(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	i = 0;
	while (str && str[i] && str[i] != ',')
		i++;
	if (str[i] == ',' && str[i + 1] == '0' && str[i + 2] == 'X')
		return (ft_atoi_base("0123456789ABCDEF", &str[i + 3]) << 8 | 0xFF);
	return (0);
}
