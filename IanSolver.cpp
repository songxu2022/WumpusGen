#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "levelmake.h"

uint SIZE;
uint PITS;
uint QUANT;

//current (known) issues:
//Need to add functionality of figuring out where pits are, when possible. Harder than gold / wumpus. Necessary for some of hardest puzzles.
//Also need to "remember" that the square where wumpus was killed must be safe after killing it. This is likely something where the NODE class is
//going to come in handy. just starting at the wumpus spot might not be enough in all cases. need to use NODE.

board readFile(std::string fileName)
{
	//takes in a standard text file and reads it to a 2d vector.
	board b = build(SIZE);
	char c;
	uint x = 0;
	uint y = 0;

	std::ifstream inFile;
	inFile.open(fileName);
	if (!inFile)
	{
		std::cerr << "Unable to open file!";
		exit(1);
	}
	while (inFile >> c)
	{
		b[x][y] = c;
		x++;
		std::cout << c;
		if (x == SIZE)
		{
			std::cout << std::endl;
			x = 0;
			y++;
		}
	}
	inFile.close();
	return b;
}

void writeFile(std::string fileName, board& b)
{
	std::ofstream outFile;
	outFile.open(fileName, std::ios_base::app);
	if (!outFile)
	{
		std::cerr << "Unable to open file!";
		exit(1);
	}
	for (uint i = 0; i < SIZE; ++i)
	{
		for (uint j = 0; j < SIZE; ++j)
		{
			outFile << b[j][i];
		}
		outFile << "\n";
	}
	outFile << "\n";
	outFile.close();
}

bool nextTo(board& b, board& known, std::string targ, int x, int y)
{
	//this one is a bit complicated, hopefully we can get rid of these nested loops.
	//given an xy position on the board, it checks that all the blocks next to it that we've seen
	//have the clue for the target.
	//The usefulness lies in that if the function returns false, the xy position must NOT contain the
	//target value, based on the knowledge gathered so far.

	bool out = true;
	// std::cout << "nextTo checking position: (" << x << ", " << y << ")" << std::endl;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			// std::cout << "i, j" << i << ", " << j << std::endl;
			if (inBoard(x+i, y+j, SIZE) && (i != 0 || j != 0) && (i == 0 || j == 0))
			{
				if (known[x+i][y+j] == "seen")
				{
					bool hasSign = false;
					// std::cout << "(" << x+i << ", " << y+j << ")" << std::endl;
					for (int i2 = -1; i2 < 2; ++i2)
					{
						for (int j2 = -1; j2 < 2; ++j2)
						{
							if (inBoard(x+i+i2, y+j+j2, SIZE) && (i2 != 0 || j2 != 0) && (i2 == 0 || j2 == 0))
							{
								if (b[x+i+i2][y+j+j2] == targ)
								{
									hasSign = true;
								}
							}
						}
					}
					if (!hasSign)
						out = false;
				}
			}
		}
	}
	return out;
}

void narrow(board& b, board& known, std::string targ, std::list<coord>& coordsList)
{
	//"narrows down" the options for where a target object could be.
	//The target object must be either gold or wumpus, as these are the only two that are guaranteed to
	//be of exact quantity 1 per board.
	for (std::list<coord>::iterator i = coordsList.begin(); i != coordsList.end(); i++)
	{
		if (!nextTo(b, known, targ, i->first, i->second))
		{
			// std::cout << "narrowing down, removed: " << i->first << ", " << i->second << std::endl;
			i = coordsList.erase(i);
		}
	}
}

std::string adjacent(board& b, int size, int x, int y, bool allowWump = false)
{
	//checks adjacent squares, finds which clues (stench, glitter, etc) would be seen at the square (x, y).
	//gives string output, with b for breeze, s for stench, and g for glitter. Combinations are always in the
	//same order - if breeze is found, b will always be first, and stench will always be before glitter.
	//IE: breeze + stench returns bs, breeze + glitter returns bg, glitter + stench returns sg.
	bool wumpus = false;
	bool pit = false;
	bool gold = false;
	std::string out;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			if (inBoard(x+i, y+j, size) && (i != 0 || j != 0) && (i == 0 || j == 0))
			{
				if ((b[x+i][y+j]) == "w" && (!allowWump))
					wumpus = true;
				if (b[x+i][y+j] == "p")
					pit = true;
				if ((b[x+i][y+j] == "g"))
					gold = true;
			}
		}
	}
	if (pit)
		out += 'b';
	if (wumpus)
		out += 's';
	if (gold)
		out += 'g';
	if (out.length() == 0)
		out = "safe";
	return out;
}

std::list<coord> possibleLocations(board& b, board& known, std::string targ, int x, int y)
{
	//determines which locations are possible locations for the target object. Does not use reductive reasoning.
	std::list<coord> coordList;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			if (inBoard(x+i, y+j, SIZE))
			{
				if (known[x+i][y+j] != "seen" && known[x+i][y+j] != "gold" && known[x+i][y+j] != "wumpus"
					&& (i != 0 || j != 0) && (i == 0 || j == 0))
				{
					if(nextTo(b, known, targ, x+i, y+j))
					{
						coord c(x+i, y+j);
						coordList.push_back(c);
					}
				}
			}
		}
	}
	return coordList;
}


