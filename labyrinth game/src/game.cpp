 // game.cpp
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .cpp subor game.cpp
 /* game engine*/

#include "game.h"
#include <iostream>     // std::cout

//!if player doesnt have card, get next card from pack, put into hand
void get_card(Player *selected_player, CardPack * pack){
    if (selected_player->actual_card() == -1){
        TreasureCard card=pack->popCard();
        selected_player->set_card(card.CardNuber());
    }
    return;
}

//!function returns true and draw card for player if he stands on treasure
bool check_treasure(Board * game, Player *selected_player,CardPack * pack){
    if (selected_player->actual_card() == game->gameBoard[selected_player->row][selected_player->col]->actStone->getTreasure())
    {
        //remove treasure from stone on board
        game->gameBoard[selected_player->row][selected_player->col]->actStone->removeTreasure();
        //add point, remove card
        selected_player->card_found();
        //get next card, put into hand
        get_card(selected_player,pack);
        return true;
    }
    return false;
}

//!function shifts players standing on stone that has been shifted
void move_players(int size,int row, int col, char direction, ActivePlayers *players_group){
    switch (direction){
        case 'U':
            for (int i = 0; i < players_group->number_of_players; i++){
                //check if player is located on same column
                if (players_group->game_players[i]->col == col ){
                    if (players_group->game_players[i]->row == 0){
                        players_group->game_players[i]->row = size-1;
                    }
                    else players_group->game_players[i]->row--;
                }
            }
        break;
             
        case 'D':
            for (int i = 0; i < players_group->number_of_players; i++){
                //check if player is located on same column
                if (players_group->game_players[i]->col == col ){
                    if (players_group->game_players[i]->row == size-1){
                        players_group->game_players[i]->row = 0;
                    }
                    else players_group->game_players[i]->row++;
                }
            }
        break;

        case 'L':
            for (int i = 0; i < players_group->number_of_players; i++){
                //check if player is located on same column
                if (players_group->game_players[i]->row == row ){
                    if (players_group->game_players[i]->col == 0){
                        players_group->game_players[i]->col = size-1;
                    }
                    else players_group->game_players[i]->col--;
                }
            }
        break;

        case 'R':
            for (int i = 0; i < players_group->number_of_players; i++){
                //check if player is located on same column
                if (players_group->game_players[i]->row == row ){
                    if (players_group->game_players[i]->col == size-1){
                        players_group->game_players[i]->col = 0;
                    }
                    else players_group->game_players[i]->col++;
                }
            }
        break;
    }
}

//! funtion return true and moves player is possible
bool try_move(Board * game, Player *moving_player,int row, int col ){
    if (row<0 || row > game->size-1 || col<0 || col > game->size-1) return false;

    bool destination;
    bool start;
    //going left
    if (row == moving_player->row && col == moving_player->col -1){
        start= game->gameBoard[moving_player->row][moving_player->col]->actStone->canGo('L');
        destination= game->gameBoard[row][col]->actStone->canGo('R');
        if (start && destination){
            moving_player->move('L');
            return true;
        }else return false;
    }

    //going right
    if (row == moving_player->row && col == moving_player->col +1){
        start= game->gameBoard[moving_player->row][moving_player->col]->actStone->canGo('R');
        destination= game->gameBoard[row][col]->actStone->canGo('L');
        if (start && destination){
            moving_player->move('R');
            return true;
        }else return false;
    }

    //going up
    if (row == moving_player->row -1 && col == moving_player->col){
        start= game->gameBoard[moving_player->row][moving_player->col]->actStone->canGo('U');
        destination= game->gameBoard[row][col]->actStone->canGo('D');
        if (start && destination){
            moving_player->move('U');
            return true;
        }else return false;
    }

    //going down
    if (row == moving_player->row +1 && col == moving_player->col){
        start= game->gameBoard[moving_player->row][moving_player->col]->actStone->canGo('D');
        destination= game->gameBoard[row][col]->actStone->canGo('U');
        if (start && destination){
            moving_player->move('D');
            return true;
        }else return false;
    }
    return false;
}

//count number of lines
int LinesCount(std::string s)
{
    int count=0;
    for(char& c : s) {
        if (c == '\n') count ++;
    }
    return count;
}

//!remove last line ( called when undo)
std::string RemoveLastLine (std::string str)
{
  unsigned found = str.find_last_of("\n");
  return str.substr(0,found);
}

//!returns last line ( called when load)
std::string ReturnLastLine (std::string str)
{
  unsigned found = str.find_last_of("\n");
  return str.substr(found+1);
}

