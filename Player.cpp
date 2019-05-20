
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

void Player::giveShip(Ship *s){
  int type = s->getSize();
  pending_[type-2]++;
  inventory_.push_back(s);
}

void Player::setGrid(int xSize, int ySize){
  grid_ = new Grid(xSize, ySize);
}

bool Player::placeShip(int xPos, int yPos, int heading){
  Ship *s = nullptr;
  if(!inventory_.empty()){
    s = inventory_.front();
    if(s->placeAtXY(grid_, xPos, yPos, heading)){
      pending_[s->getSize()-2]--;
      placed_[s->getSize()-2]++;
      inventory_.pop_front();
      return true;
    }
  }
  return false;
}

void Player::removeShip(Ship *s){
  s->removeFromMap();
  inventory_.push_back(s);
  pending_[s->getSize()-2]++;
  placed_[s->getSize()-2]--;
}

void Player::skipInventory(){
  if(!inventory_.empty()){
    inventory_.push_back(inventory_.front());
    inventory_.pop_front();
  }
}


int Player::getPending(int s){return pending_[s];};
int Player::getPlaced(int s){return placed_[s];};
