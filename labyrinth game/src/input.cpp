 // input.h
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .h subor input.h
 /* input.cpp definiton*/
#include "input.h"
#include <iostream> 
#include <sstream>

//=================================
// function prototypes

void input_game_properties(int *players, int *cards, int *board){
    using namespace std;
    bool ok;
    do
    {
        stringstream  strstream;
        string line;
        getline(cin, line);
        strstream << line;
    
        ok=true;
        if ((strstream >> *players) && (strstream >> *cards) && (strstream >> *board)){
            if ((*players > 4) || (*players < 2) ) ok=false;
            if ( !((*board == 5) || (*board == 7) || (*board == 9) || (*board == 11)) ) ok=false;
            if ( !((*cards == 12) || (*cards == 24)) ) ok=false;
            if ( *cards == 24 && *board == 5) *cards=12;
        }else ok=false;

        cin.clear();
    }while(!ok);
}


std::string input_name(){
    using namespace std;
    string line;
    do {
        getline(cin, line);
    }while (line.empty());
    return line;
} 

void input_menu(char * choice){
    using namespace std;
    bool ok;
    do
    {
        ok=false;
        string line;
        getline(cin, line);

        if (line.compare(0,4,"exit") == 0){
            *choice='E';
            ok=true;
        }
        if (line.compare(0,4,"load") == 0){
            *choice='L';
            ok=true;
        }
        if (line.compare(0,4,"game") == 0){
            *choice='G';
            ok=true;
        }
        cin.clear();

    }while(!ok);
} 

void input_shift(int *row, int *col, char * extra){
	using namespace std;
	bool ok=true;
	do
	{
    	cout << "Input coorinates of stone to replace with free (row col)" << endl;
    
        stringstream  strstream;
    	string line;
    	getline(cin, line);
    	strstream << line;
    
        ok=true;
    	if (strstream >> *row){
    		if (!(strstream >> *col)) ok=false;
            *row=*row -1;
            *col=*col -1;
    	}else ok=false;

    	if (!ok){
    		if (line.compare(0,4,"exit") == 0){
    			*extra='E';
    			ok=true;
    		}
    		if (line.compare(0,4,"load") == 0){
    			*extra='L';
    			ok=true;
    		}
    	}

    }while(!ok);
}

void input_move(int *row, int *col, char * extra){
    using namespace std;
    bool ok=true;
    do
    {
        cout << "Input coorinates of field you want to move" << endl;
    
        stringstream  strstream;
        string line;
        getline(cin, line);
        strstream << line;
    
        ok=true;
        if (strstream >> *row){
            if (!(strstream >> *col)) ok=false;
            *row=*row -1;
            *col=*col -1;
        }else ok=false;

        if (!ok){
            if (line.compare(0,6,"finish") == 0){
                *extra='F';
                ok=true;
            }
            if (line.compare(0,4,"exit") == 0){
                *extra='E';
                ok=true;
            }
            if (line.compare(0,4,"load") == 0){
                *extra='L';
                ok=true;
            }
        }

    }while(!ok);
}


void input_rotate(char * extra){
    using namespace std;
    bool ok=true;
    do
    {
        cout << "Rotate or finish rotation (type: rotate / finish)" << endl;
    
        stringstream  strstream;
        string line;
        getline(cin, line);
        strstream << line;
    
        ok=true;
        if (line.compare(0,6,"rotate") == 0){
            *extra='R';
            ok=true;
        }

        if (line.compare(0,6,"finish") == 0){
            *extra='F';
            ok=true;
        }

        if (line.compare(0,4,"exit") == 0){
            *extra='E';
            ok=true;
        }
        if (line.compare(0,4,"load") == 0){
            *extra='L';
            ok=true;
        }
        if (line.compare(0,4,"save") == 0){
            *extra='S';
            ok=true;
        }
        if (line.compare(0,4,"undo") == 0){
            *extra='U';
            ok=true;
        }
    }while(!ok);
}


//void input_move(int *row, int *col, char * extra);

//=================================

