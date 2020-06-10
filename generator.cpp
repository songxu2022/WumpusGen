#include <iostream>
#include <fstream>
#include <stdlib.h>    
#include <time.h> 
#include <string>
#define   RAND_MAX   0x7fffu 
using namespace std;
int main()   
{ 
	int size;
	cout << "Enter the size:"; // enter the size of the matrix
	cin >> size;
	int pits;
	cout << "Enter the number of pits:"; // enter the # of pits
	cin >> pits;
	int size_square;
	size_square = size * size;
	string coordinate[size_square];

	//initialize matrix with empty unit
	for(int i = 0; i < size_square; i++)
	{
		coordinate[i] = "e";
	}

	coordinate[0] = 's'; // the left bottom is marked as start

	// generate the position of gold
	coordinate[rand()%size_square] = "g";

	// generate the position of wumpus
	while(true)
	{
		int random;
		random = rand()%size_square;
		if(coordinate[random] == "e")
		{
			coordinate[random] = "w";
			break;
		}
	}

	// generate the position of pits
	for(int i = 0; i < pits; i++){
		while(true)
		{
			int random;
			random = rand()%size_square;
			if(coordinate[random] == "e")
			{
				coordinate[random] = "p";
				break;
			}
		}
	}

	// write the matrix into a txt file
	// the format of matrix will be: row, column, element
	ofstream OutFile("generator.txt");
	for(int i = 0; i < size_square; i++)
	{
		string temp;
		int row = i / size;
		int column = i % size;
		temp = to_string(row)+" "+to_string(column)+" "+ coordinate[i];
		OutFile << temp << "\n";
	}
	OutFile.close();
	return  0;
} 
