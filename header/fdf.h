/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:43:08 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:19:06 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

// INCLUDES

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <sys/wait.h> //check if needed, but it must be
# include <time.h> //check if needed
# include <sys/types.h> //open function1
# include <sys/stat.h> //open function2
# include <fcntl.h> //open function3
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/header/libft.h"

// DEFINITIONS

// STRUCTURES
// FDF structure

// typedef struct s_map
// {
// 	char	**m;	//
// 	t_point	**mo;	//original map coordinates
// 	t_point	**mr;	//rotated orig
// 	t_coord	**ms;	//screen
// 	int		w;		//width of map
// 	int		h;		//height of map
// 	int		d;		//distance of points
// 	int		max;	//max height on map
// 	int		min;	//min height on map
// 	int		xs;		//x shift
// 	int		ys;		//y shift
// 	int		p;		//projection (0 isometric, 1 cabinet)
// 	int		x;
// 	int		y;
// 	int		z;		//level of zoom
// 	double	q;		//height of stuff
// 	double	ax;
// 	double	ay;		//angles of rotation around x/y/z axis;
// 	double	az;
// }	t_map;

// typedef struct s_point
// {
// 	double	x; //x
// 	double	y; //y
// 	double	z; //z
// 	int		c; //colour it contains <<8 |= 0xFF, if no, then 0;
// }	t_point;

typedef struct s_point
{
	double			x;
	double			y;
	double			z;
	unsigned int	c;
}	t_point;

typedef struct s_coord
{
	int				x;
	int				y;
	unsigned int	c;
}	t_coord;

typedef struct s_line
{
	int				x[3];
	int				y[3];
	unsigned int	c[2];
	int				dx;
	int				dy;
	union
	{
		int			xi;
		int			yi;
	};
	int				d;
}	t_line;

typedef struct s_map
{
	char	**m;
	t_point	**mo;
	t_point	**mr;
	t_coord	**ms;
	int		w;
	int		h;
	int		d;
	int		max;
	int		min;
	int		xs;
	int		ys;
	int		p;
	int		x;
	int		y;
	int		z;
	double	q;
	double	ax;
	double	ay;
	double	az;
}	t_map;

typedef struct s_max
{
	mlx_t			*mlx;
	t_map			*map;
	mlx_image_t		*img;
}	t_max;

// PROTOTYPES

//	ft_hook
void			ft_hook(void *param);
void			ft_hook2(t_max	*max);
void			ft_super_swap(int a[3], int b[3], unsigned int c[2]);
void			ft_rotate_map(double angle, double *x, double *y);

//	ft_colour1
unsigned int	ft_mix_colour(int x[3], int y[3], unsigned int c[2]);

//	ft_plot
void			ft_plot_line_low(t_max *max, t_line l);
void			ft_plot_line_high(t_max *max, t_line l);
void			ft_plot_line_hor(t_max *max, int i, int j);
void			ft_plot_line_ver(t_max *max, int i, int j);
void			ft_place_line(t_max *max, int i, int j);

//	ft_update
void			ft_update_map(t_map *map);
void			ft_update_screen_isometric(t_map *map);
void			ft_update_screen_cabinet(t_map *map);
void			ft_update_screen(t_map *map);

//	ft_colour2
void			ft_black(t_max *max);
void			ft_colourize(void *param);
int				ft_get_color(char *str);

//	ft_init
void			ft_init_row(t_map *map, int i);
void			ft_init_coord(t_map *map);
void			ft_init_map(t_map *map);

//	ft_colour3
unsigned int	ft_colour(t_map *map, int i, int j);

//	ft_fill
void			ft_screen_row(t_map *map, int i);
void			ft_fill_screen(t_map *map);
void			ft_fill_map(t_map *map, char *mapfile);
void			ft_fill_row(t_map *map, char **row, int i);
void			ft_fill_coord(t_map *map);

//	ft_free
void			ft_free_double(void **ptr);
void			ft_free(t_map *map);

#endif
