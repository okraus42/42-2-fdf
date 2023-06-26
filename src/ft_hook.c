/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:11:34 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:12:56 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fdf.h"

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

void	ft_super_swap(int a[3], int b[3], unsigned int c[2])
{
	ft_swap(&a[0], &a[1]);
	ft_swap(&b[0], &b[1]);
	ft_uswap(&c[0], &c[1]);
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
