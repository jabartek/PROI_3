
#include "Player.h"
#include "Ship.h"

#include <fstream> //DEBUG


Player::Player(){
  //empty as of now
};

Player::~Player(){
  std::string aa = "debug"; //DEBUG
  std::ofstream outFile;
  outFile.open(aa, std::ofstream::out | std::ofstream::app);
    outFile << "P";
    outFile.close();

  for(Ship* s : inventory_){
    delete s;
  }
  delete grid_;
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

void Player::addPlaced(int size){
  if(size > 1 && size <6){
    placed_[size-2]++;
  }
}

int Player::shotAtGridXY(int xPos, int yPos){
  int result = 0;
  result = grid_->shotAtXY(xPos, yPos);
  if(result == -1){
    sunken_[grid_->getShip(xPos,yPos)->getSize()-2]++;
  }
  return result;
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
int Player::getSunken(int s){return sunken_[s];};
