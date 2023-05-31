/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:43:08 by okraus            #+#    #+#             */
/*   Updated: 2023/05/31 19:31:23 by okraus           ###   ########.fr       */
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

// typedef struct map_s
// {
// 	char	**m;		//map saved in array
// 	int		w;			//width of map
// 	int		h;			//height of map
// 	int		p;			//player status 1-alive, 0 dead
// 	int		px;			//player position on map the x axis
// 	int		py;			//player position on map the y axis
//						//add player direction?
// 	int		ct;			//total number of collectibles
//	int		cr;			//number of remaining collectibles
// 	int		*c;			//collectible status 
// 	int		*cx;		//collectible position on the x axis
// 	int		*cy;		//collectible position on the y axis
// 	int		et;			//total number of enemies
//						//add enemy remaining?
// 	int		*e;			//array of enemies 0 dead, 1 alive
// 	int		*ex;		//enemy position on map the x axis
// 	int		*ey;		//enemy position on map the y axis
//						//add enemy direction?
//	int		x;			// exit status 0 closed, 1 open
//	int		xx;			// exit X
//	int		xy;			// exit Y
//	int		steps;		// number of steps player did
// } map_t;


// typedef struct s_point
// {
// 	double	x; //x
// 	double	y; //y
// 	double	z; //z
// 	int		c; //colour it contains <<8 |= 0xFF, if no, then 0;
// }	t_point;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	unsigned int		c;
}	t_point;

typedef struct s_coord
{
	int		x;
	int		y;
	unsigned int		c;
}	t_coord;

typedef struct s_map
{
	char	**m;	//
	t_point	**mo;	//original map coordinates
	t_point	**mr;	//rotated orig
	t_coord	**ms;	//screen
	int		w;		//width of map
	int		h;		//height of map
	int		d;		//distance of points
	int		max;	//max height on map
	int		min;	//min height on map
	int		x;
	int		y;
}	t_map;

typedef struct s_max
{
	mlx_t			*mlx;
	t_map			*map;
	mlx_image_t		*img;
}	t_max;

// PROTOTYPES

//	ft_draw

#endif
