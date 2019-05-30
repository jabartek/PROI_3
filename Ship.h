//
// Created by Bartek on 15.05.2019.
//

#ifndef STATKI_SHIP_H
#define STATKI_SHIP_H

#include <iostream>

#include <cmath>

#include <memory>

#include <deque>

#include <string>

#include <stdexcept>

class Grid;

class Ship {
  public:

  Ship();

  virtual ~Ship();

  bool placeAtXY(Grid * , int, int, int);

  bool isValid(Grid * , int, int, int);

  void removeFromMap();

  int shotAtTile(int);

  virtual void damageTile(int);
  virtual int getTile(int);

  inline int getSize() {
    return size_;
  };

    inline int getHeadX() { return headX_;};
    inline int getHeadY() { return headY_;};
    inline int getHeading() { return heading_;};

  bool isDead();

  char renderTile(int, int param = 0);



protected:
  int heading_ = -1;
  int headX_ = -1;
  bool isPlaced_ = false;
  int headY_ = -1;
  int size_ = 0;
  int health_ = 0;
  Grid * placedOn_ = nullptr;
};

class Carrier: public Ship {
  public:
    Carrier();
    ~Carrier();
  void damageTile(int);
  int getTile(int);
  private: int hitTiles_[5];
};

class Battleship: public Ship {
  public:
    Battleship();
    ~Battleship();
  void damageTile(int);
  int getTile(int);
  private: int hitTiles_[4];
};

class Cruiser: public Ship {
  public:
    Cruiser();
    ~Cruiser();
  void damageTile(int);
  int getTile(int);
  private: int hitTiles_[3];
};

class Destroyer: public Ship {
  public:
    Destroyer();
    ~Destroyer();
  void damageTile(int);
  int getTile(int);
  private: int hitTiles_[2];
};

#endif //STATKI_SHIP_H
