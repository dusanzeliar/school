// output.cpp
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .h subor output.h
 /* output.cpp definiton*/

#include <iostream>     // std::cout
#include <sstream>
#include "output.h"

void printMenu()
{
    using namespace std;
    cout << "Game labyrint" << endl;
    cout << "New game, enter \"game\" " << endl;
    cout << "Load game, enter \"load\" " << endl;
    cout << "Exit game, enter \"exit\" " << endl;
    return;
}

void printSaveInstructions(){
    using namespace std;
    cout << "Enter game name" << endl;
}

void printErrorOnRead(){
    using namespace std;
    cout << "Loading game has file, application will exit" << endl;
}

void printFirstRound(){
    using namespace std;
    cout << "Can not undo last round, this is first one" << endl;
}

void printSaveError(){
    using namespace std;
    cout << "Error on save. Game was not saved." << endl;
}

void printSaveSuccess(){
    using namespace std;
    cout << "Game was saved." << endl;
}

void printGameInfo(){
    using namespace std;
    cout << "Game info:" << endl;
    cout << "Whenever during game commands:" << endl;
    cout << "Exit application, enter \"exit\" " << endl;
    cout << "Load saved game, enter \"load\" " << endl;
    cout << "At the start of players turn commands:" << endl;
    cout << "Restore last turn game state, enter \"undo\" " << endl;
    cout << "Save game state, enter \"save\" " << endl;
    cout << "Enter: number of players(2/3/4) number of cards(12/24) labyrinth size(5/7/9/11)" << endl;
    return;
}

char numToTreasure(int num)
{
    switch (num)
    {
        case -1:
            return ' ';
        case 0:
            return 'a';
        case 1:
            return 'b';
        case 2:
            return 'c';
        case 3:
            return 'd';
        case 4:
            return 'e';
        case 5:
            return 'f';
        case 6:
            return 'g';
        case 7:
            return 'h';
        case 8:
            return 'i';
        case 9:
            return 'j';
        case 10:
            return 'k';
        case 11:
            return 'l';
        case 12:
            return 'm';
        case 13:
            return 'n';
        case 14:
            return 'o';
        case 15:
            return 'p';
        case 16:
            return 'q';
        case 17:
            return 'r';
        case 18:
            return 's';
        case 19:
            return 't';
        case 20:
            return 'u';
        case 21:
            return 'v';
        case 22:
            return 'w';
        case 23:
            return 'y';
        default:
            return 'z';
    }
}


