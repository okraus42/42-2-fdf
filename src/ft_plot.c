/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:11:58 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:18:44 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fdf.h"

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
