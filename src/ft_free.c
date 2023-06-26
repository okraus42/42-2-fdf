/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:12:15 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:17:31 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fdf.h"

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
	if (map->m)
		ft_free_split(map->m);
	if (map->mo)
		ft_free_double((void **)map->mo);
	if (map->mr)
		ft_free_double((void **)map->mr);
	if (map->ms)
		ft_free_double((void **)map->ms);
}
