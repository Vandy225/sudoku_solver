//--Implementation file for solver objects

#include "solver.h"
#include "puzzle.h"


//---------------------------------------------------------------------------------------------------------------------
//--Function to check if a value is already in a row, leading to a constraint violation on assignment
//
//--Arguments:
//
//				int row --> the index of the row we are checking
//
//				int value --> the value that we are checking to see if it has been repeated
//
//				puzzle& puzzle --> the puzzle object we are checking
//
//--Return Type:
//
//				bool, indicating if the row constraint has been violated
//
//---------------------------------------------------------------------------------------------------------------------
bool solver::check_row_constraint(int row, int value, puzzle& puzzle){
//loop through all rows
for (int i =0; i < 9; i++){
	//the row is not valid as the value is duplicated
	if (puzzle.get_value(row,i) == value){
		//return false due to constraint violation
		return false;
	}
}
//if the value was not found in the row, return true
return true;
}


//---------------------------------------------------------------------------------------------------------------------
//--Function to check if a particular value is already in a column of the puzzle, leading to constraint violation on
//	assignment
//
//--Arguments:
//
//				int col --> the index of the column we are checking
//
//				int value --> the value we are checking to see if it is in a column
//
//				puzzle& puzzle --> reference to puzzle object we are checking
//
//--Return Type:
//
//				bool, indicating if the column constraint has been violated
//
//---------------------------------------------------------------------------------------------------------------------
bool solver::check_column_constraint(int col, int value, puzzle& puzzle){
	//loop through the columns
	for(int i=0; i < 9; i++){
		//value was duplicated, not a valid row
		if(puzzle.get_value(i, col) == value ){
			//return false to indicate constraint violation
			return false;
		}
	}
	//value was not found in column, the column constraint has not been violated
	return true;
}
//---------------------------------------------------------------------------------------------------------------------
//--Function to check the local 3X3 square that we are assigning a value to in order to determine local square
//	constraint violation
//
//--Arguments:
//
//				int secttion --> indicates what particular local square we are trying to assign a value to (numbered 0-8).
//								 The sections start in the top left and end in the bottom right.
//
//				int value --> the value we are checking to see if it is already in the local square
//
//				puzzle& puzzle --> reference the the puzzle object we are checking
//
//--Return Type:
//
//				bool, indicating if the local square constraint has been violated
//
//---------------------------------------------------------------------------------------------------------------------
bool solver::check_local_square (int section, int value, puzzle& puzzle){
	//defining initial min and max bounds for each of the sections
	int row_min = 0;
	int row_max = 0;
	int col_min = 0;
	int col_max = 0;

	//the sections are defined as follows:

	//-------
	//|0|1|2|
	//|3|4|5|
	//|6|7|8|
	//-------

	//switch statement to handle all of the possible sections. Assign the row and col min/max indices as appropriate
	switch(section){
		//we are in section 0
		case 0:
		row_min = 0;
		row_max = 2;
		col_min = 0;
		col_max = 2;
		break;
		//we are in section 1
		case 1:
		row_min = 0;
		row_max = 2;
		col_min = 3;
		col_max = 5;
		break;
		//we are in section 2
		case 2: 
		row_min = 0;
		row_max = 2;
		col_min = 6;
		col_max = 8;
		break;
		//section 3
		case 3:
		row_min = 3;
		row_max = 5;
		col_min = 0;
		col_max = 2;
		break;
		//section 4
		case 4:
		row_min = 3;
		row_max = 5;
		col_min = 3;
		col_max = 5;
		break;
		//section 5
		case 5:
		row_min = 3;
		row_max = 5;
		col_min = 6;
		col_max = 8;
		break;
		//section 6
		case 6:
		row_min = 6;
		row_max = 8;
		col_min = 0;
		col_max = 2;
		break;
		//section 7
		case 7:
		row_min = 6;
		row_max = 8;
		col_min = 3;
		col_max = 5;
		break;
		//section 8
		case 8:
		row_min = 6;
		row_max = 8;
		col_min = 6;
		col_max = 8;
		break;

	}
	//now that we have our bounds for the local square, check to see if the value has been
	//duplicated in the local 3X3 square

	//for the values in row_min to row_max (section dependent)
	for ( int i = row_min; i <= row_max; i++){
		//for the values in col_min to col_max (section dependent)
		for(int j=col_min; j <= col_max; j++){
			//if the value at any of these squares equals our value argument, the constraing has been violated
			if(puzzle.get_value(i,j) == value){
				//value has been duplicated in local square, not within constraints
				return false;
			}
		}
	}
	//return true indicating that the constraint has not been violated
	return true;
}


