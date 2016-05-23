#include <iostream>
#include <string>
//#include "proj.h"
using namespace std;


enum directionsFree{LEFT, UP, RIGHT, DOWN, NO};


class Stone
{
    directionsFree up;
    directionsFree down;
    directionsFree right;
    directionsFree left;
    char stoneType;

    // generator
    Stone(directionsFree left, directionsFree right, directionsFree up, directionsFree down, char stoneType){
        this->left = left ;
        this->right = right ;
        this->up = up ;
        this->down = down ;
        this->stoneType = stoneType;
    }
    
    // methods
    Stone* createStone(char type);
    bool canGo(directionsFree directions);
    void turnRight();
    
};

Stone* Stone::createStone(char type)
{
    Stone *tmpStone;

    switch (type){
        case 'I':
            tmpStone = new Stone(LEFT, NO, UP, NO,'I');
        break;
             
        case 'L':
            tmpStone = new Stone(UP, RIGHT, NO, NO,'L');
        break;
                
        case 'T':
            tmpStone = new Stone(LEFT, RIGHT, UP, NO,'T');
        break;
    }
            
    return tmpStone;
}

bool Stone::canGo(directionsFree directions)
{
     if (directions == LEFT && left != NO)
         return true;
         else if (directions == LEFT && left == NO)
            return false;

     if (directions == RIGHT && right != NO)
         return true;
         else if (directions == RIGHT && right == NO)
            return false;

     if (directions == UP && up != NO)
         return true;
         else if (directions == UP && up == NO)
            return false;

     if (directions == DOWN && down != NO)
         return true;
         else if (directions == DOWN && down == NO)
            return false;

     return false;
}

void Stone::turnRight()
{       
   directionsFree tmp;
   tmp = up;
   
   up = left;
   left = down;
   down = right;
   right = tmp;
 
   if (up != NO) up = UP;
   if (down != NO) down = DOWN;
   if (left != NO) left= LEFT;
   if (right != NO) right = RIGHT;
}

