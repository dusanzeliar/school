// save.cpp
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .cpp subor save.cpp

//dependencies
#include <iostream>
#include <fstream>
#include "save.h"

 /* save.cpp definiton*/
bool save_game(std::string saved_players, std::string saved_cards, std::string saved_board, std::string filename){
    using namespace std;

    string savename=filename + "_players";

    ofstream savefile (savename);
    if (savefile.is_open()){
        savefile << saved_players;
        savefile.close();
    }else return false;

    savename=filename + "_board";
    savefile.open(savename);
    if (savefile.is_open()){
        savefile << saved_board;
        savefile.close();
    }else return false;

    savename=filename + "_cards";
    savefile.open(savename);
    if (savefile.is_open()){
        savefile << saved_cards;
        savefile.close();
    }else return false;

    return true;
    

}
//! A constructor.
