/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:46:36 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/28 19:53:07 by nmanzini         ###   ########.fr       */
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
	int		old_ret;

	counter = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	buf = ft_strnew(21);
	while ((ret = read(fd, buf, 21)))
	{
		if (block_validator(buf) || ret < 20)
			return (0);
		counter++;
		old_ret = ret;
	}
	if (old_ret != 20)
		return (0);
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
** returns an error
*/

char	***return_error(void)
{
	ft_putendl("error");
	return (NULL);
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
	size = input_length(path);
	if (!size)
		return (return_error());
	str = input_strings(path, size);
	if (!str)
		return (return_error());
	matrix = gen_matrices(size, 4, 4, '.');
	if (!matrix)
		return (return_error());
	fill_matrices(matrix, str);
	if (tetro_checker(matrix, 0, 0) == 0)
		return (return_error());
	clean_row_matrices(matrix);
	clean_column_matrices(matrix);
	return (matrix);
}
