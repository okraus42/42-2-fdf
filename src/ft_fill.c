/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:12:11 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:17:11 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fdf.h"

void	ft_screen_row(t_map *map, int i)
{
	int	j;

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
			map->ms[i][j].c = ft_colour(map, i, j);
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

void	ft_fill_row(t_map *map, char **row, int i)
{
	int			j;

	j = 0;
	while (row[j])
		j++;
	if (!map->w)
		map->w = j;
	if (map->w != j)
	{
		ft_free(map);
		ft_free_split(row);
		ft_printf_fd(2, "%21CBadly formatted map%0C\n");
		exit(-1);
	}
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

void	ft_fill_map(t_map *map, char *mapfile)
{
	int		fd;
	char	*fdfmap;
	char	*line;

	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(2, "%41CCould not open the mapfile, does it ");
		ft_printf_fd(2, "exist and does it have read permissions?%0C\n");
		exit(-1);
	}
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
