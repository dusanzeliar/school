// board.cpp
 // Riesenie ICP-PROJEKT,  6.5.2014
 // Autor: Dusan Zeliar,xzelia00, FIT
 //        Filip Mutnansky, xmutna00, FIT
 // Přeloženo: g++ 4.8.2
 // .cpp subor board.cpp

 /* board.cpp definiton*/
#include "board.h"
#include <time.h> 
#include <cstdlib>  
#include <string>
#include <sstream>

//! constructor
Board::Board(int n){
    for (int i = 0; i< n; i++)
        for (int j = 0; j< n; j++)
            gameBoard[i][j] = new Field();
    this->size = n;
    this->no_shift_col=-1;
    this->no_shift_row=-1;
}

//! destructor
Board::~Board(){
    delete[] this->freeStone;
    for (int i = 0; i< this->size; i++)
        for (int j = 0; j< this->size; j++)
            {
                delete[] (gameBoard[i][j]->getStone());
                delete[] gameBoard[i][j];
            }
}

//!retruns pointer to field on position
Field* Board::getField(int r, int c)
{
    return gameBoard[r][c];
}

//!returns poiter to one free stone
Stone* Board::getFreeStone()
{
    return freeStone;
}

//! shifts stone to direction 
/*!
  row and col locate index to board, directions are U D L R
*/
void Board::shift(int row, int col, char direction){
	Stone *tmpStone;

	if (direction == 'U'){
		tmpStone=freeStone;
		this->freeStone=gameBoard[0][col]->getStone();
		for (int i = 0; i<size; i++){
			if (i == size -1){
				gameBoard[i][col]->setStone(tmpStone);
			}
			else{
				gameBoard[i][col]->setStone( gameBoard[i+1][col]->getStone() );
			}
		}
	}

	if (direction == 'D'){
		tmpStone=gameBoard[size-1][col]->getStone();
		for (int i = size-1; i>=0; i--){
			if (i == 0){
				gameBoard[i][col]->setStone(freeStone);
			}
			else{
				gameBoard[i][col]->setStone( gameBoard[i-1][col]->getStone() );
			}
		}
		freeStone=tmpStone;
	}

	if (direction == 'L'){
		tmpStone=freeStone;
		this->freeStone=gameBoard[row][0]->getStone();
		for (int i = 0; i<size; i++){
			if (i == size -1){
				gameBoard[row][i]->setStone(tmpStone);
			}
			else{
				gameBoard[row][i]->setStone( gameBoard[row][i+1]->getStone() );
			}
		}
	}

	if (direction == 'R'){
		tmpStone=gameBoard[row][size-1]->getStone();
		for (int i = size-1; i>=0; i--){
			if (i == 0){
				gameBoard[row][i]->setStone(freeStone);
			}
			else{
				gameBoard[row][i]->setStone( gameBoard[row][i-1]->getStone() );
			}
		}
		freeStone=tmpStone;
	}


} 

//!check validity od operation,if possible, shifts stone to direction 
/*!
  row and col locate index to board, returns true on success or false
*/
bool Board::try_shift(int row, int col, char * direction){
    if (this->no_shift_col == col && this->no_shift_row == row) return false;
	if (col==0 or col==this->size-1){
		if (row % 2 == 1){
			if (col==0) {
				this->shift(row,col,'R');
				*direction='R';
                this->no_shift_col=size-1;
                this->no_shift_row=row;
			}
			else{
				this->shift(row,col,'L');
				*direction='L';
                this->no_shift_col=0;
                this->no_shift_row=row;
			}
		    return true;
		}
	    else return false;
	}
	else if (row==0 or row==this->size-1){
		if (col % 2 == 1){
			if (row==0){
				this->shift(row,col,'D');
				*direction='D';
                this->no_shift_col=col;
                this->no_shift_row=size-1;
			}
			else{
			    this->shift(row,col,'U');
			    *direction='U';
                this->no_shift_col=col;
                this->no_shift_row=0;
			}
		    return true;
		}
	    else return false;
	} else return false;
}



