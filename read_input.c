/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:46:36 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/24 17:50:06 by nmanzini         ###   ########.fr       */
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
** inputs the file path of the source and the verbose option
** opens it
** loops trough every 21 char
**		vaidate them
** closes it
*/

int	open_file(char *path, int verbose)
{
	int		ptr;
	int		ret;
	char	*buf;
	int		counter;
	int		sum;

	counter = 0;
	ptr = open(path, O_RDONLY);
	if (ptr == -1)
	{
		ft_putendl("open() FAILED");
		return (1);
	}
	buf = ft_strnew(21);
	while ((ret = read(ptr, buf, 21)))
	{
		buf[ret] = 0;
		counter++;
		sum = block_validator(buf);
		if (sum)
			ft_putendl("UNVALID CHAR");
		if (verbose)
		{
			ft_putstr("\nblock # = ");
			ft_putnbr(counter);
			ft_putchar('\n');
			ft_putstr("wrong = ");
			ft_putnbr(sum);
			ft_putchar('\n');
			ft_putstr(buf);
		}
	}
	if (close(ptr) == -1)
	{
		ft_putendl("Close() FAILED");
		return (1);
	}
	return (counter);
}

int	reader(char *path)
{
	int pieces;

	pieces = open_file(path, 1);
	ft_putstr("Found ");
	ft_putnbr(pieces);
	ft_putendl(" Pieces");
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
