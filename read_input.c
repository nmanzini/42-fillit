/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:46:36 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/24 19:14:41 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	block_validator(char *block)
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

char	**open_file(char *path)
{
	int		ptr;
	int		ret;
	char	*buf;
	int		counter;
	char	**list;

	list = (char**)malloc(sizeof(char*) * 27);
	list[27] = NULL;
	counter = 0;
	ptr = open(path, O_RDONLY);
	if (ptr == -1)
	{
		ft_putendl("open() FAILED");
		return (NULL);
	}
	buf = ft_strnew(21);
	while ((ret = read(ptr, buf, 21)))
	{
		list[counter] = buf;
		counter++;
		buf = ft_strnew(21);
	}
	list[++counter] = NULL;
	if (close(ptr) == -1)
	{
		ft_putendl("Close() FAILED");
		return (NULL);
	}
	return (list);
}

/*
** take a list and prints the input
*/

int print_input(char **list)
{
	int i;

	i = 0;
	while (list[i] != NULL)
	{
		ft_putstr("block #");
		ft_putnbr(i);
		ft_putchar('\n');
		ft_putstr(list[i]);
		i++;
		(*list)++;
	}
	return (0);
}

char ***lst_to_lstmatrix(char**str_list)
{
	char ***list;
	char **matrix;
	char *row;
}

/*
** take a path as inputs and opens it
*/

int	reader(char *path)
{
	char **list;
	list = open_file(path);
	print_input(list);
	return (0);
}

int	main(int argc, char **argv)
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