char game(int player_input, int cards_input, int board_input)
{
    //const int cards_input=12;
    //const int board_input=7;
    //const int player_input=2;

	using namespace std;
    CardPack c_pack(cards_input);
    c_pack.shuffle();

    Board game(board_input);
    game.createGame(cards_input);

    ActivePlayers players_group (player_input, board_input);
    int id=0;
    int col=0,row=0;
    char extra='-';
    char direction;
    bool action_coplete;
    bool stay;
    bool main_operation=false;
    string saved_board;
    string saved_players;
    string saved_cards;

    string filename;

    saved_cards=c_pack.SaveCardPack();
    saved_board=game.saveBoard();
    saved_players=players_group.savePlayers();

    while (1)
    {
        id=players_group.on_turn;
        get_card(players_group.game_players[id], &c_pack);
        check_treasure(&game,players_group.game_players[id],&c_pack);
        if (players_group.is_winner(cards_input)) break;

        //DRAW
        string game_state=game.saveBoard();
        string players_state=players_group.savePlayers();
        drawBoard(game_state, players_state);

        //rotate stone, allows save,load,undo and exit input also
        action_coplete=false;
        do{
            extra='-';
            input_rotate(&extra);

            switch (extra)
            {
                case 'R':
                    game.freeStone->turnRight();
                    //DRAW
                    game_state=game.saveBoard();
                    players_state=players_group.savePlayers();
                    drawBoard(game_state, players_state);
                    break;
                case 'F':
                    action_coplete=true;
                    break;
                case 'E':
                    action_coplete=true;
                    main_operation=true;
                    break;
                case 'S':
                    printSaveInstructions(); 
                    filename=input_name();
                    if (!save_game(saved_players,saved_cards,saved_board,filename)){
                        printSaveError();
                       }else printSaveSuccess();
                    break;
                case 'L':
                    action_coplete=true;
                    main_operation=true;
                    break;
                case 'U':
                    if (LinesCount(saved_cards) > 0){
                        action_coplete=true;
                        main_operation=true;
                    }else printFirstRound(); 
                    break;
            }
        }while(!action_coplete);
        
        //BREAK if load,undo or exit
        if (main_operation == true) break;

        //shift stone
        action_coplete=false;
        do{
            extra='-';
            input_shift(&row,&col,&extra);
            switch (extra)
            {
                case 'E':
                    action_coplete=true;
                    main_operation=true;
                    break;
                case 'L':
                    action_coplete=true;
                    main_operation=true;
                    break;
                //input= row and col 
                case '-':
                    if (game.try_shift(row, col, &direction)) {
                        action_coplete=true;
                        move_players(game.size, row, col, direction, &players_group);
                    }
                    break;
            }
        }while(!action_coplete);

        //BREAK if load or exit
        if (main_operation == true) break;
        

        //DRAW
        game_state=game.saveBoard();
        players_state=players_group.savePlayers();
        drawBoard(game_state, players_state);

        //move player
        action_coplete=false;
        do{
            extra='-';
            input_move(&row,&col,&extra);
            switch (extra)
            {
                case 'E':
                    action_coplete=true;
                    main_operation=true;
                    break;
                case 'L':
                    action_coplete=true;
                    main_operation=true;
                    break;
                case 'F':
                    action_coplete=true;
                    break;
                //input= row and col 
                case '-':
                    if (try_move(&game, players_group.game_players[id], row, col)) {
                        //DRAW
                        game_state=game.saveBoard();
                        players_state=players_group.savePlayers();
                        drawBoard(game_state, players_state);
                    }
                    break;
            }
        }while(!action_coplete);

        //BREAK if load or exit
        if (main_operation == true) break;

        stay=check_treasure(&game,players_group.game_players[id],&c_pack);

        if (players_group.is_winner(cards_input)){
            extra='W';
            break;
        }

        if (!stay) players_group.end_turn();
         
        //ADD ACTUAL STATE TO SAVED
        saved_cards+="\n" + c_pack.SaveCardPack();
        saved_board+="\n" + game.saveBoard();
        saved_players+="\n" + players_group.savePlayers();

    }
    
    switch (extra)
    {
        case 'W':
            return 'W';
            break;
        case 'E':
            return 'E';
        case 'L':
            return 'L';
        case 'U':
            saved_cards= RemoveLastLine(saved_cards);
            saved_board= RemoveLastLine(saved_board);
            saved_players= RemoveLastLine(saved_players);
            save_game(saved_players,saved_cards,saved_board,"undo");
            return 'U';
    }
    return '-';
}




