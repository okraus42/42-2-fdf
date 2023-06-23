/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:35:23 by okraus            #+#    #+#             */
/*   Updated: 2023/06/23 20:27:26 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fdf.h"

void	ft_fill_screen(t_map *map);

void	ft_hook2(t_max	*max)
{
	if (mlx_is_key_down(max->mlx, MLX_KEY_W))
		max->map->ax -= 0.03125;
	if (mlx_is_key_down(max->mlx, MLX_KEY_S))
		max->map->ax += 0.03125;
	if (mlx_is_key_down(max->mlx, MLX_KEY_A))
		max->map->az -= 0.03125;
	if (mlx_is_key_down(max->mlx, MLX_KEY_D))
		max->map->az += 0.03125;
	if (mlx_is_key_down(max->mlx, MLX_KEY_Q))
		max->map->ay -= 0.03125;
	if (mlx_is_key_down(max->mlx, MLX_KEY_E))
		max->map->ay += 0.03125;
	if (mlx_is_key_down(max->mlx, MLX_KEY_P))
	{
		max->map->p++;
		if (max->map->p >= 20)
			max->map->p = 0;
	}
}

void	ft_hook(void *param)
{
	t_max	*max;

	max = param;
	if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(max->mlx);
	if (mlx_is_key_down(max->mlx, MLX_KEY_UP))
		max->map->ys += 50;
	if (mlx_is_key_down(max->mlx, MLX_KEY_DOWN))
		max->map->ys -= 50;
	if (mlx_is_key_down(max->mlx, MLX_KEY_LEFT))
		max->map->xs += 50;
	if (mlx_is_key_down(max->mlx, MLX_KEY_RIGHT))
		max->map->xs -= 50;
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_ADD) && max->map->z < 64)
		max->map->z += 1;
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_SUBTRACT) && max->map->z > 1)
		max->map->z -= 1;
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_MULTIPLY) && max->map->q > 1)
		max->map->q -= 1;
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_DIVIDE) && max->map->q < 256)
		max->map->q += 1;
	ft_hook2(max);
}

// plotLineLow(x0, y0, x1, y1)
//     dx = x1 - x0
//     dy = y1 - y0
//     yi = 1
//     if dy < 0
//         yi = -1
//         dy = -dy
//     end if
//     D = (2 * dy) - dx
//     y = y0

//     for x from x0 to x1
//         plot(x, y)
//         if D > 0
//             y = y + yi
//             D = D + (2 * (dy - dx))
//         else
//             D = D + 2*dy
//         end if

unsigned int	ft_mix_colour2(unsigned int d[2], unsigned int rgb[4],
	unsigned int c[2])
{
	unsigned int	r[4];

	if ((c[0] & 0xFF000000) < (c[1] & 0xFF000000))
		r[0] = ((rgb[0] * d[0]) / d[1] + ((c[0] & 0xFF000000) >> 24)) << 24;
	else
		r[0] = (((c[0] & 0xFF000000) >> 24) - ((rgb[0] * d[0]) / d[1])) << 24;
	if ((c[0] & 0xFF0000) < (c[1] & 0xFF0000))
		r[1] = (rgb[1] * d[0] / d[1] + ((c[0] & 0xFF0000) >> 16)) << 16;
	else
		r[1] = (((c[0] & 0xFF0000) >> 16) - (rgb[1] * d[0] / d[1])) << 16;
	if ((c[0] & 0xFF00) < (c[1] & 0xFF00))
		r[2] = (rgb[2] * d[0] / d[1] + ((c[0] & 0xFF00) >> 8)) << 8;
	else
		r[2] = (((c[0] & 0xFF00) >> 8) - (rgb[2] * d[0] / d[1])) << 8;
	if ((c[0] & 0xFF) < (c[1] & 0xFF))
		r[3] = rgb[3] * d[0] / d[1] + (c[0] & 0xFF);
	else
		r[3] = (c[0] & 0xFF) - rgb[3] * d[0] / d[1];
	return (r[0] | r[1] | r[2] | r[3]);
}

unsigned int	ft_mix_colour(int x[3], int y[3], unsigned int c[2])
{
	unsigned int	d[2];
	unsigned int	rgb[4];

	d[0] = ft_abs(x[2] - x[0]) + ft_abs(y[2] - y[0]);
	d[1] = ft_abs(x[1] - x[0]) + ft_abs(y[1] - y[0]);
	if (!d[1])
		d[1] = 1;
	rgb[0] = (ft_uabsdif(c[0] & 0xFF000000, c[1] & 0xFF000000)) >> 24;
	rgb[1] = (ft_uabsdif(c[0] & 0xFF0000, c[1] & 0xFF0000)) >> 16;
	rgb[2] = (ft_uabsdif(c[0] & 0xFF00, c[1] & 0xFF00)) >> 8;
	rgb[3] = ft_uabsdif(c[0] & 0xFF, c[1] & 0xFF);
	return (ft_mix_colour2(d, rgb, c));
}

void	ft_plot_line_low(t_max *max, t_line l)
{
	l.dx = l.x[1] - l.x[0];
	l.dy = l.y[1] - l.y[0];
	l.yi = 1;
	if (l.dy < 0)
	{
		l.yi = -1;
		l.dy *= -1;
	}
	l.d = (2 * l.dy) - l.dx;
	l.x[2] = l.x[0];
	l.y[2] = l.y[0];
	while (l.x[2] <= l.x[1])
	{
		if (l.x[2] > 0 && l.x[2] < 1600 && l.y[2] > 0 && l.y[2] < 900)
			mlx_put_pixel(max->img, l.x[2], l.y[2],
				ft_mix_colour(l.x, l.y, l.c));
		if (l.d > 0)
		{
			l.y[2] = l.y[2] + l.yi;
			l.d += 2 * (l.dy - l.dx);
		}
		else
			l.d = l.d + 2 * l.dy;
		l.x[2]++;
	}
}

// plotLineHigh(x0, y0, x1, y1)
//     dx = x1 - x0
//     dy = y1 - y0
//     xi = 1
//     if dx < 0
//         xi = -1
//         dx = -dx
//     end if
//     D = (2 * dx) - dy
//     x = x0

//     for y from y0 to y1
//         plot(x, y)
//         if D > 0
//             x = x + xi
//             D = D + (2 * (dx - dy))
//         else
//             D = D + 2*dx
//         end if

void	ft_plot_line_high(t_max *max, t_line l)
{
	l.dx = l.x[1] - l.x[0];
	l.dy = l.y[1] - l.y[0];
	l.xi = 1;
	if (l.dx < 0)
	{
		l.xi = -1;
		l.dx *= -1;
	}
	l.d = (2 * l.dx) - l.dy;
	l.x[2] = l.x[0];
	l.y[2] = l.y[0];
	while (l.y[2] <= l.y[1])
	{
		if (l.x[2] > 0 && l.x[2] < 1600 && l.y[2] > 0 && l.y[2] < 900)
			mlx_put_pixel(max->img, l.x[2], l.y[2],
				ft_mix_colour(l.x, l.y, l.c));
		if (l.d > 0)
		{
			l.x[2] = l.x[2] + l.xi;
			l.d = l.d + (2 * (l.dx - l.dy));
		}
		else
			l.d = l.d + 2 * l.dx;
		l.y[2]++;
	}
}

// plotLine(x0, y0, x1, y1)
//     if abs(y1 - y0) < abs(x1 - x0)
//         if x0 > x1
//             plotLineLow(x1, y1, x0, y0)
//         else
//             plotLineLow(x0, y0, x1, y1)
//         end if
//     else
//         if y0 > y1
//             plotLineHigh(x1, y1, x0, y0)
//         else
//             plotLineHigh(x0, y0, x1, y1)
//         end if
//     end if

void	ft_super_swap(int a[3], int b[3], unsigned int c[2])
{
	ft_swap(&a[0], &a[1]);
	ft_swap(&b[0], &b[1]);
	ft_uswap(&c[0], &c[1]);
}

void	ft_plot_line_hor(t_max *max, int i, int j)
{
	t_map	*m;
	t_line	l;

	m = max->map;
	l.x[0] = m->ms[i][j].x;
	l.y[0] = m->ms[i][j].y;
	l.c[0] = m->ms[i][j].c;
	l.x[1] = m->ms[i][j + 1].x;
	l.y[1] = m->ms[i][j + 1].y;
	l.c[1] = m->ms[i][j + 1].c;
	if (ft_abs(l.y[1] - l.y[0]) < ft_abs(l.x[1] - l.x[0]))
	{
		if (l.x[0] > l.x[1])
			ft_super_swap(l.x, l.y, l.c);
		ft_plot_line_low(max, l);
	}
	else
	{
		if (l.y[0] > l.y[1])
			ft_super_swap(l.x, l.y, l.c);
		ft_plot_line_high(max, l);
	}
}

void	ft_plot_line_ver(t_max *max, int i, int j)
{
	t_map	*m;
	t_line	l;

	m = max->map;
	l.x[0] = m->ms[i][j].x;
	l.y[0] = m->ms[i][j].y;
	l.c[0] = m->ms[i][j].c;
	l.x[1] = m->ms[i + 1][j].x;
	l.y[1] = m->ms[i + 1][j].y;
	l.c[1] = m->ms[i + 1][j].c;
	if (ft_abs(l.y[1] - l.y[0]) < ft_abs(l.x[1] - l.x[0]))
	{
		if (l.x[0] > l.x[1])
			ft_super_swap(l.x, l.y, l.c);
		ft_plot_line_low(max, l);
	}
	else
	{
		if (l.y[0] > l.y[1])
			ft_super_swap(l.x, l.y, l.c);
		ft_plot_line_high(max, l);
	}	
}

void	ft_place_line(t_max *max, int i, int j)
{
	t_map	*m;

	m = max->map;
	if (i != m->h - 1)
		ft_plot_line_ver(max, i, j);
	if (j != m->w - 1)
		ft_plot_line_hor(max, i, j);
}

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

void	ft_rotate_map(double angle, double *x, double *y)
{
	double	tx;
	double	ty;

	tx = *x;
	ty = *y;
	*x = tx * cos(angle) - ty * sin(angle);
	*y = tx * sin(angle) + ty * cos(angle);
}

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

// -----------------------------------------------------------------------------

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

void	ft_fill_row(t_map *map, char **row, int i)
{
	int			j;

	j = 0;
	while (row[j])
	{
		j++;
	}
	if (!map->w)
		map->w = j;
	if (map->w != j)
		exit(-1);//wrong map need to free stuff
	j = 0;
	map->mo[i] = malloc((map->w) * sizeof(t_point));
	while (row[j])
	{
		map->mo[i][j].y = i;
		map->mo[i][j].x = j;
		map->mo[i][j].z = ft_atoi(row[j]);
		map->mo[i][j].c = ft_get_color(row[j]);
		j++;
	}
}

void	ft_fill_coord(t_map *map)
{
	char	**row;
	int		i;

	i = 0;
	map->mo = malloc((map->h + 1) * sizeof(t_point *));
	while (i < map->h)
	{
		row = ft_split(map->m[i], ' ');
		ft_fill_row(map, row, i);
		ft_free_split(row);
		i++;
	}
	map->mo[map->h] = NULL;
}

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

unsigned int	ft_colour_3(int d[2], unsigned int c0, unsigned int c1,
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

unsigned int	ft_colour_2(int d[2], unsigned int c0, unsigned int c1)
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

unsigned int	ft_colour(t_map *map, int i, int j, int d[2])
{
	if (map->mo[i][j].z < 0)
	{
		d[0] = ft_abs(map->min - map->mo[i][j].z);
		d[1] = ft_abs(map->min);
		return (ft_colour_2(d, 0x000066FF, 0xCCFFFFFF));
	}
	else if (map->mo[i][j].z <= (1 * map->max / 2))
	{
		d[0] = ft_abs(map->mo[i][j].z);
		d[1] = ft_abs(1 * map->max / 2);
		return (ft_colour_2(d, 0x00FF00FF, 0xFFFFCCFF));
	}
	else if (map->mo[i][j].z <= (7 * map->max / 8))
	{
		d[0] = ft_abs(map->mo[i][j].z - 1 * map->max / 2);
		d[1] = ft_abs(1 * map->max / 2 - 7 * map->max / 8);
		return (ft_colour_2(d, 0xFFFFCCFF, 0x663300FF));
	}
	else
	{
		d[0] = ft_abs(map->mo[i][j].z - 7 * map->max / 8);
		d[1] = ft_abs(map->max - 7 * map->max / 8);
		return (ft_colour_2(d, 0x663300FF, 0xFFFFFFFF));
	}
}

void	ft_screen_row(t_map *map, int i)
{
	int	j;
	int	d[2];

	j = 0;
	map->ms[i] = malloc((map->w) * sizeof(t_coord));
	while (j < map->w)
	{
		map->ms[i][j].x = map->xs
			+ (map->mr[i][j].x - map->mr[i][j].y) * cos(M_PI / 6.0);
		map->ms[i][j].y = map->ys
			+ ((map->mr[i][j].x + map->mr[i][j].y) / 2.0) - map->mr[i][j].z;
		if (map->mr[i][j].c)
			map->ms[i][j].c = map->mr[i][j].c;
		else
			map->ms[i][j].c = ft_colour(map, i, +j, d);
		j++;
	}
}

void	ft_fill_screen(t_map *map)
{
	int		i;

	i = 0;
	map->ms = malloc((map->h + 1) * sizeof(t_coord *));
	while (i < map->h)
	{
		ft_screen_row(map, i);
		i++;
	}
	map->ms[map->h] = NULL;
}

/*
void	ft_screen_row_cabinet(t_map *map, int i)
{
	int			j;

	j = 0;
	while (j < map->w)
	{
		map->ms[i][j].x = map->xs
			+ (map->mr[i][j].x + map->mr[i][j].z / 4);
		map->ms[i][j].y = map->ys
			+ (map->mr[i][j].y + map->mr[i][j].z * sin(M_PI / 3.0) / 2.0);
		if (map->mr[i][j].c)
			map->ms[i][j].c = map->mr[i][j].c;
		else
			map->ms[i][j].c = ft_colour(map, i, j);
		j++;
	}
}

void	ft_fill_screen_cabinet(t_map *map)
{
	int		i;

	i = 0;
	while (i < map->h)
	{
		ft_screen_row_cabinet(map, i);
		i++;
	}
}*/

