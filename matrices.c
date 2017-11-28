/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:26:42 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/28 18:31:58 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_fillit.h"

/*
** allocate space for all the matrices and initialize them with dots.
*/

char	***gen_matrices(int size, int m, int n, char c)
{
	char	***matrix;
	int		b;
	int		i;
	int		j;

	b = 0;
	i = 0;
	matrix = (char***)malloc(sizeof(char**) * (size + 1));
	while (b < size)
	{
		matrix[b] = (char**)malloc(sizeof(char*) * (m + 1));
		while (i < m)
		{
			j = 0;
			matrix[b][i] = ft_strnew(n);
			while (j < n)
				matrix[b][i][j++] = c;
			i++;
		}
		matrix[b][i] = NULL;
		b++;
		i = 0;
	}
	matrix[b] = NULL;
	return (matrix);
}

/*
** take a list of matrices as input and prints them
*/

/*
**int		print_matrices(char ***matrix)
**{
**	int b;
**	int i;
**
**	b = 0;
**	i = 0;
**	ft_putchar('\n');
**	while (matrix[b] != 0)
**	{
**		while (matrix[b][i] != 0)
**		{
**			ft_putendl(matrix[b][i]);
**			i++;
**		}
**		b++;
**		i = 0;
**		ft_putchar('\n');
**	}
**	ft_putendl("+----+");
**	ft_putendl("|DONE|");
**	ft_putendl("+----+");
**	return (0);
**}
*/

/*
** take a lsit of matrices and a list of strings
*/

int		fill_matrices(char ***matrix, char **str)
{
	int b;
	int i;
	int j;

	b = 0;
	i = 0;
	j = 0;
	while (matrix[b] != 0)
	{
		while (matrix[b][i] != 0)
		{
			while (matrix[b][i][j] != 0)
			{
				if (str[b][i * 5 + j++] == '#')
					matrix[b][i][j - 1] = str[b][i * 5 + j - 1] + 30 + b;
			}
			i++;
			j = 0;
		}
		b++;
		i = 0;
	}
	//free_row(str);
	return (0);
}

/*
** take a lsit of matrices and removes the dotted rows
*/

int		clean_row_matrices(char ***matrix)
{
	int b;
	int i;
	int i2;

	b = 0;
	i = 0;
	while (matrix[b] != 0)
	{
		while (matrix[b][i] != 0)
		{
			if (!strcmp(matrix[b][i], "...."))
			{
				i2 = i--;
				while (matrix[b][i2] != 0)
				{
					matrix[b][i2] = matrix[b][i2 + 1];
					i2++;
				}
			}
			i++;
		}
		b++;
		i = 0;
	}
	return (0);
}

/*
** take a matrix and a column and cleans it
*/

int		clean_single_column(char ***matrix, int b, int i, int j)
{
	int j2;

	j2 = 0;
	while (matrix[b][i] != 0)
	{
		if (matrix[b][i][j] == '.')
			j2++;
		i++;
	}
	if (j2 == i)
	{
		i = 0;
		while (matrix[b][i] != 0)
		{
			j2 = j;
			while (matrix[b][i][j2] != 0)
			{
				matrix[b][i][j2] = matrix[b][i][j2 + 1];
				j2++;
			}
			i++;
		}
		j--;
	}
	return (j);
}

/*
** take a lsit of matrices and removes the dotted columns
*/

int		clean_column_matrices(char ***matrix)
{
	int b;
	int i;
	int j;

	b = 0;
	i = 0;
	j = 0;
	while (matrix[b] != 0)
	{
		while (matrix[b][i][j] != 0)
		{
			j = clean_single_column(matrix, b, i, j);
			j++;
		}
		b++;
		j = 0;
	}
	return (0);
}
