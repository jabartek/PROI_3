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

class Game{
public:
  Game();
  ~Game();

  void startGame(int, int, int, int, int, int);
  void runGame(int);

  void togglePlayer(){currentPlayer = (currentPlayer+1)%2;};

  Player* getP(int);
  Player* getP1(){
    return getP(0);
  };
  Player* getP2(){
    return getP(1);
  };

  inline bool wasStarted(){return isRunning;};
  inline int currPlayer(){return currentPlayer;};

  int hasWon();
  void abortGame();




private:
  Player P_[2];
  bool isRunning = false;
  int currentPlayer = -1;
  int shipCounts[4] = {0,0,0,0};
};

#endif //STATKI_GAME_H
