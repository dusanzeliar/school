 // input.h
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .h subor input.h

//=================================
// include guard
#ifndef __INPUT_H_INCLUDED__
#define __INPUT_H_INCLUDED__
#include <string>


//=================================
// function prototypes
std::string input_name();
void printSaveInstructions(); 
void input_game_properties(int *players, int *cards, int *board);
void input_menu(char * choice);
void input_shift(int *row, int *col, char * extra);
void input_move(int *row, int *col, char * extra);
void input_rotate(char * extra);

//=================================


#endif // __INPUT_H_INCLUDED__