/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:46:36 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/24 21:34:53 by nmanzini         ###   ########.fr       */
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
** saves each buffer in its own string
** closes it
*/

int		input_length(char *path)
{
	int		ptr;
	int		ret;
	char	*buf;
	int		counter;

	counter = 0;
	ptr = open(path, O_RDONLY);
	if (ptr == -1)
		return (0);
	buf = ft_strnew(21);
	while ((ret = read(ptr, buf, 21)))
	{
		if (block_validator(buf))
			return (0);
		counter++;
	}
	free(buf);
	if (close(ptr) == -1)
		return (0);
	return (counter);
}

/*
** allocate space for all the matrices and initialize them with dots.
*/

char	***gen_matrices(int block_num, int m, int n)
{
	char ***matrix;
	int b;
	int i;

	b = 0;
	i = 0;
	matrix = (char***)malloc(sizeof(char**) * (block_num + 1));
	while (b < block_num)
	{
		matrix[b] = (char**)malloc(sizeof(char*) * (m + 1));
		while (i < 4)
		{
			matrix[b][i] = ft_strnew(n);
			matrix[b][i] = "....";
			i++;
		}
		b++;
		i = 0;
	}
	return (matrix);
}

/*
** take a path as inputs, check his length and formal validity
*/

int		get_matrix(char ***matrix)
{
	int b;
	int i;

	b = 0;
	i = 0;
	while (matrix[b] != 0)
	{
		ft_putendl("----");
		while (matrix[b][i] !=0)
			ft_putendl(matrix[b][i++]);
		b++;
		i = 0;
	}
	ft_putendl("----");
	ft_putendl("DONE");
	return (0);
}

/*
** take a path as inputs, check his length and formal validity
*/

int fill_matrix(char ***matrix)
{

}

int		reader(char *path)
{
	int block_num;
	char ***matrix;

	block_num = 0;
	block_num = input_length(path);
	if (!block_num)
		ft_putendl("ERROR in validation or reading");
	ft_putendl("number of blocks:");
	ft_putnbr(block_num);
	ft_putchar('\n');

	ft_putendl("generating matrices");
	matrix = gen_matrices(block_num,4,4);
	ft_putendl("getting matrices");
	get_matrix(matrix);

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
		reader(argv[1]);
		return (0);
	}
	return (1);
}
