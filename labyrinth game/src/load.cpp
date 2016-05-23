// load.cpp
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .cpp subor load.cpp

//dependencies
#include <iostream>
#include <fstream>
#include <string>
#include "load.h"

 /* save.cpp definiton*/
bool load_game(std::string * saved_players, std::string * saved_cards, std::string * saved_board,  std::string filename){
    using namespace std;
    string line;

    string loadname=filename + "_players";

    ifstream loadfile (loadname);
    if (loadfile.is_open()){
        while ( getline (loadfile,line) )
        {
            *saved_players+=line + '\n';
        }
        loadfile.close();
    }else return false;

    loadname=filename + "_board";
    loadfile.open(loadname);
    if (loadfile.is_open()){
        while ( getline (loadfile,line) )
        {
            *saved_board+=line + '\n';
        }
        loadfile.close();
    }else return false;

    loadname=filename + "_cards";
    loadfile.open(loadname);
    if (loadfile.is_open()){
        while ( getline (loadfile,line) )
        {
            *saved_cards+=line + '\n';
        }
        loadfile.close();
    }else return false;

    return true;
    

}
//! A constructor.
