/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:46:36 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/24 14:35:49 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open_file(char *path, int verbose)
{
	int		ptr;
	int		ret;
	char	*buf;
	int		counter = 0;

	ptr = open(path,O_RDONLY);
	if (ptr == -1)
	{
		ft_putendl_fd("open() FAILED",2);
		return (1);
	}
	buf = ft_strnew(21);
	while ((ret = read(ptr, buf, 21)))
	{
		buf[ret] = 0;
		counter++;
		if (verbose)
		{
			ft_putstr("block number ");
			ft_putnbr(counter);
			ft_putchar('\n');
			ft_putstr(buf);
		}
	}
	if (close(ptr) == -1)
	{
		ft_putendl_fd("Close() FAILED",2);
		return (1);
	}
	return (counter);
}

int reader(char *path)
{
	int pieces;

	pieces = open_file(path,1);
	ft_putstr ("Found ");
	ft_putnbr (pieces);
	ft_putendl(" Pieces");
	return (0);
}


int main (int argc, char **argv)
{
	if (argc < 2)
		ft_putendl_fd("usage: fillit source_file",2);
	else if (argc > 2)
		ft_putendl_fd("to much inputting, SHTAP!",2);
	else
	{
		reader(argv[1]);
		return (0);
	}
	return (1);
}
