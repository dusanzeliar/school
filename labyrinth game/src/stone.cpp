 // stone.cpp
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .cpp subor stone.cpp

 /* stone.cpp definiton*/
#include "stone.h"

//! A constructor.
/*!
  constructs object Stone, requires bool parameter for direction and char for type.
  Implicit value of treasue is no treasure on stone
*/
Stone::Stone(bool left, bool right, bool up, bool down, char stoneType){
    this->left = left ;
    this->right = right ;
    this->up = up ;
    this->down = down ;
    this->stoneType = stoneType;
    this->treasureNumber= -1;
}

//! Function returns pointer to new stone
/*!
  call constuctor with char type
*/
Stone* Stone::createStone(char type)
{
    Stone *tmpStone;

    switch (type){
        case 'I':
            tmpStone = new Stone(true, true, false, false,'I');
        break;
             
        case 'L':
            tmpStone = new Stone(false, true, true, false, 'L');
        break;
                
        case 'T':
            tmpStone = new Stone(true, true, true, false,'T');
        break;
    }
            
    return tmpStone;
}

//! Function set treasure to stone
/*!
  returns true on success, false if stone allready contains treasure
*/
bool Stone::putTreasure(int number){
    if (this->treasureNumber == -1) {
        this->treasureNumber= number;
        return true;
    }
    else return false;
}

//! function gets direction and decides if this way is allowed
/*!
  returns true if direction is allowed, false when not
*/
bool Stone::canGo(char directions)
{
     if (directions == 'L' && left == true)
         return true;
         else if (directions == 'L' && left == false)
            return false;

     if (directions == 'R' && right == true)
         return true;
         else if (directions == 'R' && right == false)
            return false;

     if (directions == 'U' && up == true)
         return true;
         else if (directions == 'U' && up == false)
            return false;

     if (directions == 'D' && down == true)
         return true;
         else if (directions == 'D' && down == false)
            return false;

     return false;
}

//! changes direction of stone by 90 degrees
void Stone::turnRight()
{       
   bool tmp;
   tmp = up;
   
   up = left;
   left = down;
   down = right;
   right = tmp;
}