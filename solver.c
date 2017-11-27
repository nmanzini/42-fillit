/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 16:34:15 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/27 17:36:53 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_fillit.h"

/*
** returns the floored squareroot, carefull really buggy on edge cases
*/

int		ft_floor_sqrt(int value)
{
	int i;
	while (value > 1)
	{
		i = 1;
		while (i*i <= value)
		{
			if (i*i == value)
				return (i);
			i++;
		}
		value--;
	}
	return (0);
}

/*
** calculates the number of teraminos in the list
*/

int		num_tetra(char ***tetra)
{
	int b;

	b = 0;
	while(tetra[b] != 0)
		b++;
	return(b);
}

/*
** creates a square matrix filled with dots;
*/

// char	**grid(int size)
// {
// 	int i;
// 	int j;

// 	b = 0;
// 	i = 0;
// 	matrix = (char**)malloc(sizeof(char*) * (size + 1));
// 	while (b < size)
// 	{
// 		matrix[b] = (char**)malloc(sizeof(char*) * (m + 1));
// 		while (i < 4)
// 			matrix[b][i++] = ft_strdup("....");
// 		b++;
// 		i = 0;
// 	}
// 	return (matrix);

// }

/*
** calls for the solution
*/

int		solve(char ***tetra)
{
	ft_putendl("START of solve");
	int min_size;

	min_size = ft_floor_sqrt(num_tetra(tetra) * 4);
	ft_putnbr(num_tetra(tetra));
	ft_putendl(" = num of blocks");
	ft_putnbr(min_size);
	ft_putendl(" = minimum side size of solution square");

	return (0);
}