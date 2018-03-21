//-- Main program file

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

	//declare a solver object in order to call solver functions
	solver solver;
	//declare "global" row and column ints as they are needed
	//by functions inside solver to advance through the assignments
	//properly
	int row=0;
	int column=0;
	//declare file pointer
	std::ifstream fin;
	//open the input file
	fin.open("sudoku.input");
	//make sure that the file is actually open
	if (! fin.is_open()){
		//tell user there was a problem opening the file
		printf("file was not open \n");
		//exit program
		return 1;
	}
	//declare temp to hold the values coming in from the file
	int temp=0;
	//iterate through the rows, make sure file input is good
	for (int i =0; i < 9 && fin.good(); i++){
		//iterate through columns, make sure file input is good
		for(int j =0; j < 9 && fin.good(); j++){
			//get input from the file into temp
			fin >> temp;
			//assign the value held in temp into the puzzle's grid at position [i][j]
			puzzle.assign_value(i, j, temp);
		}

	}
	//Puzzle is full of values from input now, print the initial configuration
	puzzle.print_board();

	//run backtracking algorithm, see if a solution was found (returns true if yes, false if no)
	if (solver.backtracking_sudoku(row, column, puzzle)){
		//if a solution is found, tell user a solution was found
		printf("Solution found!\n\n");
		//print the solution
		puzzle.print_board();
	}
	//else it was a bad config, and there is no solution
	else {
		//tell the user no solution found
		printf("Solution not found....");
	}
	//close the file pointer
	fin.close();

	//exit program
	return 0;
}