bool getInfo(board& b, board& known, int x, int y, std::list<coord>& wumpLocs, std::list<coord>& goldLocs)
{
	//recursive function to explore the board, finding all the safe spots
	// std::cout << "(" << x << ", " << y << ")\n";
	bool out = false;
	int wumpX = -1;
	int wumpY = -1;
	known[x][y] = "seen";
	if (b[x][y] == "g" || goldLocs.size() == 1)
	{
		return true;
	}
	std::string status = adjacent(b, SIZE, x, y);
	if ((status == "bs" || status == "s" || status == "sg") && wumpLocs.size() != 1)
	{
		std::list<coord> temp = possibleLocations(b, known, "w", x, y);
		if (wumpLocs.size() == 0)
			wumpLocs = temp;
		else
		{
			std::list<coord> temp2 = wumpLocs;
			std::set_intersection(temp.begin(), temp.end(), temp2.begin(), temp2.end(), wumpLocs.begin());
			wumpLocs.sort();
			wumpLocs.unique();
			if (wumpLocs.size() == 1)
			{
				wumpX = wumpLocs.begin()->first;
				wumpY = wumpLocs.end()->second;
				known[wumpX][wumpY] = "wumpus"; //we know the wumpus is here now.
			}
		}
	}
	status = adjacent(b, SIZE, x, y);
	if (status == "bg" || status == "sg" || status == "g")
	{
		std::list<coord> temp = possibleLocations(b, known, "g", x, y);
		if (goldLocs.size() == 0)
			goldLocs = temp;
		else
		{
			std::list<coord> temp2 = goldLocs;
			std::set_intersection(temp.begin(), temp.end(), temp2.begin(), temp2.end(), goldLocs.begin());
			goldLocs.sort();
			goldLocs.unique();
			if (goldLocs.size() == 1)
			{
				// std::cout << "gold location found!!!!!" << std::endl;
				return true;
			}
		}
	}

	if (wumpLocs.size() == 1)
	{
		wumpX = wumpLocs.begin()->first;
		wumpY = wumpLocs.begin()->second;
		status = adjacent(b, SIZE, x, y, true);	
	}

	if (status == "safe" || status == "g") //g == glitter
	{
		for (int i = -1; i < 2; ++i)
		{
			for (int j = -1; j < 2; ++j)
			{
				if (inBoard(x+i, y+j, SIZE) && (i != 0 || j != 0) && (i == 0 || j == 0) && (x+i != wumpX || y+j != wumpY))
				{
					if (known[x+i][y+j] != "seen")
					{
						if (getInfo(b, known, x+i, y+j, wumpLocs, goldLocs))
						{
							out = true;
						}
					}

				}
			}
		}
	}
	
	// std::cout << "(" << x << ", " << y << "): " << status << std::endl;
	if (goldLocs.size() == 1)
		return true;
	return out;
}
bool solveable(board& b, board& known)
{
	//combines the basic info gathering function with some logic & mostly reductive reasoning to determine the solvability of a board
	//board b is the complete board, board known is the board that is "played" - it has no information on it other than the size
	board known2(known);
	board known3(known2);
	std::list<coord> wumpLocs;
	std::list<coord> goldLocs;
	bool first = getInfo(b, known, 0, SIZE-1, wumpLocs, goldLocs);
	if (first)
		return true;
	else
	{
		narrow(b, known, "w", wumpLocs);
		narrow(b, known, "g", goldLocs);
		if (goldLocs.size() == 1)
			return true;
	}
	if (wumpLocs.size() == 1)
	{
		// std:: cout << "found wump\n";
		board b2 = b;
		b2[wumpLocs.begin()->first][wumpLocs.begin()->second] = "e"; //remove wumpus from board as if it had been shot.
		if(!getInfo(b2, known2, wumpLocs.begin()->first, wumpLocs.begin()->second, wumpLocs, goldLocs))
		{
			narrow(b2, known2, "g", goldLocs);
			if (goldLocs.size() == 1)
				return true;
		}
		else
			return true;
	}
	return false;
}

int main()
{
	std::string testingQuery;
	std::cout << "Testing mode? (y/n)" << std::endl;
	std::cin >> testingQuery;
	std::cout << "How many maps?" << std::endl;
	std::cin >> QUANT;
	std::cout << "What size? (edgelength)" << std::endl;
	std::cin >> SIZE;
	std::cout << "How many pits? (per map)" << std::endl;
	std::cin >> PITS;
	bool testing = true;
	if (testingQuery != "y" && testingQuery != "yes")
		testing = false;
	if (!testing)
	{
		std::vector<board> boards = makeBoards(SIZE, QUANT, PITS); //makes 1 board, with size 4 (edgelength)
		int counter = 0;
		std::set<board> successes;
		for (uint i = 0; i < QUANT; ++i)
		{
			board b = boards[i];
			board known = build(SIZE);
			known[0][SIZE-1] = "seen";
			bool success = solveable(b, known);
			if (success)
			{
				counter++;
				successes.insert(b);
			}
		}
		for (std::set<board>::iterator i = successes.begin(); i != successes.end(); ++i)
		{
			board x = *i;
			writeFile("wumpusOut.txt", x);
		}
		std::cout << counter << " were successful!" << std::endl;
		std::cout << successes.size() << " were unique!" << std::endl;
	}
	else
	{
		board b = readFile("wumpus1.txt");
		board known = build(SIZE);
		known[0][3] = "seen";
		bool success = solveable(b, known);
		if (success)
		{
			std::cout << "success!";
		}
	}
}
