
#include "Player.h"
#include "Ship.h"

Player::Player(){
  //empty as of now
};

Player::~Player(){
  for(Ship* s : inventory_){
    delete s;
  }
}

void Player::giveShip(Ship* s){
  inventory_.push_back(s);
}

void Player::setGrid(int xSize, int ySize){
  grid_ = new Grid(xSize, ySize);
}
