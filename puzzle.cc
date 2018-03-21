#include "puzzle.h"
#include <iostream>


//constructor
puzzle::puzzle(){

	for (int i =0; i < 9; i++){
		for (int j=0; j < 9; j++){
			grid[i][j] = 0;
		}
	}
}



//
puzzle & puzzle::operator=(const puzzle & right_operand){

	for(int i = 0; i < 9; i++){
		for(int j=0; j<9; j++){
			this->grid[i][j] = right_operand.grid[i][j];
		}
	}

	return *this;

}


void puzzle::assign_value(int row, int col, int val){

	this->grid[row][col] = val;
}

int puzzle::get_value(int row, int col) const {
	return this->grid[row][col];
}

void puzzle::print_board(){

	std::cout << "--------------------";
	printf("\n");
	for(int i =0; i<9; i++){
		std::cout << std::endl;
		printf("| ");
		for(int j =0; j < 9; j++){
			std::cout << grid[i][j] << " | ";
			
		}
	}
	printf("\n");
	std::cout << "--------------------";

}