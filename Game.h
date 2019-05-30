 #ifndef STATKI_GAME_H
#define STATKI_GAME_H

#include <iostream>

#include <cmath>

#include <memory>

#include <deque>

#include <string>

#include <stdexcept>

#include "Player.h"

class Ship;

class Grid;

class Game {
public:
Game();
~Game();

void startGame(int, int, int, int, int, int);
void runGame(int);

inline void toggleRunning(){
        isRunning = !isRunning;
}

inline void setPlayer(int s){
        currentPlayer = s;
}

inline void togglePlayer(){
        currentPlayer = (currentPlayer+1)%2;
};

Player* getP(int);

inline bool wasStarted(){
        return isRunning;
};
inline int currPlayer(){
        return currentPlayer;
};

inline int getXSize(){
        return xSize_;
};
inline int getYSize(){
        return ySize_;
};


inline void setSaved(){
        saved_ = true;
};
int hasWon();
void abortGame();




private:
bool saved_ = false;
Player P_[2];
bool isRunning = false;
int currentPlayer = 0;
int shipCounts[4] = {0,0,0,0};
int xSize_ = -1;
int ySize_ = -1;
};

#endif //STATKI_GAME_H
