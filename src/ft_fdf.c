/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:35:23 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:17:49 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fdf.h"

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

void	ft_fdf2(t_max *max)
{
	if (!(max->img))
	{
		mlx_close_window(max->mlx);
		ft_printf_fd (2, "%s\n", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(max->mlx, max->img, 0, 0) == -1)
	{
		mlx_close_window(max->mlx);
		ft_printf_fd (2, "%s\n", mlx_strerror(mlx_errno));
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
		ft_printf_fd (2, "%s\n", mlx_strerror(mlx_errno));
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
