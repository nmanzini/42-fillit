/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:46:36 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/28 11:10:31 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_fillit.h"

/*
** inputs a string of 21 chars and returns 0 if is a valid representation of a
** tetraminos
** -----------------------------------------------------------------------------
** - while
** iterate till the 19th slot to sum everything
** - while - if
** check that every fifth element is a new line
** 		returns (1) if not
** - if
** check that i = 20 is either a end or a new line
**		returns (2) if not
** - if
** check that sum == 732, the sum of 4 hash  12 dots and 4 \n
** 4 * 35 (#) + 12 * 46 (.) + 4 * 10 (\n)= 732
** 140        + 552         + 40         = 732
**		returns (3) if not
*/

int		block_validator(char *block)
{
	int i;
	int sum;

	i = 0;
	sum = 0;
	while (i < 20)
	{
		sum += block[i];
		i++;
		if (i % 5 == 0 && block[i - 1] != '\n')
			return (1);
	}
	if (!(block[i] == 0 || block[i] == '\n'))
	{
		return (2);
	}
	if (sum != 732)
		return (3);
	return (0);
}

/*
** inputs the file path of the source
** opens it
** loops trough every 21 char
** closes it
*/

int		input_length(char *path)
{
	int		fd;
	int		ret;
	char	*buf;
	int		counter;

	counter = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	buf = ft_strnew(21);
	while ((ret = read(fd, buf, 21)))
	{
		if (block_validator(buf))
			return (0);
		counter++;
	}
	free(buf);
	if (close(fd) == -1)
		return (0);
	return (counter);
}

/*
** takes as inputs the file path of the source and the number of blocks
** malloc a list[size];
** opens the source
** loops trough every 21 char
** saves a string in every slot of the list
** frees the buffer
*/

char	**input_strings(char *path, int size)
{
	int		fd;
	int		ret;
	int		b;
	char	*buf;
	char	**output;

	b = 0;
	buf = ft_strnew(21);
	output = (char**)malloc(sizeof(char*) * (size + 1));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while ((ret = read(fd, buf, 21)))
	{
		output[b] = ft_strdup(buf);
		b++;
	}
	free(buf);
	if (close(fd) == -1)
		return (NULL);
	return (output);
}

/*
** takes a list of strings as input
** prints every string till the 0 memeber in the list;
*/

int		print_strings(char **str)
{
	ft_putchar('\n');
	while (*str != 0)
	{
		ft_putstr(*str);
		str++;
	}
	return (0);
}

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

int		print_matrices(char ***matrix)
{
	int b;
	int i;

	b = 0;
	i = 0;
	ft_putchar('\n');
	while (matrix[b] != 0)
	{
		while (matrix[b][i] != 0)
		{
			ft_putendl(matrix[b][i]);
			i++;
		}
		b++;
		i = 0;
		ft_putchar('\n');
	}
	ft_putendl("+----+");
	ft_putendl("|DONE|");
	ft_putendl("+----+");
	return (0);
}

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
		free(str[b]);
		b++;
		i = 0;
	}
	free(str[b]);
	free(str);
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
** take a lsit of matrices and removes the dotted columns
*/

int		clean_column_matrices(char ***matrix)
{
	int b;
	int i;
	int j;
	int counter;
	int j2;

	b = 0;
	i = 0;
	j = 0;
	while (matrix[b] != 0)
	{
		while (matrix[b][i][j] != 0)
		{
			counter = 0;
			while (matrix[b][i] != 0)
			{
				if (matrix[b][i][j] == '.')
					counter++;
				i++;
			}
			if (counter == i)
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
			i = 0;
			j++;
		}
		b++;
		j = 0;
	}
	return (0);
}

/*
** initialization of everything
*/

char	***set_up(char *path)
{
	int		size;
	char	***matrix;
	char	**str;

	size = 0;
	ft_putendl("reading, calculating length and validating");
	size = input_length(path);
	if (!size)
	{
		ft_putendl("ERROR in reading or validating");
		return (NULL);
	}
	ft_putstr("number of blocks = ");
	ft_putnbr(size);
	ft_putchar('\n');
	str = input_strings(path, size);
	if (!str)
	{
		ft_putendl("ERROR in moving to string input");
		return (NULL);
	}
	ft_putendl("generating matrices");
	matrix = gen_matrices(size, 4, 4, '.');
	if (!matrix)
	{
		ft_putendl("ERROR can't make the matrix");
		return (NULL);
	}
	ft_putendl("filling matrices");
	fill_matrices(matrix, str);
	ft_putendl("cleaning rows matrices");
	clean_row_matrices(matrix);
	ft_putendl("cleaning columns matrices");
	clean_column_matrices(matrix);
	ft_putendl("printing cleaned matrices");
	print_matrices(matrix);
	ft_putendl("END OF SETUP");
	return (matrix);
}
