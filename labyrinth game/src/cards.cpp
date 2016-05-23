 // cards.cpp
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .cpp subor cards.cpp

 /* cards.cpp definiton*/
#include "cards.h"
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <sstream>

/*!--------------------------------------------------------------------------
TreasureCard
Represents one card. Card has cas code of treasure.
--------------------------------------------------------------------------*/

//constructor, set card number
TreasureCard::TreasureCard(int number){
    index_of_treasure=number;	
}

int TreasureCard::CardNuber(){
	int x = this->index_of_treasure;
	return x;
}

//! random generator function:
int myrandom (int i) { return std::rand()%i;}

/*!--------------------------------------------------------------------------
CardPack
Represents instances of tresure cards.
--------------------------------------------------------------------------*/
std::vector<TreasureCard> CardPack::pack;

//Default
CardPack::CardPack(int initSize){
	pack_size=initSize;
	for (int i=initSize -1;i>=0;i--)
	{
        TreasureCard card(i);
		CardPack::pack.push_back(card);
	}
}

//!destructor
CardPack::~CardPack(){
    CardPack::pack.clear();	
}

//Save cards to string
std::string CardPack::SaveCardPack(){
	std::string save;
	std::vector<TreasureCard>   Data=CardPack::pack;
	char numstr[21];
	int size=CardPack::size();
	save += std::to_string(pack_size) + " ";
	for (int i=size ;i>0;i--)
	{
        TreasureCard karta=Data.back();
	    Data.pop_back();
	    save += std::to_string(karta.CardNuber()) + " ";
	}
	return save;
}

//Loading from string
CardPack::CardPack(std::string str){
	CardPack::pack.clear();
    std::vector<int>   Data;
    std::stringstream  strstream;
    strstream << str;

    int value;
    int initSize = -1;
    while(strstream >> value){
    	if (initSize == -1) initSize=value;
    	else Data.push_back(value);
    }
    pack_size=initSize;
     
    initSize= Data.size();
	for (int i=initSize -1;i>=0;i--)
	{
		value=Data.back();
		Data.pop_back();
        TreasureCard card(value);
		CardPack::pack.push_back(card);
	}
}

TreasureCard CardPack::popCard(){
	TreasureCard karta=CardPack::pack.back();
	CardPack::pack.pop_back();
	return karta;
}

void CardPack::shuffle(){
	srand ( unsigned ( std::time(0) ) );
	std::random_shuffle ( CardPack::pack.begin(), CardPack::pack.end(), myrandom);
	return;
}

 