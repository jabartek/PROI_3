#include "Game.h"
#include "Ship.h"
#include "Player.h"
#include "Grid.h"

Game::Game(){

}

Game::~Game(){
  //empty
}

void Game::startGame(int xSize, int ySize, int Carriers, int Battleships, int Cruisers, int Destroyers){
  for(int i =0; i<2; i++){
    P_[i].setGrid(xSize, ySize);
  }
  for(int i=0; i<Carriers; i++){
    for(int j=0; j<2; j++){
      Ship *s = new Carrier;
      P_[j].giveShip(s);
    }
  }
  for(int i=0; i<Battleships; i++){
    for(int j=0; j<2; j++){
      Ship *s = new Battleship;
      P_[j].giveShip(s);
    }
  }
  for(int i=0; i<Cruisers; i++){
    for(int j=0; j<2; j++){
      Ship *s = new Cruiser;
      P_[j].giveShip(s);
    }
  }
  for(int i=0; i<Destroyers; i++){
    for(int j=0; j<2; j++){
      Ship *s = new Destroyer;
      P_[j].giveShip(s);
    }
  }
}

Player* Game::getP(int n){
  if (n==0){
    return &P_[0];
  }
  else
  return &P_[1];
};
