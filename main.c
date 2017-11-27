/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 16:35:16 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/27 17:08:10 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_fillit.h"

int		main(int argc, char **argv)
{
	char ***matrices;

	if (argc < 2)
		ft_putendl("usage: fillit source_file");
	else if (argc > 2)
		ft_putendl("to much inputting, SHTAP!");
	else
	{

		matrices = set_up(argv[1]);
		if (!matrices)
			return(1);
		solve(matrices);
		return (0);
	}
	return (1);
}
