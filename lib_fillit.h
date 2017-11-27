/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_fillit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:12:47 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/27 13:15:29 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_FILLIT_H
# define LIB_FILLIT_H

int		block_validator(char *block);
int		input_length(char *path);
char	**input_strings(char *path, int size);
int		print_strings(char **str);
char	***gen_matrices(int size, int m, int n);
int		print_matrices(char ***matrix);
int		fill_matrices(char ***matrix, char **str);
int		analyze_matrix(char **row);
int		clean_row_matrices(char ***matrix);
int		set_up(char *path);
int		main(int argc, char **argv);

#endif