 // cards.h
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .h subor cards.h

//=================================
// include guard
#ifndef __CARDS_H_INCLUDED__
#define __CARDS_H_INCLUDED__

//=================================
// forward declared dependencies
class TreasureCard;
class CardPack;

//=================================

#include <vector>
#include <string>
/*!--------------------------------------------------------------------------
TreasureCard
Represents one card. Card has cas code of treasure.
--------------------------------------------------------------------------*/
class TreasureCard {
    private:
        int index_of_treasure; /** integer with unique number of treasure*/
    public:
        TreasureCard(int); //!constructor, set card number
        int CardNuber (); //!member function, returns number of treasure 
};
/*!--------------------------------------------------------------------------
CardPack
Represents instances of tresure cards.
--------------------------------------------------------------------------*/
class CardPack {
        
    public:
        int pack_size;
        //!destructor
        ~CardPack();
    	static std::vector<TreasureCard> pack; /** vector stores cards*/
        CardPack(int initSize); //! default constructor
        CardPack(std::string str); //! load state constructor
        std::string SaveCardPack(); //! member function, returns actual state
        TreasureCard popCard(); //! member function, returns top card from pack and removes it
        int size(){ return pack.size(); } //!member function, return number of cards in pack 
        void shuffle();  //!member function, shuffles cards in pack
};

#endif // __CARDS_H_INCLUDED__ 