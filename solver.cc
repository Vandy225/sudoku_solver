#include "solver.h"
#include "puzzle.h"



bool solver::check_row_constraint(int row, int value, puzzle& puzzle){

//loop through all rows
for (int i =0; i < 9; i++){
	//the row is not valid as the value is duplicated
	if (puzzle.get_value(row,i) == value){
		return false;
	}

}
//if it was not found, return true
return true;

}

bool solver::check_column_constraint(int col, int value, puzzle& puzzle){

	//loop through the columns
	for(int i=0; i < 9; i++){
		//value was duplicated, not a valid row
		if(puzzle.get_value(i, col) == value ){
			return false;
		}
	}
	//value was not found in column, the column is valid
	return true;
}

bool solver::check_local_square (int section, int value, puzzle& puzzle){
	//MAKE SURE TO GO EQUAL TO THESE BOUNDS, NOT < IN THE FOR LOOP

	int row_min = 0;
	int row_max = 0;
	int col_min = 0;
	int col_max = 0;

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
	for ( int i = row_min; i <= row_max; i++){
		for(int j=col_min; j <= col_max; j++){
			if(puzzle.get_value(i,j) == value){
				//value has been duplicated in local square, not within constraints
				return false;
			}
		}
	}
	return true;

}


//|0|1|2|
//|3|4|5|
//|6|7|8|

int solver::find_section(int row, int col){
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

	printf("Couldn't find section");
	exit(1);
	
}

bool solver::check_all_constraints(int row, int col, int value, puzzle & puzzle){
	int section = find_section(row, col);
	return (check_local_square(section, value,puzzle) && check_column_constraint(col, value, puzzle) && check_row_constraint(row, value, puzzle));
}

//this function tries to go through and find a placement for a value in the puzzle
bool solver::valid_next_placement(int& row, int& column, puzzle& puzzle){

	for(int i =0; i < 9; i++){
		for(int j =0; j < 9; j++){
			//assign the row/column values (by reference to communicate this to main) to the current search's values
			row=i;
			column=j;
			//TO DO: this has been altered from what was true to false, keep this in mind for the backtracking
			if(puzzle.get_value(i,j) == 0){
				//there was a valid position to put the value (i.e. row=i, column=j), which will be communicated
				//back to backtracking algorithm by reference
				return false;
			}
		}
	}
	//there was no place to put a value, the puzzle is full
	return true;

}

bool solver::backtracking_sudoku(int row, int col, puzzle& puzzle){

	//first check to see if the whole sudoku puzzle is full of values
	if(valid_next_placement(row, col, puzzle)){
		//puzzle is full, stop
		return true;
	}

	//now we want to try and assign a value in the puzzle. We know that the values will vary between
	//1 and 9, and so we can check each value in the provided row/column position and check to see
	//if the placement stays within constraints

	//loop through all values of the variable
	

	else{
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

