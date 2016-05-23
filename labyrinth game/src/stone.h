 // stone.h
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .h subor stone.h

//=================================
// include guard
#ifndef __STONE_H_INCLUDED__
#define __STONE_H_INCLUDED__

//=================================
// forward declared dependencies
class Stone;

//=================================

/*!--------------------------------------------------------------------------
Stone
Represents one stone. Stone has type, number of treasure and directions of
allowed movemet.
--------------------------------------------------------------------------*/
class Stone
{
    public:

    int treasureNumber; /*!number of treasure, dafault -1 means no treasure on stone*/
    bool up; /*!bool value, true if path is free in this direction*/
    bool down; /*!bool value, true if path is free in this direction*/
    bool right; /*!bool value, true if path is free in this direction*/
    bool left; /*!bool value, true if path is free in this direction*/
    char stoneType; /*!char value, represents shape of stone I L T*/

    //! A constructor.
    Stone(bool left, bool right, bool up, bool down, char stoneType);
    
    // methods
    static Stone* createStone(char type); //! Function returns pointer to new stone
    bool putTreasure(int number); //! Function set treasure to stone
    int getTreasure() {return this->treasureNumber;} //! returns number of treasure on stone
    void removeTreasure() {this->treasureNumber = -1; return;} //! set treasureNumber to -1
    bool canGo(char directions); //! function gets direction and decides if this way is allowed
    void turnRight(); //! changes direction of stone by 90 degrees
    
};

#endif // __STONE_H_INCLUDED__ 