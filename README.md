# 42-fillit
 This is the story of a piece of Tetris, one little square and a dev walk into a bar...

## Description

 Fillit is not about recoding Tetris, even if it’s still a variant of this game. This program will take a file as parameter, which contains a list of Tetriminos, and arrange them in order to create the smallest square possible.

### The program
 The executable "fillit" takes only one parameter, a file which contains a list of Tetriminos to assemble. This file has a very specific format (see input sample).

### Input Sample:
 Each tetraminos is represented with 4 lines of 4 characters, each followed by a new line. A Tetrimino is a classic piece of Tetris composed of 4 blocks. Each character must be either a block character(’#’) or an empty character (’.’). Each block of a Tetrimino must touch at least one other block on any of his 4 sides (up, down, left and right).

	...#
	...#
	...#
	...#

	....
	....
	....
	####

	.###
	...#
	....
	....

	....
	..##
	.##.
	....

	....
	.##.
	.##.
	....

	....
	....
	##..
	.##.

	##..
	.#..
	.#..
	....

	....
	###.
	.#..
	....


### Output Sample:
The program displays the smallest assembled square on the standard output. To
identify each Tetrimino in the square solution, a capital letter will be assigned to each
Tetrimino, starting with ’A’ and increasing for each new Tetrimino.

	ABBBB.
	ACCCEE
	AFFCEE
	A.FFGG
	HHHDDG
	.HDD.G

# Solution
The program is divided in two parts:A part that reads, validate, organize the input and a second part that solves the problem using backtracking.
here is how the program works:

### Reading the input and preparing the data

* The program take the path of the input file as argument, returns usage instruction if argument is blank, error if there are more than 1 arguments.
* The function _main()_ calls _setup()_, here the buffer of the file reads 21 bytes while it counts and validate formally the block.
* Kowning how many blocks are in the input file _gen_matrices()_ allocates a list of _size_ matrices (4x4) and then _fill_matrices()_ fills it with the letters representing the different blocks.
* The empty rows and column of the matries representig each block are removed by the functions _clean_row_matrices()_ and _clean_column_matrices()_, (this is probably not the best way to do this).

### Solving the problem

* Takes the list of tetraminos and evaluates how big should be the minimum square that can hold all those pieces.
* Generates a matrix of size _min_size_ with the fucntion _gen_row()_.
* Calls the function _bfs_big_fucking_solver()_ wich taking in the emty solution grid and the list of tetraminos solves the problem wihtout allocating any more memory trough backtracking, insertions and restorations.
* The solution is printed by _print_row(row)_

# Notes
The matrices starts at zero and the standard naming system is used (as shown in the image underneath). Every row is null terminated and the last row is NULL.

![Matrix Notation](https://upload.wikimedia.org/wikipedia/commons/thumb/b/bb/Matrix.svg/247px-Matrix.svg.png)
