#ifndef STATKI_PLAYER_H
#define STATKI_PLAYER_H


#include "Grid.h"

#include <iostream>

#include <list>

#include <stdexcept>


class Player {
public:
  Player();
  ~Player();

  void setGrid(int, int);

  inline Grid* getGrid(){ return grid_;};
  inline bool isDead(){ return (getGrid()->getAlive()<=0);};
  void giveShip(Ship*);




private:
  Grid* grid_ = nullptr;
  std::list<Ship*> inventory_ = {};
};

#endif //STATKI_PLAYER_H
