 // player.cpp
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .cpp subor player.cpp

 /* player.cpp definiton*/
#include "player.h"
#include <string>
#include <sstream>
#include <iostream>

//! A constructor.
/*!
  constructs object Player, requires coordinates and ID 
*/
Player::Player(int start_row, int start_col, int id_number){
    this->row = start_row ;
    this->col = start_col ;
    this->id = id_number ;
    this->card = -1 ;
    this->points = 0;
}

//! Function moves player to new coordinates
/*!
  direction can be U D L R
*/
void Player::move(char direction)
{
    switch (direction){
        case 'U':
            this->row--;
            break;
        case 'D':
            this->row++;
            break;
        case 'L':
            this->col--;
            break;
        case 'R':
            this->col++;
            break;
    }
    return;
}

//!returns number of actual card
int Player::actual_card(){
    return this->card;
}

//!draws card from pack to player
void Player::set_card(int value){
    this->card=value;
    return;
}

//!increase points gained by 1, set actual card to -1
void Player::card_found(){
    this->points++;
    this->card--;
}

int ActivePlayers::number_of_players;
int ActivePlayers::on_turn;

//! A constructor.
/*!
  constructs object ActivePlayers, requires number of players that will play this game
*/
ActivePlayers::ActivePlayers(int number, int board_size){
    ActivePlayers::number_of_players=number;
    ActivePlayers::on_turn=0;
    for (int i=0; i< number; i++){
        switch (i){
            case 0:
                game_players[0] = new Player(0, 0, 0);
                break;
            case 1:
                game_players[1] = new Player(board_size -1, board_size -1, 1);
                break;
            case 2:
                game_players[2] = new Player(0, board_size -1, 2);
                break;
            case 3:
                game_players[3] = new Player(board_size -1, 0, 3);
                break;
        }
    }
}

//destructor
ActivePlayers::~ActivePlayers(){
    for (int i=0; i< this->number_of_players; i++)
        delete[] game_players[i];
}

//! Function set next player on turn
void ActivePlayers::end_turn(){
    if (ActivePlayers::on_turn +1 < ActivePlayers::number_of_players){
        ActivePlayers::on_turn++;
        return;
    }else ActivePlayers::on_turn=0;
}

//! Function check if any player has won
bool ActivePlayers::is_winner(int cards){
    for (int i=0; i< ActivePlayers::number_of_players; i++){
        if (game_players[i]->points >= cards/ActivePlayers::number_of_players){
			std::cout << "Player " << i << " Has won !!" << std::endl;
			return true;
		}
    }
    return false;
}

//! Creates string with info about players
std::string ActivePlayers::savePlayers(){
    std::string saveString;
    saveString += std::to_string(ActivePlayers::number_of_players) + " ";
    saveString = saveString + std::to_string(ActivePlayers::on_turn) + " ";

    for (int i = 0; i < number_of_players; i++)
    {
        saveString += std::to_string(game_players[i]->id) + " ";
        saveString += std::to_string(game_players[i]->points) + " ";
        saveString += std::to_string(game_players[i]->card) + " ";
        saveString += std::to_string(game_players[i]->row) + " ";
        saveString += std::to_string(game_players[i]->col) + " ";
    }

    return saveString;
}

ActivePlayers::ActivePlayers(std::string inputStr)
{
    std::stringstream  strStream;
    strStream << inputStr;
    int num;

    strStream >> ActivePlayers::number_of_players;

    strStream >> ActivePlayers::on_turn;
    
    for (int i = 0; i < number_of_players; i++)
    {
        game_players[i] = new Player(0, 0, 0);
        strStream >> game_players[i]->id;
        strStream >> game_players[i]->points;
        strStream >> game_players[i]->card;
        strStream >> game_players[i]->row;
        strStream >> game_players[i]->col;
    }

    

}

