#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <queue>

using namespace std;
const int boardSize = 20;

//20x20 map design
//#=valid space, ' '=Ocean or water
// '_' = non-space land
//DO NOT CHANGE MAP WITHOUT CHANGING ADJACENCY LIST XY VALUES
// 27 locations because 26 letters in alphabet, simplest way
// of containing input
char _map[20][20] =
{ 
"   _ _         _   ",
"  _#__      ____#_ ",
" ____#_    __#_____",
"_#__#_____#______#_",
" ______   _________",
"  _#___#   _____#__",
"  ___  _   __  _  _",
"  #_      ___ _#_  ",
"   __     _#__     ",
"  __#__   ___#__   ",
" _______  _______  ",
"__#_____  _#___#_  ",
"________#____#___  ",
" _#__#__  _____    ",
" ______   __#_    _",
" _____     ____#___",
" ___             _#",
"  _#              _",
"   _               ",
"                   " 
};




class Space
{
public:
	//When playerID is -1 that means its an empty space or its invalid, and cannot be won or taken.
	int playerId;
	int troopCount;
	int spaceId;


	Space(int _playerId, int _troopCount, int _spaceId)
	{
		playerId = _playerId;
		troopCount = _troopCount;
		spaceId = _spaceId;
	}

	Space(int _landType = -2)
	{
		playerId = _landType;
		troopCount = -1;
		spaceId = 0;
	}

	//prints the space, if highlighted prints the space highlighted
	//Added char replacement tool for future
	void printSpace(bool isHighlighted = false, char replace = 0){
	    if(isHighlighted) cout << " [" << troopCount << "] "; //highlight player
	    else if(replace != 0)  cout << " [" << replace << "] "; //print out character
	    else cout << " " << playerId << ":" << troopCount << " ";
	}

};

//Dependency: Space class
class Board
{
private:
	Space board[boardSize][boardSize];

	//holds a reference to adjacent spaces
	//Neccesarry for checking possible attack and defense locations
	map<int, vector<int>> AdjacencyMap;
	//Holds board location of Space ID vector should only have two entries, xy
	map<int, vector<int>> coordinateMap;

public:
	Board(int numPlayers, char _in_map[boardSize][boardSize] = _map)
	{
		generate(numPlayers, _in_map);
		//initialize AdjacencyMap inside each space
		AdjacencyMap[1] = {3,5};
		AdjacencyMap[2] = {4,8};
		//TODO: FINISH ADJACENCY MAP

	}

	//Generate spaces and player counts for the board
	void generate(int numPlayers, char _in_map[boardSize][boardSize])
	{
	    //counter for assigning all 27 space IDs
	    int spaceId = 1;
		for (int x = 0; x < boardSize; x++)
		{
			for (int y = 0; y < boardSize; y++)
			{
				//randomly assign each space a player id and their number of troops
				if (_in_map[x][y] == '#'){
				    board[x][y] = Space(rand() % numPlayers + 1, rand() % numPlayers + 1, spaceId);
				    coordinateMap[spaceId] = {x,y};
				    spaceId++;
				}
				else if (_in_map[x][y] == '_') {board[x][y] = Space(-1);}
				else { board[x][y] = Space(-2); }//null space if the char is a space
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
				if (board[x][y].playerId >= 0)
				    board[x][y].printSpace();
				else if(board[x][y].playerId == -1)
					std::cout << "_____";
				else
				    std::cout << "     ";
			}
			std::cout << '\n';
		}
	}

	//Print map with emphasis on player locations
	void printMap(int playerId)
	{
	    cout<<"Below is map with player " << playerId << "'s locations highlighted between brackets\n";
		for (int x = 0; x < boardSize; x++)
		{
			for (int y = 0; y < boardSize; y++)
			{
				//Player IDs of -1 are invalid spaces (or empty) and not to print those out.
				if (board[x][y].playerId >=0)
				{
					if (playerId != board[x][y].playerId)
					    board[x][y].printSpace();
					else
					    board[x][y].printSpace(true);

				}
				else if(board[x][y].playerId == -1)
				    std::cout << "_____";
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
     * For getting console input, pass a vector of acceptable inputs
     * @param validInputs array of desired inputs
     * @return character inputed
     */
    char getConsoleInput (vector<char> validInputs){
        char inp = 0;
        while (true){
            cout<< "(valid inputs:";
            for(int i=0; i<validInputs.size(); i++){
                cout<< " " << validInputs[i] <<",";
            }
            cout<<"):";
            cin>>inp;
            for(int i=0; i < validInputs.size(); i++){
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
        if(p1.getConsoleInput({'y','n'}) == 'y') readRules();
    }

    //Function call for reading rules, maybe make 'rules' an optional input
    //for wanting to check rules mid-game
    void readRules(){
        //TODO: RULES TEXT NEEDS TO BE UPDATED
        string rules = "Goal: To control every space on the board\n"
                       "Players: Four (including console player)\n"
                       "Spaces: Every space has a number of player troops\n"
                       "Attacking: \n";
        cout<<rules;
    }
};


int main()
{
    Game Risk;
    Risk.start();

	Board map = Board(4, _map);
//	map.printMap();
    //prints out map with player locations highlighted
	map.printMap(1);
}