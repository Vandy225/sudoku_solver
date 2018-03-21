#ifndef PUZZLE_H
#define PUZZLE_H

class puzzle {

public:

	//puzzle constructor
	puzzle();

	//overloaded =operator
	puzzle & operator=(const puzzle &);

	//getter function to find out what is in a square
	int get_value(int,int) const;

	//function to assign a value to a position within the grid
	void assign_value(int,int,int); 

	void print_board();






private: 
	//double pointer for 2D array, fixed at 9X9
	int grid[9][9];



};
#endif