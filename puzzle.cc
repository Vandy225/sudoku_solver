//-- Implementation file for puzzle objects
#include "puzzle.h"
#include <iostream>


//---------------------------------------------------------------------------------------------------------------------
//--Constructor for the puzzle object. Initializes the grid to be full of 0's initially.
//
//--Arguments:
//
//				None
//
//--Return type:
//
//				None, returns puzzle object
//
//---------------------------------------------------------------------------------------------------------------------

puzzle::puzzle(){
	//iterate through rows
	for (int i =0; i < 9; i++){
		//iterate through columns
		for (int j=0; j < 9; j++){
			//set value at that square to be 0
			grid[i][j] = 0;
		}
	}
}



//---------------------------------------------------------------------------------------------------------------------
//--Overloaded = operator for setting two puzzles equal to each other
//
//--Arguments:
//
//				const puzzle& right_operand --> reference to puzzle to be copied
//		
//--Return Type:
//
//				puzzle reference
//
//---------------------------------------------------------------------------------------------------------------------
puzzle & puzzle::operator=(const puzzle & right_operand){

	//go through rows of destination object
	for(int i = 0; i < 9; i++){
		//go through columns of destination object
		for(int j=0; j<9; j++){
			//set the value for each square in the destination object to be that of the 
			//value of the right_operand's square
			this->grid[i][j] = right_operand.grid[i][j];
		}
	}
	//return the destination object
	return *this;

}

//---------------------------------------------------------------------------------------------------------------------
//--Function to assign a value to a square within the puzzle
//
//--Arguments:
//
//				int row--> the row where the value will be placed
//
//				int col--> the column where the value will be placed
//
//				int val--> the value that will be held at grid[row][col]
//
//--Return Type:
//
//				void
//
//---------------------------------------------------------------------------------------------------------------------
void puzzle::assign_value(int row, int col, int val){
	//set the value in the calling object's grid at grid[row][col] = val
	this->grid[row][col] = val;
}


//---------------------------------------------------------------------------------------------------------------------
//--Getter function to get the value held at grid[row][col]
//
//--Arguments:
//
//				int row--> specifies the row index
//
//				int col--> specifies the col index
//
//--Return Type:
//
//				int, which is the value held at grid[row][col]
//
//---------------------------------------------------------------------------------------------------------------------
int puzzle::get_value(int row, int col) const {
	//return the value held at grid[row][col] in the calling object
	return this->grid[row][col];
}

//---------------------------------------------------------------------------------------------------------------------
//--Function to print the board configuration to the screen
//
//--Arguments:
//
//				none, function is called on object
//
//--Return Type:
//
//				void, just prints to screen
//
//---------------------------------------------------------------------------------------------------------------------
void puzzle::print_board(){
	//print formatting string
	std::cout << "--------------------";
	//print separating newline
	printf("\n");
	//for all of the rows
	for(int i =0; i<9; i++){
		//print an endl to separate the rows
		std::cout << std::endl;
		//print separator for values in squares
		printf("| ");
		//go through columns
		for(int j =0; j < 9; j++){
			//output the value at grid[i][j] followed by separator
			std::cout << grid[i][j] << " | ";
			
		}
	}
	//print final endline
	printf("\n");
	//print bottom of the board
	std::cout << "--------------------";

}