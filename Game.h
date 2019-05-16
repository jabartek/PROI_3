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

  Player* getP1(){return &P1_;};
  Player* getP2(){return &P2_;};

  void abortGame();

private:
  bool isRunning = false;
  int currentPlayer = 0;
  int shipCounts[4] = {0,0,0,0};
  Player P1_;
  Player P2_;
};

#endif //STATKI_GAME_H
