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

static int	ft_strlen2(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		i++;
	}
	return (i);
}

int	ft_base_pos (const char *base, char c)
{
	int	i;

	i = 0;
	while (base[i] != c)
	{
		i++;
	}
	return (i);
}

//add check that str[i] is in base string
unsigned int	ft_atoi_base(const char *base, char* str)
{
	int				baselen;
	int				i;
	unsigned int	num;

	num = 0;
	i = 0;
	baselen = ft_strlen2(base);
	while (str[i])
	{
		num = num * baselen + ft_base_pos(base, str[i]);
		i++;
	}
	return (num);	
}

/*
int	main(void)
{
	const char	*base = "0123456789ABCDEF";
	char		*str = "FF";

	printf("%x\n", ft_atoi_base(base, str));
	printf("%x\n", ft_atoi_base(base, "FFAB01CD"));
	return (0);
}
*/