//beware of printf
/*
void	ft_show_coord(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->mo[i])
	{
		j = 0;
		while (j < map->w)
		{
			map->ax = 0;
			//printf("x = %f, y = %f, z = %f, c = %x\n",
			//	map->mo[i][j].x, map->mo[i][j].y,
			//	map->mo[i][j].z, map->mo[i][j].c);
			j++;
		}
		i++;
	}
}

//beware of printf
void	ft_show_coord2(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->mr[i])
	{
		j = 0;
		while (j < map->w)
		{
			//printf("x = %f, y = %f, z = %f, c = %x\n",
			//	map->mr[i][j].x, map->mr[i][j].y,
			//	map->mr[i][j].z, map->mr[i][j].c);
			j++;
		}
		i++;
	}
}

void	ft_show_coord3(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->ms[i])
	{
		j = 0;
		while (j < map->w)
		{
			//ft_printf("x = %d, y = %d, c = %x\n",
			//	map->ms[i][j].x, map->ms[i][j].y,
			//	map->ms[i][j].c);
			j++;
		}
		i++;
	}
}
*/

void	ft_fill_map(t_map *map, char *mapfile)
{
	int		fd;
	char	*fdfmap;
	char	*line;

	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		exit(-1);
	line = get_next_line(fd);
	fdfmap = ft_strdup("");
	while (line)
	{
		fdfmap = ft_strjoin_freeleft(fdfmap, line);
		free (line);
		line = get_next_line(fd);
		map->h++;
	}
	map->m = ft_split(fdfmap, '\n');
	free(fdfmap);
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
	map->xs = 200;
	map->ys = 200;
	map->ax = 0;
	map->ay = 0;
	map->az = 0;
}

