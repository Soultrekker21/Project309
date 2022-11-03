#include <iostream>
#include <string>

const int boardSize = 20;

//20x20 map design
//#=valid space, ' '=Ocean or water
char _map[20][20] = 
{ 
"   # #         #   ",
"  ####      ###### ",
" ######    ########",
"###################",
" ######   #########",
"  ######   ########",
"  ###  #   ##  #  #",
"  ##      ### ###  ",
"   ##     ####     ",
"  #####   ######   ",
" #######  #######  ",
"########  #######  ",
"#################  ",
" #######  #####    ",
" ######   ####    #",
" #####     ########",
" ###             ##",
"  ##              #",
"   #               ",
"                   " 
};

class Space
{
public:
	//When playerID is -1 that means its an empty space or its invalid, and cannot be won or taken.
	int playerId;
	int troopCount;
	Space(int _playerId, int _troopCount)
	{
		playerId = _playerId;
		troopCount = _troopCount;
	}

	Space()
	{
		playerId = -1;
		troopCount = -1;
	}
};

//Dependency: Space class
class Board
{
private:
	Space board[boardSize][boardSize];
public:
	Board(int numPlayers, char _in_map[boardSize][boardSize] = _map)
	{
		generate(numPlayers, _in_map);
	}

	//Generate spaces and player counts for the board
	void generate(int numPlayers, char _in_map[boardSize][boardSize])
	{
		for (int x = 0; x < boardSize; x++)
		{
			for (int y = 0; y < boardSize; y++)
			{
				//randomly assign each space a player id and their number of troops
				if (_in_map[x][y] == '#')
				board[x][y] = Space(rand() % numPlayers + 1, rand() % numPlayers + 1);
				else
					board[x][y] = Space(); //null space if the char is a space
			}
		}
	}

	//Print out the map in terms of a string
	void printMap()
	{
		for (int x = 0; x < boardSize; x++)
		{
			for (int y = 0; y < boardSize; y++)
			{
				//Player IDs of -1 are invalid spaces (or empty) and not to print those out.
				if (board[x][y].playerId != -1)
					std::cout << " " << board[x][y].playerId << "-" << board[x][y].troopCount << " ";
				else
					std::cout << "     ";
			}
			std::cout << '\n';
		}
	}
};

int main()
{
	Board map = Board(4, _map);
	map.printMap();
}