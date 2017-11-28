/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:29:53 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/28 18:32:01 by nmanzini         ###   ########.fr       */
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
		while (i * i <= value)
		{
			if (i * i == value)
				return (i);
			i++;
		}
		value++;
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
	while (tetra[b] != 0)
		b++;
	return (b);
}

/*
** creates a square matrix filled with dots;
** every row zero terminated, and last row equal to NULL;
*/

char	**gen_row(int m, int n, char c)
{
	int		i;
	int		j;
	char	**row;

	i = 0;
	j = 0;
	row = (char**)malloc(sizeof(char*) * (n + 1));
	while (i < n)
	{
		row[i] = (char*)malloc(sizeof(char) * (m + 1));
		while (j < m)
			row[i][j++] = c;
		row[i][j] = 0;
		j = 0;
		i++;
	}
	row[i] = NULL;
	return (row);
}

/*
** frees the grid
*/

int		**free_row(char **row)
{
	int	i;

	i = 0;
	while (row[i] != 0)
	{
		free(row[i]);
		i++;
	}
	free(row[i]);
	row = NULL;
	return (0);
}

/*
** prints a row or matrix of any size
*/

int		print_row(char **row)
{
	int i;

	i = 0;
	while (row[i] != 0)
	{
		ft_putendl(row[i]);
		i++;
	}
	return (0);
}
