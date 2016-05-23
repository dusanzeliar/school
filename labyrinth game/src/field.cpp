// field.cpp
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .cpp subor field.cpp

 /* field.cpp definiton*/
#include "field.h"

//! A constructor.
Field::Field(){
    this->actStone = NULL;
}

//! Function set field pointer 
void Field::setStone( Stone *c){
    this->actStone=c;
}

//! Function returns pointer to  stone
Stone* Field::getStone(){
    return this->actStone;
}

//! function create stone and store its pointer in field
void Field::putStone(Stone c)
{
    if (actStone == NULL)
        actStone = new Stone(c.left,c.right,c.up,c.down,c.stoneType);
    else
    {
        delete actStone;
        actStone = new Stone(c.left,c.right,c.up,c.down,c.stoneType);
    }
}