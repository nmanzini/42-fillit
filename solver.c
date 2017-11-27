/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 16:34:15 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/27 19:38:33 by nmanzini         ###   ########.fr       */
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
** every row zero terminated, and last row equal to NULL;
*/

char	**gen_grid(int m,int n)
{
	int i;
	int j;
	char **row;

	i = 0;
	j = 0;

	row = (char**)malloc(sizeof(char*) * (n + 1));
	while (i < n)
	{
		row[i] = (char*)malloc(sizeof(char) * (m + 1));
		while (j < m)
			row[i][j++] = '.';
		row[i][j] = 0;
		j = 0;
		i++;
	}
	row[i] = NULL;
	return (row);
}

/*
** prints a grid or matrix of any size
*/

int		print_grid(char **row)
{
	int i;

	i = 0;
	while (row[i] != 0)
	{
		ft_putendl(row[i]);
		i++;
	}
	return(0);
}

/*
** insert a certain tetra ina a grid at a certain slot
** avoiding the '.' part of the tetra
*/

int		insert_tetra_grid(char **row, char **tetra, int x, int y)
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
				row[x + i][y + j] =  tetra[i][j];
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

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

int		insert_complete(char **row, char **tetra, int x, int y)
{
	ft_putendl("cheking insertion of tetra in grid");
	if (insert_checker(row,tetra,x,y))
	{
		ft_putendl("Passed");
		insert_tetra_grid(row,tetra,x,y);
	}
	else
		ft_putendl("Not possible");
}

int		solve(char ***tetra)
{
	ft_putendl("START of solve");
	int min_size;
	char **grid;

	min_size = ft_floor_sqrt(num_tetra(tetra) * 4);
	ft_putnbr(num_tetra(tetra));
	ft_putendl(" = num of blocks");
	ft_putnbr(min_size);
	ft_putendl(" = minimum side size of solution square");
	ft_putendl("Generating solution grid of size min_size");
	grid = gen_grid(min_size,min_size);
	ft_putendl("Printing said grid");
	print_grid(grid);

	insert_complete(grid,tetra[0],0,0);
	print_grid(grid);
	insert_complete(grid,tetra[0],1,1);
	print_grid(grid);
	insert_complete(grid,tetra[0],2,2);
	print_grid(grid);
	return (0);
}