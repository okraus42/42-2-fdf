/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:35:23 by okraus            #+#    #+#             */
/*   Updated: 2023/06/01 15:29:43 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/fdf.h"

/*unsigned int	ft_abs(int x, int y)
{
	if (x > y)
		return (x - y);
	else
		return (y - x);
}*/

void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

int	main(void)
{
	int a = 5;
	int b = 6;

	ft_swap(&a, &b);
	printf("%i, %i\n", a, b);
	return (0);
}

