/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 16:34:15 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/28 17:51:51 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_fillit.h"

/*
** insert a certain tetra ina a row at a certain slot
** avoiding the '.' part of the tetra
*/

int		insert_tetra_row(char **row, char **tetra, int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tetra[i] != 0)
	{
		while (tetra[i][j] != 0)
		{
			if (tetra[i][j] != '.')
			{
				row[x + i][y + j] = tetra[i][j];
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

/*
** cleans up after a wrong placement
*/

int		clean_tetra_row(char **row, char **tetra, int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tetra[i] != 0)
	{
		while (tetra[i][j] != 0)
		{
			if (tetra[i][j] != '.')
			{
				row[x + i][y + j] = '.';
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

/*
** check fi the isnertion of a tetra is valid
*/

int		insert_checker(char **row, char **tetra, int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tetra[i] != 0)
	{
		if (row[x + i] == 0)
			return (0);
		while (tetra[i][j] != 0)
		{
			if (row[x + i][y + j] == 0)
				return (0);
			if (tetra[i][j] != '.' && row[x + i][y + j] != '.')
			{
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

/*
** a rather small big fucking solver
*/

int		bfs_big_fucking_solver(char **row, char ***tetra, int b)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (tetra[b] == 0)
		return (0);
	while (row[i] != 0)
	{
		while (row[i][j] != 0)
		{
			if (insert_checker(row, tetra[b], i, j))
			{
				insert_tetra_row(row, tetra[b], i, j);
				if (!bfs_big_fucking_solver(row, tetra, b + 1))
					return (0);
				clean_tetra_row(row, tetra[b], i, j);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (1);
}

int		solve(char ***tetra)
{
	int		min_size;
	char	**row;

	min_size = ft_floor_sqrt(num_tetra(tetra) * 4);
	row = gen_row(min_size, min_size, '.');
	while (bfs_big_fucking_solver(row, tetra, 0))
	{
		min_size++;
		free_row(row);
		row = gen_row(min_size, min_size, '.');
	}
	print_row(row);
	return (0);
}
