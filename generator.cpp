#include <iostream>
#include <fstream>
#include <stdlib.h>    
#include <time.h> 
#include <string>
#include "generatorIdeas.cpp"
#include "node.h"

#define   RAND_MAX   0x7fffu 

// My goal is to consolidate everything we are doing for the generator into one place
// so I am using the generatorIdeas functions to create the grid
// and the nodes class to add nodes to the grid to create something that can be more
// interactive and respond then prompted to

// I am not sure what we want to output, so it is easy to return the grid of strings or nodes 
// It is possible to just 

int main()   
{ 
	int size;
	int pits;

	std::cout << "Enter the size:"; // enter the size of the matrix
	std::cin >> size;
	std::cout << "Enter the number of pits:"; // enter the # of pits
	std::cin >> pits;
	
	std::vector<board> listOfGrids;

	// create 1 board without any stuff in it
	listOfGrids= makeBoards(size, 1, pits);
	board genGrid= listOfGrids[0];

	// use this code if we want to make the grid have nodes in it
	// ignore this code if we want to return a 2D grid of strings instead
	std::vector<std::vector<nodes> > game; // implementation of gameBoard with nodes instead of strings

	// replaces strings with a 2d grid with nodes
	for(int x=0; x< size; x++){
		for(int y=0; y<size; y++){
			game[x][y]= Node node(x, y, genGrid[x][y], size);
		}
	}
	// write the matrix into a visualize txt file
	string visual[size];
	for(int x=0; x< size; x++){
		for(int y=0; y<size; y++){
			visual[x] = game[x][y].get_label();
		}
	}
	ofstream OutFile("generator_visual.txt");
	for(int i = size - 1; i >= 0; i--){
		OutFile << visual[i] << "\n";
	}
	OutFile.close();




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
