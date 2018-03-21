//-- Header file for the solver type object

#ifndef SOLVER_H
#define SOLVER_H

#include "puzzle.h"
#include <string>
#include <iostream>

//class declaration
class solver {

//just a collection of functions
public:

	//helper function to determine if the row is within constraints
	bool check_row_constraint(int, int, puzzle&);
	//helper function to determine if the column is within constraints
	bool check_column_constraint(int, int, puzzle&);
	//helper function to check if local 3X3 square is within constraints
	bool check_local_square (int, int, puzzle&);
	//helper function to perform a cumulative check of:
	//check_row_constraint
	//check_column_constraint
	//check_local_square 
	bool check_all_constraints(int, int, int, puzzle&);
	//backtracking algorithm
	bool backtracking_sudoku(int, int, puzzle&);
	//creates a puzzle from a text file
	puzzle make_puzzle_from_file(std::string);
	//function to find the next place to assign a variable
	bool valid_next_placement(int&, int&, puzzle&);
	//helper function to determine what local square we are in inside the puzzle
	int find_section(int,int);


};
#endif