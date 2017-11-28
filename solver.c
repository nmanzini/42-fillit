/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 16:34:15 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/28 13:59:52 by nmanzini         ###   ########.fr       */
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
** prints a row or matrix of any size
*/

int		print_row(char **row)
{
	int i;

	i = 0;
	ft_putchar(10);
	while (row[i] != 0)
	{
		ft_putendl(row[i]);
		i++;
	}
	return (0);
}

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
** cleans up a mistake we did before
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

int		insert_check_complete(char **row, char **tetra, int x, int y)
{
	ft_putendl("cheking insertion of tetra in row");
	if (insert_checker(row, tetra, x, y))
	{
		ft_putendl("Passed");
		insert_tetra_row(row, tetra, x, y);
	}
	else
		ft_putendl("Not possible");
	return (0);
}



int BFS_big_fucking_solver(char **row, char ***tetra, int b)
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
			if (insert_checker(row,  tetra[b],  i,  j))
			{
				insert_tetra_row(row, tetra[b], i, j);
				print_row(row);
				if (!BFS_big_fucking_solver(row, tetra, ++b))
				{
					return(0);
				}
				clean_tetra_row(row, tetra[--b], i, j);
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

	ft_putendl("START of solve");
	min_size = ft_floor_sqrt(num_tetra(tetra) * 4);
	ft_putnbr(num_tetra(tetra));
	ft_putendl(" = num of blocks");
	ft_putnbr(min_size);
	ft_putendl(" = minimum side size of solution square");
	ft_putendl("Generating solution row of size min_size");
	row = gen_row(min_size, min_size, '.');
	ft_putendl("Printing said row");

	while (BFS_big_fucking_solver(row,tetra,0))
	{
		min_size++;
		row = gen_row(min_size, min_size, '.');
		BFS_big_fucking_solver(row,tetra,0);
		// remember to free row memory when you create a new one
	}
	print_row(row);



	print_row(row);
	return (0);
}
