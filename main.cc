#include "puzzle.h"
#include <iostream>
#include "solver.h"
#include "stdio.h"
#include "getopt.h"
#include <string>
#include <fstream>


int main() {

	//declare the puzzle object
	puzzle puzzle;

	//declare a solver object
	solver solver;
	//declare "global" row and column ints as they are needed
	//by functions inside solver to advance through the assignments
	//properly

	int row=0;
	int column=0;

	std::ifstream fin;
	fin.open("sudoku.input");

	if (! fin.is_open()){
		printf("file was not open \n");
		return 1;
	}
	
	int temp=0;
	for (int i =0; i < 9 && fin.good(); i++){
		for(int j =0; j < 9 && fin.good(); j++){
			
			fin >> temp;
			puzzle.assign_value(i, j, temp);
		}

	}


	puzzle.print_board();

	//run backtracking algorithm, see if a solution was found (returns true if yes, false if no)
	if (solver.backtracking_sudoku(row, column, puzzle)){

		printf("Solution found!\n\n");
		puzzle.print_board();
	}
	else {
		printf("Solution not found....");
	}

	fin.close();


	return 0;
}