void drawStone(Stone *stoneToDraw, char c, int allowInc, int *player_id, int *row, int *column, int numOfPlayers, int r, int col)
{
    using namespace std;
    int playerChar = 100;

    if (player_id)
        for (int i = 0; i < numOfPlayers; i++)
        {
            if (row[i] == r && column[i] == col)
            {
                playerChar = player_id[i];
                break;
            }
        }

    char itemOnStone;

    if (playerChar == 100)
        itemOnStone = numToTreasure(stoneToDraw->treasureNumber);
        else
            itemOnStone = '0' + playerChar;

    //char itemOnStone = numToTreasure(stoneToDraw->treasureNumber);

    if (stoneToDraw->stoneType == 'I')
    {
        if (stoneToDraw->left)
        {
            if (allowInc == 0)
                cout << c << c << c;
            if (allowInc == 1)
                cout << ' ' << itemOnStone << ' ';
            if (allowInc == 2)
                cout << c << c << c;
        }
                
        if (stoneToDraw->up)
        {
            if (allowInc == 0)
                cout << c << ' ' << c;
            if (allowInc == 1)
                cout << c << itemOnStone << c;
            if (allowInc == 2)
                cout << c << ' ' << c;
        }
    }

    if (stoneToDraw->stoneType == 'L')
    {
        if (stoneToDraw->left && stoneToDraw->up)
        {
            if (allowInc == 0)
                cout << c << ' ' << c;
            if (allowInc == 1)
                cout << ' ' << itemOnStone << c;
            if (allowInc == 2)
                cout << c << c << c;
        }
                
        if (stoneToDraw->left && stoneToDraw->down)
        {
            if (allowInc == 0)
                cout << c << c << c;
            if (allowInc == 1)
                cout << ' ' << itemOnStone << c;
            if (allowInc == 2)
                cout << c << ' ' << c;
        }

        if (stoneToDraw->up && stoneToDraw->right)
        {
            if (allowInc == 0)
                cout << c << ' ' << c;
            if (allowInc == 1)
                cout << c << itemOnStone << ' ';
            if (allowInc == 2)
                cout << c << c << c;
        }

        if (stoneToDraw->down && stoneToDraw->right)
        {
            if (allowInc == 0)
                cout << c << c << c;
            if (allowInc == 1)
                cout << c << itemOnStone << ' ';
            if (allowInc == 2)
                cout << c << ' ' << c;
        }
    }

    if (stoneToDraw->stoneType == 'T')
    {
        if (!stoneToDraw->up)
        {
            if (allowInc == 0)
                cout << c << c << c;
            if (allowInc == 1)
                cout << ' ' << itemOnStone << ' ';
            if (allowInc == 2)
                cout << c << ' ' << c;
        }

        if (!stoneToDraw->right)
        {
            if (allowInc == 0)
                cout << c << ' ' << c;
            if (allowInc == 1)
                cout << ' ' << itemOnStone << c;
            if (allowInc == 2)
                cout << c << ' ' << c;
        }

        if (!stoneToDraw->down)
        {
            if (allowInc == 0)
                cout << c << ' ' << c;
            if (allowInc == 1)
                cout << ' ' << itemOnStone << ' ';
            if (allowInc == 2)
                cout << c << c << c;
        }

        if (!stoneToDraw->left)
        {
            if (allowInc == 0)
                cout << c << ' ' << c;
            if (allowInc == 1)
                cout << c << itemOnStone << ' ';
            if (allowInc == 2)
                cout << c << ' ' << c;
        }

    }
}

void drawBoard(std::string inputStr, std::string inputStr2)
{
    using namespace std;
    Board boardToDraw (inputStr);
    
    std::stringstream  strStream;
    strStream << inputStr2;
    int num;
    int tmp_points;
    int player_on_turn;
    int player_on_turn_points;
    int tmp_card;
    int player_on_turn_card;

    strStream >> num;
    int numOfPlayers = num;

    strStream >> player_on_turn;
    
    int player_id[4];
    int row[4];
    int col[4];   

    for (int i = 0; i < numOfPlayers; i++)
    {
        strStream >> player_id[i];
        strStream >> tmp_points;
        strStream >> tmp_card;
        strStream >> num;
        row[i] = num;
        strStream >> num;
        col[i] = num;

        if(player_id[i] == player_on_turn) {
            player_on_turn_points=tmp_points;
            player_on_turn_card=tmp_card;
        }
    }
    cout << "Player " << player_on_turn << " Card " << numToTreasure(player_on_turn_card) << " actual points " << player_on_turn_points << endl;
    cout << "Free stone" << endl;

    int allowInc = 0, i = 0;
    char wallChar = '#';
    
    drawStone(boardToDraw.freeStone, wallChar, 0, NULL, NULL, NULL,0, 0, 0);
    cout << endl;
    drawStone(boardToDraw.freeStone, wallChar, 1, NULL, NULL, NULL,0, 0, 0);
    cout << endl;
    drawStone(boardToDraw.freeStone, wallChar, 2, NULL, NULL, NULL,0, 0, 0);
    cout << endl << endl;

    while (i < boardToDraw.size)
    {
        for(int j = 0; j<boardToDraw.size; j++)
        {
            drawStone(boardToDraw.gameBoard[i][j]->actStone, wallChar, allowInc, player_id, row, col, numOfPlayers, i, j);

            if (wallChar == '#')
                wallChar = 'X';
                else
                    wallChar = '#';

            if (j == boardToDraw.size-1)
            {
                if (allowInc == 1 || allowInc == 0)
                {
                    if (wallChar == '#')
                        wallChar = 'X';
                        else
                            wallChar = '#';
                }
                cout << endl;
            }
        }
        
        allowInc++;
    
        if (allowInc == 3)
        {
            allowInc = 0;
            i++;
        }
    
    }
}
