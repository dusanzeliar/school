 // output.h
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .h subor output.h

//=================================
// include guard
#ifndef __OUTPUT_H_INCLUDED__
#define __OUTPUT_H_INCLUDED__

#include "board.h"
#include "stone.h"
#include "player.h"
//=================================

// function prototypes
void printErrorOnRead();
void printMenu();
void printFirstRound();
void printSaveError();
void printSaveSuccess();
void printSaveInstructions(); 
void printGameInfo();
char numToTreasure(int num);
void drawStone(Stone *stoneToDraw, char c, int allowInc, int *player_id, int *row, int *column, int numOfPlayers, int r, int col);
void drawBoard(std::string inputStr, std::string inputStr2);
//void drawBoard(std::string inputStr);
//=================================


#endif // __OUTPUT_H_INCLUDED__ 

