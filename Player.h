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
  inline int shipNum(){return inventory_.size();};
  inline std::list<Ship*>* getInventory(){return &inventory_;};
  inline Grid* getGrid(){ return grid_;};
  inline bool isDead(){ return (getGrid()->getAlive()<=0);};

  int getPending(int);
  int getPlaced(int);

  bool placeShip(int, int, int);
  void giveShip(Ship*);
  void removeShip(Ship*);

private:
  int pending_[4] = {0,0,0,0};
  int placed_[4] = {0,0,0,0};
  Grid* grid_ = nullptr;
  std::list<Ship*> inventory_ = {};
};

#endif //STATKI_PLAYER_H
