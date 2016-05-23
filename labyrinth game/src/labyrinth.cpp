 // labyrinth.cpp
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .cpp subor labyrinth.cpp
 /* labyrinth.cpp definiton*/
#include "game.h"
#include <string>
#include <iostream> 

int main()
{
	using namespace std;

	char state;
	string user_input;

	int cards_input;
    int board_input;
    int player_input;

    printMenu();
    input_menu(&state);

    do{ 
        switch (state)
        {
            case 'E':
            case 'W':
                return 0;
                break;
            case 'G':
                printGameInfo();
                input_game_properties(&player_input, &cards_input, &board_input);
                state= game(player_input, cards_input, board_input);
                break;
            case 'L':
                printSaveInstructions();
                user_input=input_name();
                state= gameLoad(user_input);
                break;
            case 'U':
                state= gameLoad("undo");
                break;


        }
    }while(state == 'L' || state == 'U');



}