char gameLoad(std::string game_name)
{
    using namespace std;

    string saved_board;
    string saved_players;
    string saved_cards;

    string init_board;
    string init_players;
    string init_cards;





    load_game(&saved_players, &saved_cards, &saved_board, game_name);
    saved_players.pop_back();
    saved_cards.pop_back();
    saved_board.pop_back();


    if (saved_players.empty() || saved_cards.empty() || saved_board.empty()){
        printErrorOnRead();
        return 'E'; 
    }
     if (LinesCount(saved_cards) >0){
        //get last lines
        init_board=ReturnLastLine(saved_board);
        init_players=ReturnLastLine(saved_players);
        init_cards=ReturnLastLine(saved_cards);
     }else
     {
        init_board=saved_board;
        init_players=saved_players;
        init_cards=saved_cards;
     }


    CardPack c_pack(init_cards);

    Board game (init_board);


    ActivePlayers players_group (init_players);

    int cards_input=c_pack.pack_size;
    int board_input=game.size;
    int player_input=players_group.number_of_players;


    int id=0;
    int col=0,row=0;
    char extra='-';
    char direction;
    bool action_coplete;
    bool stay;
    bool main_operation=false;



    string filename;

    while (1)
    {
        id=players_group.on_turn;
        get_card(players_group.game_players[id], &c_pack);
        check_treasure(&game,players_group.game_players[id],&c_pack);
        if (players_group.is_winner(cards_input)) break;

        //DRAW
        string game_state=game.saveBoard();
        string players_state=players_group.savePlayers();
        drawBoard(game_state, players_state);

        //rotate stone, allows save,load,undo and exit input also
        action_coplete=false;
        do{
            extra='-';
            input_rotate(&extra);

            switch (extra)
            {
                case 'R':
                    game.freeStone->turnRight();
                    //DRAW
                    game_state=game.saveBoard();
                    players_state=players_group.savePlayers();
                    drawBoard(game_state, players_state);
                    break;
                case 'F':
                    action_coplete=true;
                    break;
                case 'E':
                    action_coplete=true;
                    main_operation=true;
                    break;
                case 'S':
                    printSaveInstructions(); 
                    filename=input_name();
                    if (!save_game(saved_players,saved_cards,saved_board,filename)){
                        printSaveError();
                       }else printSaveSuccess();
                    break;
                case 'L':
                    action_coplete=true;
                    main_operation=true;
                    break;
                case 'U':
                    if (LinesCount(saved_cards) > 0){
                        action_coplete=true;
                        main_operation=true;
                    }else printFirstRound(); 
                    break;
            }
        }while(!action_coplete);
        
        //BREAK if load,undo or exit
        if (main_operation == true) break;

        //shift stone
        action_coplete=false;
        do{
            extra='-';
            input_shift(&row,&col,&extra);
            switch (extra)
            {
                case 'E':
                    action_coplete=true;
                    main_operation=true;
                    break;
                case 'L':
                    action_coplete=true;
                    main_operation=true;
                    break;
                //input= row and col 
                case '-':
                    if (game.try_shift(row, col, &direction)) {
                        action_coplete=true;
                        move_players(game.size, row, col, direction, &players_group);
                    }
                    break;
            }
        }while(!action_coplete);

        //BREAK if load or exit
        if (main_operation == true) break;
        

        //DRAW
        game_state=game.saveBoard();
        players_state=players_group.savePlayers();
        drawBoard(game_state, players_state);

        //move player
        action_coplete=false;
        do{
            extra='-';
            input_move(&row,&col,&extra);
            switch (extra)
            {
                case 'E':
                    action_coplete=true;
                    main_operation=true;
                    break;
                case 'L':
                    action_coplete=true;
                    main_operation=true;
                    break;
                case 'F':
                    action_coplete=true;
                    break;
                //input= row and col 
                case '-':
                    if (try_move(&game, players_group.game_players[id], row, col)) {
                        //DRAW
                        game_state=game.saveBoard();
                        players_state=players_group.savePlayers();
                        drawBoard(game_state, players_state);
                    }
                    break;
            }
        }while(!action_coplete);

        //BREAK if load or exit
        if (main_operation == true) break;

        stay=check_treasure(&game,players_group.game_players[id],&c_pack);

        if (players_group.is_winner(cards_input)){
            extra='W';
            break;
        }

        if (!stay) players_group.end_turn();
         
        //ADD ACTUAL STATE TO SAVED
        saved_cards+="\n" + c_pack.SaveCardPack();
        saved_board+="\n" + game.saveBoard();
        saved_players+="\n" + players_group.savePlayers();

    }
    
    switch (extra)
    {
        case 'W':
            return 'W';
            break;
        case 'E':
            return 'E';
        case 'L':
            return 'L';
        case 'U':
            saved_cards= RemoveLastLine(saved_cards);
            saved_board= RemoveLastLine(saved_board);
            saved_players= RemoveLastLine(saved_players);
            save_game(saved_players,saved_cards,saved_board,"undo");
            return 'U';
    }
    return '-';
}

