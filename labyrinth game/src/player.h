 // player.h
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .h subor player.h

//=================================
// include guard
#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include <string>
//=================================
// forward declared dependencies
class Player;
class ActivePlayers;

//=================================
/*!--------------------------------------------------------------------------
Player
Represents one player. Stores hes ID number, points, position, actual card number.
Static value is number of players in game.
--------------------------------------------------------------------------*/
class Player
{
    public:
    
    int points; /*!number of actual points*/
    int card; /*! Cards and treasure number player is looking for*/
    int id; /*! players id number, starts with 0*/
    int row; /*!actual cooirdinates*/
    int col; /*!actual cooirdinates*/


    //! A constructor.
    Player(int start_row, int start_col, int id_number);
    
    // methods
    void move(char direction); //! Function changes actual coordinates
    int actual_card(); //!returns number of actual card
    void set_card (int value); //!set cards value
    void card_found(); //!increase points gained by 1, set actual card to -1   
};

/*!--------------------------------------------------------------------------
ActivePlayers
Represents all players in current session.
--------------------------------------------------------------------------*/
class ActivePlayers
{
    public:
    
    Player *game_players[4]; /*!pointer to array of Players currently playing*/
    static int number_of_players; /*!static variable, stores number of players in actual game*/
    static int on_turn;


    //! A constructor.
    ActivePlayers(int number, int board_size);
    ActivePlayers(std::string inputStr);

    //! destructor
    ~ActivePlayers();
    
    // methods
    void end_turn();
    bool is_winner(int cards); //! Function check if any player has won
    std::string savePlayers();
};

#endif // __PLAYER_H_INCLUDED__ 
