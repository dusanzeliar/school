 // board.h
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .h subor board.h

//=================================
// include guard
#ifndef __BOARD_H_INCLUDED__
#define __BOARD_H_INCLUDED__

//=================================
// forward declared dependencies
class Board;

//=================================
#include "field.h"
#include <string>

/*!--------------------------------------------------------------------------
Board
Stores pointer to array of Fields, one stone and its size.
--------------------------------------------------------------------------*/
class Board 
{
    public:
    Field *gameBoard[11][11]; /*!pointer to array of Fields that creates board*/
    Stone *freeStone; /*!pointer to stone that will be played*/
    int size; /*! size of Board*/
    int no_shift_col;
    int no_shift_row;
    
    //! constructor
    Board(int n);
    //! constructor to load
    Board(std::string inputStr);
    //!destructor
    ~Board();
    
    // methods
    void createGame(int cards); //
    Field* getField(int r, int c); //!retruns pointer to field on position
    Stone* getFreeStone(); //!returns poiter to one free stone
    void shift(int row, int col, char direction);//!shifts stone to direction 
    bool try_shift(int row, int col, char * direction);//!check validity od operation,if possible, shifts stone, saves direction
    std::string saveBoard(); //!creates string containing info about board

};

#endif // __BOARD_H_INCLUDED__
