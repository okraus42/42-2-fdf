/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colour1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:11:43 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:13:37 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fdf.h"

static unsigned int	ft_mix_colour2(unsigned int d[2], unsigned int rgb[4],
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
