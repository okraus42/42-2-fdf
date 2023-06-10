/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:35:23 by okraus            #+#    #+#             */
/*   Updated: 2023/06/10 16:44:47 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/fdf.h"

void	ft_fill_screen(t_map *map);

void	ft_hook(void *param)
{
	t_max	*max;

	max = param;
	if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(max->mlx);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_UP))
	{
		max->map->ys += 50;
		//ft_printf("up  %i\n", max->map->ys);
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_DOWN))
	{
		max->map->ys -= 50;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_LEFT))
	{
		max->map->xs += 50;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_RIGHT))
	{
		max->map->xs -= 50;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_ADD) && max->map->z < 64)
	{
		max->map->z += 1;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_SUBTRACT) && max->map->z > 1)
	{
		max->map->z -= 1;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_MULTIPLY) && max->map->q > 1)
	{
		max->map->q -= 1;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_DIVIDE) && max->map->q < 64)
	{
		max->map->q += 1;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_Q))
	{
		max->map->ax -= 0.03125;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_E))
	{
		max->map->ax += 0.03125;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_W))
	{
		max->map->az -= 0.03125;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_S))
	{
		max->map->az += 0.03125;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_A))
	{
		max->map->ay -= 0.03125;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_D))
	{
		max->map->ay += 0.03125;
	}
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
// By switching the x and y axis an implementation for positive or negative steep slopes can be written as

unsigned int	ft_uabsdif(unsigned int a, unsigned int b)
{
	if (a < b)
		return (b - a);
	else
		return (a - b);
}

void	ft_uswap(unsigned int *a, unsigned int *b)
{
	unsigned int	c;

	c = *b;
	*b = *a;
	*a = c;
}

unsigned int	ft_umin(unsigned int a, unsigned int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

unsigned int	ft_mix_colour(int x[3], int y[3], unsigned int c[2])
{
	unsigned int	d[2];
	unsigned int	rgb[4];
	unsigned int	r[4];

	d[0] = ft_abs(x[2] - x[0]) + ft_abs(y[2] - y[0]);
	d[1] = ft_abs(x[1] - x[0]) + ft_abs(y[1] - y[0]);
	if (!d[1])
		d[1] = 1;
	// rgb[0][0] = (ft_umin(c[0] & 0xFF000000, c[1] & 0xFF000000)) >> 24;
	// rgb[0][1] = (ft_umin(c[0] & 0xFF0000, c[1] & 0xFF0000)) >> 16;
	// rgb[0][2] = (ft_umin(c[0] & 0xFF00, c[1] & 0xFF00)) >> 8;
	// rgb[0][3] = ft_umin(c[0] & 0xFF, c[1] & 0xFF);
	rgb[0] = (ft_uabsdif(c[0] & 0xFF000000, c[1] & 0xFF000000)) >> 24;
	rgb[1] = (ft_uabsdif(c[0] & 0xFF0000, c[1] & 0xFF0000)) >> 16;
	rgb[2] = (ft_uabsdif(c[0] & 0xFF00, c[1] & 0xFF00)) >> 8;
	rgb[3] = ft_uabsdif(c[0] & 0xFF, c[1] & 0xFF);
	// ft_printf("testcolour2\n");
	// ft_printf("\nx0 = %i, x1 = %i, x2 = %i\n", x[0], x[1], x[2]);
	// ft_printf("y0 = %i, y1 = %i, y2 = %i\n", y[0], y[1], y[2]);
	// ft_printf("c0 = %x, c1 = %x\n", c[0], c[1]);
	// ft_printf("d0 = %u, d1 = %u\n", d[0], d[1]);
	// ft_printf("r0 = %x, r1 = %x, r2 = %x, r3 = %x\n", r[0], r[1], r[2], r[3]);
	if ((c[0] & 0xFF000000) < (c[1] & 0xFF000000))
	{
		r[0] = ((rgb[0] * d[0]) / d[1] + ((c[0] & 0xFF000000) >> 24)) << 24;
	}
	else
	{
		r[0] = (((c[1] & 0xFF000000) >> 24) - ((rgb[0] * d[0]) / d[1])) << 24;
	}
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
	// ft_printf("\nx0 = %i, x1 = %i, x2 = %i\n", x[0], x[1], x[2]);
	// ft_printf("y0 = %i, y1 = %i, y2 = %i\n", y[0], y[1], y[2]);
	// ft_printf("c0 = %x, c1 = %x\n", c[0], c[1]);
	// ft_printf("d0 = %u, d1 = %u\n", d[0], d[1]);
	// ft_printf("r0 = %x, r1 = %x, r2 = %x, r3 = %x\n", r[0], r[1], r[2], r[3]);
	return (r[0] | r[1] | r[2] | r[3]);
}

void	ft_plot_line_low(t_max *max, int x[3], int y[3], unsigned int c[2])
{
	int	dx;
	int	dy;
	int	yi;
	int	d;

	dx = x[1] - x[0];
	dy = y[1] - y[0];
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy *= -1;
	}
	d = (2 * dy) - dx;
	x[2] = x[0];
	y[2] = y[0];
	while (x[2] <= x[1])
	{
		// create function to fix colour
		if (x[2] > 0 && x[2] < 1600 && y[2] > 0 && y[2] < 900)
			mlx_put_pixel(max->img, x[2], y[2], ft_mix_colour(x, y, c));
		//ft_printf("x0[%i]|x1[%i]|x2[%i]|y0[%i]|y1[%i]|y2[%i]|dx[%i]|dy[%i]|yi[%i]|d[%i]\n", x[0], x[1], x[2], y[0], y[1], y[2], dx, dy, yi, d);
		if (d > 0)
		{
			y[2] = y[2] + yi;
			d += 2 * (dy - dx);
		}
		else
			d = d + 2 * dy;
		x[2]++;
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
// A complete solution would need to detect whether x1 > x0 or y1 > y0 and reverse the input coordinates before drawing, thus

void	ft_plot_line_high(t_max *max, int x[3], int y[3], unsigned int c[2])
{
	int	dx;
	int	dy;
	int	xi;
	int	d;

	dx = x[1] - x[0];
	dy = y[1] - y[0];
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx *= -1;
	}
	d = (2 * dx) - dy;
	x[2] = x[0];
	y[2] = y[0];
	while (y[2] <= y[1])
	{
		// create function to fix colour
		// ft_printf("testalpha0\n");
		// ft_printf("x0[%i]|x1[%i]|x2[%i]|y0[%i]|y1[%i]|y2[%i]|dx[%i]|dy[%i]|xi[%i]|d[%i]\n", x[0], x[1], x[2], y[0], y[1], y[2], dx, dy, xi, d);
		if (x[2] > 0 && x[2] < 1600 && y[2] > 0 && y[2] < 900)
			mlx_put_pixel(max->img, x[2], y[2], ft_mix_colour(x, y, c));
		// ft_printf("testalpha1\n");
		// ft_printf("x0[%i]|x1[%i]|x2[%i]|y0[%i]|y1[%i]|y2[%i]|dx[%i]|dy[%i]|xi[%i]|d[%i]\n", x[0], x[1], x[2], y[0], y[1], y[2], dx, dy, xi, d);
		if (d > 0)
		{
			x[2] = x[2] + xi;
			d = d + (2 * (dx - dy));
		}
		else
			d = d + 2 * dx;
		y[2]++;
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

void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

void	ft_super_swap(int a[3], int b[3])
{
	ft_swap(&a[0], &a[1]);
	ft_swap(&b[0], &b[1]);
}

void	ft_plot_line_hor(t_max *max, int i, int j)
{
	t_map			*m;
	int				x[3];
	int				y[3];
	unsigned int	c[2];

	m = max->map;
	x[0] = m->ms[i][j].x;
	y[0] = m->ms[i][j].y;
	c[0] = m->ms[i][j].c;
	x[1] = m->ms[i][j + 1].x;
	y[1] = m->ms[i][j + 1].y;
	c[1] = m->ms[i][j + 1].c;
	if (ft_abs(y[1] - y[0]) < ft_abs(x[1] - x[0]))
	{
		if (x[0] > x[1])
		{
			ft_swap(&x[0], &x[1]);
			ft_swap(&y[0], &y[1]);
			ft_uswap(&c[0], &c[1]);
		}
		ft_plot_line_low(max, x, y, c);
	}
	else
	{
		if (y[0] > y[1])
		{
			ft_swap(&x[0], &x[1]);
			ft_swap(&y[0], &y[1]);
			ft_uswap(&c[0], &c[1]);
		}
		ft_plot_line_high(max, x, y, c);
	}
}

void	ft_plot_line_ver(t_max *max, int i, int j)
{
	t_map			*m;
	int				x[3];
	int				y[3];
	unsigned int	c[2];

	m = max->map;
	x[0] = m->ms[i][j].x;
	y[0] = m->ms[i][j].y;
	c[0] = m->ms[i][j].c;
	x[1] = m->ms[i + 1][j].x;
	y[1] = m->ms[i + 1][j].y;
	c[1] = m->ms[i + 1][j].c;
	if (ft_abs(y[1] - y[0]) < ft_abs(x[1] - x[0]))
	{
		if (x[0] > x[1])
		{
			ft_swap(&x[0], &x[1]);
			ft_swap(&y[0], &y[1]);
			ft_uswap(&c[0], &c[1]);
		}
		ft_plot_line_low(max, x, y, c);
	}
	else
	{
		if (y[0] > y[1])
		{
			ft_swap(&x[0], &x[1]);
			ft_swap(&y[0], &y[1]);
			ft_uswap(&c[0], &c[1]);
		}
		ft_plot_line_high(max, x, y, c);
	}
}

void	ft_place_line(t_max *max, int i, int j)
{
	t_map	*m;

	m = max->map;
	if (i != m->h - 1)
		ft_plot_line_ver(max, i , j);
	if (j != m->w - 1)
		ft_plot_line_hor(max, i , j);
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
			map->mr[y][x].z = map->mo[y][x].z * 16.0 / map->q;
			ft_rotate_map(map->ax, &map->mr[y][x].y, &map->mr[y][x].z);
			ft_rotate_map(map->ay, &map->mr[y][x].x, &map->mr[y][x].z);
			ft_rotate_map(map->az, &map->mr[y][x].x, &map->mr[y][x].y);
			x++;
		}
		y++;
	}
}

void	ft_update_screen(t_map *map)
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
		//ft_printf("test-z1\n");
		while (j < m->w)
		{
			//check that pixel is in image
			//ft_printf("test-z2\n");
			ft_place_line(max, i , j);
			//ft_printf("test-z3\n");
			if (m->ms[i][j].x > 0 && m->ms[i][j].x < 1600 && m->ms[i][j].y > 0 && m->ms[i][j].y < 900)
				mlx_put_pixel(max->img, m->ms[i][j].x, m->ms[i][j].y, m->ms[i][j].c);
			j++;
		}
		i++;
	}
}

// -----------------------------------------------------------------------------

unsigned int	ft_atoi_base(const char *base, char* str);

int	ft_get_color(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		str[i] = ft_toupper(str[i]);
		//ft_printf("%c\n", str[i]);
		i++;
	}
	i = 0;
	while (str && str[i] && str[i] != ',')
	{
		//ft_printf("%d\n", str[i]);
		i++;
	}
	if (str[i] == ',' && str[i + 1] == '0' && str[i + 2] == 'X')
		return(ft_atoi_base("0123456789ABCDEF", &str[i + 3]) << 8 | 0xFF);
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
		exit(-1);//wrong9 *  map need to free stuff
	j = 0;
	map->mo[i] = malloc((map->w) * sizeof(t_point));;
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
	ft_free_split(row);
}

void	ft_init_row(t_map *map, int i)
{
	int			j;

	j = 0;
	map->mr[i] = malloc((map->w) * sizeof(t_point));;
	while (j < map->w)
	{
		map->mr[i][j].y = (map->mo[i][j].y) + (map->z * (i - map->h / 2));
		map->mr[i][j].x = (map->mo[i][j].x) + (map->z * (j - map->w / 2));
		map->mr[i][j].z = map->mo[i][j].z;
		map->mr[i][j].c = map->mo[i][j].c;
		j++;
	}
}

void	ft_init_coord(t_map *map)
{
	int		i;

	i = 0;
	map->mr = malloc((map->h + 1) * sizeof(t_point *));
	while (i < map->h)
	{
		ft_init_row(map, i);
		i++;
	}
	map->mr[map->h] = NULL;
}

void	ft_screen_row(t_map *map, int i)
{
	int			j;

	j = 0;
	map->ms[i] = malloc((map->w) * sizeof(t_coord));
	while (j < map->w)
	{
		map->ms[i][j].x = map->xs + (map->mr[i][j].x - map->mr[i][j].y) * cos(M_PI / 6.0);
		map->ms[i][j].y = map->ys + ((map->mr[i][j].x + map->mr[i][j].y) / 2.0) - map->mr[i][j].z;
		if (map->mr[i][j].c)
			map->ms[i][j].c = map->mr[i][j].c;
		else
			map->ms[i][j].c = 0xFFFF00FF;
		//ft_printf("i=%i,j=%i,x=%i,y=%i\n", i, j, map->ms[i][j].x, map->ms[i][j].y);
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

//beware of printf
void	ft_show_coord(t_map *map)
{
	int	i;
	int j;

	i = 0;
	while (map->mo[i])
	{
		j = 0;
		while (j < map->w)
		{map->ax = 0;
			//printf("x = %f, y = %f, z = %f, c = %x\n", map->mo[i][j].x, map->mo[i][j].y, map->mo[i][j].z, map->mo[i][j].c);
			j++;
		}
		i++;
	}
}

//beware of printf
void	ft_show_coord2(t_map *map)
{
	int	i;
	int j;

	i = 0;
	while (map->mr[i])
	{
		j = 0;
		while (j < map->w)
		{
			printf("x = %f, y = %f, z = %f, c = %x\n", map->mr[i][j].x, map->mr[i][j].y, map->mr[i][j].z, map->mr[i][j].c);
			j++;
		}
		i++;
	}
}

void	ft_show_coord3(t_map *map)
{
	int	i;
	int j;

	i = 0;
	while (map->ms[i])
	{
		j = 0;
		while (j < map->w)
		{
			//ft_printf("x = %d, y = %d, c = %x\n", map->ms[i][j].x, map->ms[i][j].y, map->ms[i][j].c);
			j++;
		}
		i++;
	}
}

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
	map->x = 0;
	map->y = 0;
	map->z = 4;
	map->q = 16;
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

void	ft_free(t_map* map)
{
	ft_free_split(map->m);
	ft_free_double((void **)map->mo);
	ft_free_double((void **)map->mr);
	ft_free_double((void **)map->ms);
}

void	ft_fdf(t_max *max, char *mapfile)
{
	mlx_t				*mlx;
	t_map				mapt;
	mlx_image_t 		*image;

	max->map = &mapt;
	ft_init_map(max->map);
	ft_fill_map(max->map, mapfile);
	//ft_test_map(max->map);
	ft_fill_coord(max->map);
	ft_show_coord(max->map);
	ft_init_coord(max->map);
	//ft_rotate_coord(max->map);
	ft_show_coord2(max->map);
	ft_fill_screen(max->map);
	ft_show_coord3(max->map);
	//ft_update_map(max->map);
	//ft_print_map(max->map);
	ft_put_strarray(max->map->m);
	mlx = mlx_init(1600, 900, "FDF", true);
	if (!mlx)
	{
		puts(mlx_strerror(mlx_errno));
		exit(-999);
	}
	max->mlx = mlx;
	image = mlx_new_image(mlx, 1600, 900);
	max->img = image;
	if (!(max->img))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, max->img, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	ft_printf("ohno\n");
	mlx_loop_hook(max->mlx, ft_hook, max);
	mlx_loop_hook(max->mlx, ft_colourize, max);
	ft_printf("ooopsie\n");
	mlx_loop(max->mlx);
	ft_printf("ooops\n");
	ft_free(&mapt);
	mlx_terminate(max->mlx);
}

int32_t	main(int32_t argc, char *argv[])
{
	t_max				max;

	if (argc != 2)
	{
		ft_printf_fd(2, "%9CError%0C\n");
		return (1);
	}
	ft_fdf(&max, argv[1]);
	return (EXIT_SUCCESS);
}