//! Function creates Board
/*!
  fills all fields with stone
*/
void Board::createGame(int cards)
{
    srand (time(NULL));
    
    //TOP LEFT
    Stone * tmpStone =Stone::createStone('L');
    tmpStone->turnRight();
    gameBoard[0][0]->putStone(*tmpStone);

    //TOP RIGHT
    tmpStone->turnRight();
    gameBoard[0][size-1]->putStone(*tmpStone);
    
    //DOWN RIGHT
    tmpStone->turnRight();
    gameBoard[size-1][size-1]->putStone(*tmpStone);

    //DOWN LEFT
    tmpStone->turnRight();
    gameBoard[size-1][0]->putStone(*tmpStone);

    freeStone=tmpStone;

    for (int i = 0; i<size; i++)
        for (int j = 0; j<size; j++)
        {
            if (gameBoard[i][j]->actStone == NULL)
            {
                if ( ((i+1) % 2) && ((j+1) % 2))
                {
                    if (i == 0)
                    {
                        Stone tmpStone (true,true,false,true,'T');
                        gameBoard[i][j]->putStone(tmpStone);
                    } else if (j == 0)
                    {
                        Stone tmpStone (false,true,true,true,'T');
                        gameBoard[i][j]->putStone(tmpStone);
                    } else if (i == size-1)
                    {
                        Stone tmpStone (true,true,true,false,'T');
                        gameBoard[i][j]->putStone(tmpStone);
                    } else if (j == size - 1)
                    {
                        Stone tmpStone (true,false,true,true,'T');
                        gameBoard[i][j]->putStone(tmpStone);
                    } else
                    {                    
                        Stone tmpStone (true,false,true,true,'T');
                        gameBoard[i][j]->putStone(tmpStone);
                    }
                }
                else
                {
                    int num = rand() % 3;
                    int num2 = rand() % 3;

                    
                    if (num == 0)
                    {
                        Stone tmpStone (true,true,false,false,'I');
                        gameBoard[i][j]->putStone(tmpStone);
                    }
                    
                    if (num == 1)
                    {
                        Stone tmpStone2 (false,true,true,false,'L');
                        gameBoard[i][j]->putStone(tmpStone2);
                    }

                    if (num == 2)
                    {
                        Stone tmpStone3 (true,true,false,false,'I');
                        gameBoard[i][j]->putStone(tmpStone3);
                    }

                    for (int k = 0; k < num2; k++)                    
                    {
                        gameBoard[i][j]->actStone->turnRight();
                    }
                }
            }
    }
    //put treasure
    for (int i=0; i< cards; i++){
    	bool plant_failed = true;
    	do{
    		int rand_col= rand() % this->size;
    		int rand_row= rand() % this->size;
    		Stone *tmpStone=gameBoard[rand_row][rand_col]->getStone();
    		if (tmpStone->getTreasure() == -1){
    			tmpStone->putTreasure(i);
    			plant_failed=false;
    		}

    	}while(plant_failed);
    }
}


//! Function saves Board
/*!
  creates string containing info about board
*/
std::string Board::saveBoard(){
    std::string saveString;
	saveString += std::to_string(size) + " ";
    for (int i=0; i<size; i++)
	    for (int j=0; j<size; j++)
        {
            saveString += std::string(1, gameBoard[i][j]->actStone->stoneType) + " ";
	        saveString += std::to_string(gameBoard[i][j]->actStone->left) + " ";
            saveString += std::to_string(gameBoard[i][j]->actStone->right) + " ";
            saveString += std::to_string(gameBoard[i][j]->actStone->up) + " ";
            saveString += std::to_string(gameBoard[i][j]->actStone->down) + " ";
            saveString += std::to_string(gameBoard[i][j]->actStone->treasureNumber) + " ";
	    }
    
        saveString += std::string(1, freeStone->stoneType) + " ";
	    saveString += std::to_string(freeStone->left) + " ";
        saveString += std::to_string(freeStone->right) + " ";
        saveString += std::to_string(freeStone->up) + " ";
        saveString += std::to_string(freeStone->down) + " ";
        saveString += std::to_string(freeStone->treasureNumber) + " ";
    
	return saveString;
}


//! Function saves Board
/*!
  creates string containing info about board
*/
Board::Board(std::string inputStr)
{	
    std::stringstream  strStream;
    strStream << inputStr;
    int valueInt,n,leftTmp,rightTmp,upTmp,downTmp, treasureTmp;
    char valueChar,stoneTypeTmp;

    strStream >> n;
    size = n;

    int rowCount = 0, colCount = 0;
    
    for (int i = 0; i < n*n; i++)
    {
        strStream >> valueChar;
        
        gameBoard[rowCount][colCount] = new Field();        
        stoneTypeTmp = valueChar;

        for (int j = 0; j < 5; j++)
        {
            strStream >> valueInt;
            if (j==0) leftTmp = valueInt;
            if (j==1) rightTmp = valueInt;
            if (j==2) upTmp = valueInt;
            if (j==3) downTmp = valueInt;
            if (j==4) treasureTmp = valueInt;
        }

        Stone tmpStone(leftTmp,rightTmp,upTmp,downTmp,stoneTypeTmp);
        gameBoard[rowCount][colCount]->putStone(tmpStone);
        gameBoard[rowCount][colCount]->actStone->putTreasure(treasureTmp);

        colCount++;
        if ((i+1) % n == 0)
        {
            rowCount++;
            colCount = 0;
        }

    }

    strStream >> valueChar;
    stoneTypeTmp = valueChar;
    strStream >> valueInt;
    leftTmp = valueInt;
    strStream >> valueInt;
    rightTmp = valueInt;
    strStream >> valueInt;
    upTmp = valueInt;
    strStream >> valueInt;
    downTmp = valueInt;

    freeStone = new Stone(leftTmp,rightTmp,upTmp,downTmp,stoneTypeTmp);
}
