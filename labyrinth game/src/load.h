 // load.h
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .h subor load.h

//=================================
// include guard
#ifndef __LOAD_H_INCLUDED__
#define __LOAD_H_INCLUDED__
#include <string>

//=================================
// function prototypes
bool load_game(std::string * saved_players, std::string * saved_cards, std::string * saved_board, std::string filename);

//=================================


#endif // __LOAD_H_INCLUDED__