 // field.h
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .h subor field.h

//=================================
// include guard
#ifndef __FIELD_H_INCLUDED__
#define __FIELD_H_INCLUDED__

//=================================
// forward declared dependencies
class Field;

//=================================
#include "stone.h"
#include <cstddef>

/*!--------------------------------------------------------------------------
Field
Represents one field in board. Field stores pointer to stone
--------------------------------------------------------------------------*/
class Field {
    
    public:
    Stone* actStone; /*!pointer to stone that lays on field*/
    
    //! A constructor.
    Field();
    
    // methods
    Stone* getStone();//! Function returns pointer to  stone
    void setStone(Stone *c); //! Function set field pointer 
    void putStone(Stone c); //! function create stone and store its pointer in field
};

#endif // __FIELD_H_INCLUDED__