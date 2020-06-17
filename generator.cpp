#include <iostream>
#include <fstream>
#include <stdlib.h>    
#include <time.h> 
#include <string>
#include "generatorIdeas.cpp"
#include "node.h"

#define   RAND_MAX   0x7fffu 
int main()   
{ 
	int size;
	int pits;

	std::cout << "Enter the size:"; // enter the size of the matrix
	std::cin >> size;
	std::cout << "Enter the number of pits:"; // enter the # of pits
	std::cin >> pits;
	
	std::vector<std::vector<std::string> > board;

	


	return  0;
} 


// this code is all for a 1D grid, which we decided we aren't going to use
	// //initialize matrix with empty unit
	// for(int i = 0; i < size_square; i++)
	// {
	// 	coordinate[i] = "e";
	// }

	//coordinate[0] = 's'; // the left bottom is marked as start

	// generate the position of gold
	// coordinate[rand()%size_square] = "g";

	// // generate the position of wumpus
	// while(true)
	// {
	// 	int random;
	// 	random = rand()%size_square;
	// 	if(coordinate[random] == "e")
	// 	{
	// 		coordinate[random] = "w";
	// 		break;
	// 	}
	// }

	// // generate the position of pits
	// for(int i = 0; i < pits; i++){
	// 	while(true)
	// 	{
	// 		int random;
	// 		random = rand()%size_square;
	// 		if(coordinate[random] == "e")
	// 		{
	// 			coordinate[random] = "p";
	// 			break;
	// 		}
	// 	}
	// }

	// // write the matrix into a txt file
	// // the format of matrix will be: row, column, element
	// ofstream OutFile("generator.txt");
	// for(int i = 0; i < size_square; i++)
	// {
	// 	string temp;
	// 	int row = i / size;
	// 	int column = i % size;
	// 	temp = to_string(row)+" "+to_string(column)+" "+ coordinate[i];
	// 	OutFile << temp << "\n";
	// }
	// OutFile.close();