void	ft_free_double(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	ft_free(t_map *map)
{
	ft_free_split(map->m);
	ft_free_double((void **)map->mo);
	ft_free_double((void **)map->mr);
	ft_free_double((void **)map->ms);
}

void	ft_fdf2(t_max *max)
{
	if (!(max->img))
	{
		mlx_close_window(max->mlx);
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(max->mlx, max->img, 0, 0) == -1)
	{
		mlx_close_window(max->mlx);
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	mlx_loop_hook(max->mlx, ft_hook, max);
	mlx_loop_hook(max->mlx, ft_colourize, max);
	mlx_loop(max->mlx);
	ft_free(max->map);
	mlx_terminate(max->mlx);
}

void	ft_fdf(t_max *max, char *mapfile)
{
	mlx_t		*mlx;
	t_map		mapt;
	mlx_image_t	*image;

	max->map = &mapt;
	ft_init_map(max->map);
	ft_fill_map(max->map, mapfile);
	ft_fill_coord(max->map);
	ft_init_coord(max->map);
	ft_fill_screen(max->map);
	mlx = mlx_init(1600, 900, "FDF", true);
	if (!mlx)
	{
		puts(mlx_strerror(mlx_errno));
		exit(-999);
	}
	max->mlx = mlx;
	image = mlx_new_image(mlx, 1600, 900);
	max->img = image;
	ft_fdf2(max);
}

int32_t	main(int32_t argc, char *argv[])
{
	t_max	max;
	int		n;

	if (argc != 2)
	{
		ft_printf_fd(2, "%91CError%0C\n%61CWrong numbr of arguments%0C\n");
		return (1);
	}
	n = ft_strlen(argv[1]);
	if (n < 5 || argv[1][n - 1] != 'f' || argv[1][n - 2] != 'd'
		|| argv[1][n - 3] != 'f' || argv[1][n - 4] != '.')
	{
		ft_printf_fd(2, "%91CError%0C\n%61CThis is not a valid map file%0C\n");
		return (2);
	}
	ft_fdf(&max, argv[1]);
	return (EXIT_SUCCESS);
}
