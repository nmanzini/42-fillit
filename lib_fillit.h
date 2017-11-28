/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_fillit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:12:47 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/28 11:30:37 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_FILLIT_H
# define LIB_FILLIT_H

#include "./includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
** main.c
*/
int		main(int argc, char **argv);
/*
** read_input.c
*/
int		block_validator(char *block);
int		input_length(char *path);
char	**input_strings(char *path, int size);
int		print_strings(char **str);
char	***gen_matrices(int size, int m, int n, char c);
int		print_matrices(char ***matrix);
int		fill_matrices(char ***matrix, char **str);
int		analyze_matrix(char **row);
int		clean_row_matrices(char ***matrix);
int		clean_column_matrices(char ***matrix);
char	***set_up(char *path);
/*
** solver.c
*/
int		ft_floor_sqrt(int value);
int		num_tetra(char ***tetra);
char	**gen_grid(int m, int n, char c);
int		print_grid(char **row);
int		insert_tetra_grid(char **row, char **tetra, int x, int y);
int		insert_checker(char **row, char **tetra, int x, int y);
int		insert_check_complete(char **row, char **tetra, int x, int y);
int		solve(char ***matrix);


#endif