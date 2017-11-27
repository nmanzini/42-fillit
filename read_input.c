/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:46:36 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/27 13:10:36 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** gcc read_input.c libft.a -o fillit  && ./fillit  "sample.fillit"
*/

#include "./includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

char	***gen_matrices(int size, int m, int n)
{
	char	***matrix;
	int		b;
	int		i;

	b = 0;
	i = 0;
	matrix = (char***)malloc(sizeof(char**) * (size + 1));
	while (b < size)
	{
		matrix[b] = (char**)malloc(sizeof(char*) * (m + 1));
		while (i < 4)
			matrix[b][i++] = ft_strdup("....");
		b++;
		i = 0;
	}
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
** take a lsit of matrices and a list of strings
*/

int		analyze_matrix(char **row)
{
	int i;

	i = 0;
	while (row[i] != 0)
	{
		if (!strcmp(row[i], "...."))
		{
			ft_putnbr(i);
			ft_putendl("row to cancel");
		}
		i++;
	}
	return (0);
}

/*
** take a lsit of matrices and a list of strings
*/

int		clean_row_matrices(char ***matrix)
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
			if (!strcmp(matrix[b][i], "...."))
			{
				while (matrix[b][i][j] != 0)
				{
					matrix[b][i][j] = matrix[b][i + 1][j];
					j++;
				}
				ft_putnbr(b);
				ft_putnbr(i);
				ft_putendl(" row to cancel");
			}
			else
				while (matrix[b][i][j] != 0)
				{
					matrix[b][i][j] = matrix[b][i][j];
					j++;
				}
			i++;
			j = 0;
		}
		b++;
		i = 0;
	}
	return (0);
}

/*
** initialization of everything
*/

int		set_up(char *path)
{
	int		size;
	char	***matrix;
	char	**str;

	size = 0;
	ft_putendl("reading, calculating length and validating");
	size = input_length(path);
	if (!size)
		ft_putendl("ERROR in reading or validating");
	ft_putstr("number of blocks = ");
	ft_putnbr(size);
	ft_putchar('\n');
	ft_putendl("printing string");
	str = input_strings(path, size);
	if (!str)
		ft_putendl("ERROR in moving to string input");
	print_strings(str);
	ft_putendl("generating matrices");
	matrix = gen_matrices(size, 4, 4);
	ft_putendl("filling matrices");
	fill_matrices(matrix, str);
	ft_putendl("printing matrices");
	print_matrices(matrix);
	// ft_putendl("cleaning matrices");
	// clean_row_matrices(matrix);
	// print_matrices(matrix);
	return (0);
}

/*
** main file that take a path as only arguments or return error.
*/

int		main(int argc, char **argv)
{
	if (argc < 2)
		ft_putendl("usage: fillit source_file");
	else if (argc > 2)
		ft_putendl("to much inputting, SHTAP!");
	else
	{
		set_up(argv[1]);
		return (0);
	}
	return (1);
}
