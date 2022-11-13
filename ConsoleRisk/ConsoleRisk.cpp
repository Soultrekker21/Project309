#include <iostream>
#include <string>
#include <list>
#include <queue>

using namespace std;
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

	//Print map with emphasis on player locations
	void printMap(int playerId)
	{
		for (int x = 0; x < boardSize; x++)
		{
			for (int y = 0; y < boardSize; y++)
			{
				//Player IDs of -1 are invalid spaces (or empty) and not to print those out.
				if (board[x][y].playerId != -1)
				{
					if (playerId != board[x][y].playerId)
						std::cout << " " << board[x][y].playerId << "-" << board[x][y].troopCount << " ";
					else
						std::cout << " [" << board[x][y].troopCount << "] "; //highlight player
				}
				else
					std::cout << "     ";
			}
			std::cout << '\n';
		}
	}
};

class Card {
public:
    int type;
};

// The player class and its two derived classes are what should hold
// any and all information about the player, (what cards they have for example)
// ALL FUNCTIONS IN BASE CLASS SHOULD BE VIRTUAL
//TODO: need default constructor and possibly Ro3 implemented
class Player {
public:
	int isAI;
	std::list<Card> cards;
};

//There should only be one console player
class ConsolePlayer : Player{
public:

    /**
     * For getting console input, pass a char array of acceptable inputs
     * @param validInputs array of desired inputs
     * @param size number of valid inputs (array size)
     * @return character inputed
     */
    char getConsoleInput (char * validInputs, int size){
        char inp = 0;
        while (true){
            cout<< "(valid inputs:";
            for(int i=0; i<size; i++){
                cout<< " " << validInputs[i] <<",";
            }
            cout<<"):";
            cin>>inp;
            for(int i=0; i<size; i++){
                if(inp == validInputs[i]){
                    return validInputs[i];
                }
            }
        }
    }

//    Unknown if string input needed yet
//    string getConsoleInput(string * validInputs, int size){
//        return "";
//    }
};

class ComputerPlayer : Player{

};

class Game { //queue goes here
public:
    //Initialize Players
    ConsolePlayer p1;
    ComputerPlayer p2,p3,p4;


    queue<int> pTurn;


    void start(){
        //Initial intro to the game
        cout << "Welcome to Console Risk! \n"
                "Would you like to read the rules before playing?\n";

        //example of getting console input
        char c[2]= {'y','n'};
        if(p1.getConsoleInput(c,2) == 'y') readRules();
    }

    //Function call for reading rules, maybe make 'rules' an optional input
    //for wanting to check rules mid-game
    void readRules(){
        //TODO: RULES TEXT NEEDS TO BE UPDATED
        string rules = "Goal: To control every space on the board\n"
                       "Players: Four\n"
                       "Spaces: Every space has any number of troops";
        cout<<rules;
    }
};


int main()
{
    Game Risk;
    Risk.start();

    for(int i = 0; i < 100; i++){
        cout<< 1;
    }

	Board map = Board(4, _map);
//	map.printMap();
    //prints out map with player locations highlighted
	map.printMap(1);
}