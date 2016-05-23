 // game.h
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .h subor game.h

//=================================
// include guard
#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__
#include "cards.h"
#include "player.h"
#include "board.h"
#include "input.h"
#include "output.h"
#include "save.h"
#include "load.h"

//=================================
// function prototypes
void get_card(Player *selected_player, CardPack * pack); //!if player doesnt have card, get next card from pack, put into hand
bool check_treasure(Board * game, Player *selected_player,CardPack * pack);//!function returns true and draw card for player if he stands on treasure
void move_players(int size,int row, int col, char direction, ActivePlayers *players_group);//!function shifts players standing on stone that has been shifted
bool try_move(Board * game, Player *moving_player,int row, int col );//! funtion return true and moves player is possible
char game(int player_input, int cards_input, int board_input); //!initialize and play new game
char gameLoad(std::string game_name);//!load and play game

//=================================


#endif // __GAME_H_INCLUDED__
