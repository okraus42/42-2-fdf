/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:35:23 by okraus            #+#    #+#             */
/*   Updated: 2023/05/31 18:55:03 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/fdf.h"

void	ft_hook(void *param)
{
	t_max	*max;

	max = param;
	if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(max->mlx);
	}
	/*if (max->map->p && mlx_is_key_down(max->mlx, MLX_KEY_UP))
	{
		
	}
	if (max->map->p && mlx_is_key_down(max->mlx, MLX_KEY_DOWN))
	{
		
	}
	if (max->map->p && mlx_is_key_down(max->mlx, MLX_KEY_LEFT))
	{
		
	if (max->map->p && mlx_is_key_down(max->mlx, MLX_KEY_RIGHT))
	{
		
	}*/
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
		ft_printf("%c\n", str[i]);
		i++;
	}
	i = 0;
	while (str && str[i] && str[i] != ',')
	{
		ft_printf("%d\n", str[i]);
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
		exit(-1);//wrong map need to free stuff
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
		i++;
	}
	map->mo[map->h] = NULL;
	free(row);
}

void	ft_show_coord(t_map *map)
{
	int	i;
	int j;

	i = 0;
	while (map->mo[i])
	{
		j = 0;
		while (j < map->w)
		{
			printf("x = %f, y = %f, z = %f, c = %x\n", map->mo[i][j].x, map->mo[i][j].y, map->mo[i][j].z, map->mo[i][j].c);
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
	//ft_update_map(max->map);
	//ft_print_map(max->map);
	ft_put_strarray(max->map->m);
	mlx = mlx_init(1600, 900, "FDF", true);
	if (!max->mlx)
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
	ft_printf("ooopsie\n");
	mlx_loop(max->mlx);
	ft_printf("ooops\n");
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