//---------------------------------------------------------------------------------------------------------------------
//--Function to find out what section of the board we are looking in depending on the row and column indices of an access
//
//--Arguments:
//
//				int row --> row index within the grid
//
//				int col --> column index within the grid
//
//--Return Type:
//
//				int, which represents which section of the board our assignment/access is hitting
//
//---------------------------------------------------------------------------------------------------------------------
int solver::find_section(int row, int col){
	//
	//we are in the first row
	if (row < 3){
		if (col < 3){
			//we are in section 0
			return 0;
		}
		else if(col < 6 && col > 2){
			//we are in section 1
			return 1;

		}
		else if(col < 9 && col > 5){
			//we are in section 2
			return 2;
		}
	}
	//we are in the second row
	else if (row < 6 && row > 2){
		if (col < 3){
			//we are in section 3
			return 3;
		}
		else if(col < 6 && col > 2){
			//we are in section 4
			return 4;

		}
		else if(col < 9 && col > 5){
			//we are in section 5
			return 5;
		}

	}
	//we are in the third row
	else if(row < 9 && row > 5){
		if (col < 3){
			//we are in section 6
			return 6;
		}
		else if(col < 6 && col > 2){
			//we are in section 7
			return 7;

		}
		else if(col < 9 && col > 5){
			//we are in section 8
			return 8;
		}
	}
	//debugging message if this fails
	printf("Couldn't find section");
	//exit the program with code 1
	exit(1);
	
}

//---------------------------------------------------------------------------------------------------------------------
//--Function to check if an assignment of a value in a position within the grid violates any of the constraints
//
//--Arguments:
//
//				int row --> the row index of intended element placement
//
//				int col --> the column index of intended element placement
//
//				int value --> the value we are trying to assign
//
//				puzzle& puzzle --> reference to puzzle object 
//
//--Return Type:
//
//				bool, indicating if constraints have been violated or not
//
//---------------------------------------------------------------------------------------------------------------------
bool solver::check_all_constraints(int row, int col, int value, puzzle & puzzle){
	//use the find_section function to determine which section we are trying to place a value in
	int section = find_section(row, col);
	//as long as all constraints are satisfied, we return true
	//else the return statement returns false, indicating a constraint violation
	return (check_local_square(section, value,puzzle) && check_column_constraint(col, value, puzzle) && check_row_constraint(row, value, puzzle));
}


//---------------------------------------------------------------------------------------------------------------------
//--This function tries to go through and find a placement for a value in the puzzle (i.e. find an empty square)
//
//--Arguments:
//
//				int& row --> reference to global row index used for iterating through the puzzle through recursions
//
//				int& col --> reference to global column index used for iterating through puzzle through recursions
//
//				puzzle& puzzle --> reference to puzzle object that we are operating in
//
//--Return Type:
//
//				bool
//				
//				False indicates that there was a place to put the value (i.e. the board is NOT full). 
//				True indicates that there are no open spots and the board is now full
//				
//
//---------------------------------------------------------------------------------------------------------------------
bool solver::valid_next_placement(int& row, int& column, puzzle& puzzle){
	//iterate through rows
	for(int i =0; i < 9; i++){
		//iterate through columnd
		for(int j =0; j < 9; j++){
			//assign the row/column values (by reference to communicate this to main) to the current search's values
			row=i;
			column=j;
			//if the value of the square at [i][j]==0, then there is an open spot
			if(puzzle.get_value(i,j) == 0){
				//there was a valid position (i.e. the board is not full) to put the value (i.e. row=i, column=j), which will be communicated
				//back to backtracking algorithm by reference
				return false;
			}
		}
	}
	//there was no place to put a value, the puzzle is full
	return true;

}
//---------------------------------------------------------------------------------------------------------------------
//--Main backtracking algorithm that is recursively called. Returns true if the solution is found or if the board is full,
//  returns false indicating a failure of the algoritm to meet constraints and find a solution (i.e. no solution available)
//
//--Arguments:
//
//			int row --> row index of an element that we will use to try and assign a value
//
//			int col --> column index of an element that we will use to try and assign a value
//
//			puzzle& puzzle --> reference to puzzle object we are working on	
//
//--Return Type:
//
//				bool
//
//				True indicates that the board is full (i.e. all placements made) which means a solution was found
//
//				False indicates that the algorithm failed and that there is no available solution
//
//---------------------------------------------------------------------------------------------------------------------
bool solver::backtracking_sudoku(int row, int col, puzzle& puzzle){

	//first check to see if the whole sudoku puzzle is full of values
	if(valid_next_placement(row, col, puzzle)){
		//puzzle is full, stop
		return true;
	}

	//now we want to try and assign a value in the puzzle. We know that the values will vary between
	//1 and 9, and so we can check each value in the provided row/column position and check to see
	//if the placement stays within constraints

	

	else{
		//loop through all values of the variable
		for (int i =1; i <= 9; i++){
			//check to see that the value's placement at row/column matches constraints
			if(solver::check_all_constraints(row, col, i, puzzle)){
				//assign the value of the variable to the position row/col
				puzzle.assign_value(row, col, i);
				//now we recurse and call back_tracking again
				//assuming that the placement was good, call backtracking_sudoku again
				if(backtracking_sudoku(row, col, puzzle)){
					//searching is done, solution has been found, return true
					return true;
				}
				//otherwise, reset the value in the position that we tried to 0 so
				//that another iteration can try and set the value to something that works
				puzzle.assign_value(row, col, 0);
			}
		}
		//return failure, this was not a valid solution as it failed on constraints
		return false;	
}
	


	

}

