#include "Game.h"
#include "Ship.h"
#include "Player.h"
#include "Grid.h"

Game::Game(){
  //empty
}

Game::~Game(){
  //empty
}

void Game::startGame(int xSize, int ySize, int Carriers, int Battleships, int Cruisers, int Destroyers){
  P1_.setGrid(xSize, ySize);
  P2_.setGrid(xSize, ySize);
  for(int i=0; i<Carriers; i++){
    P1_.giveShip(new Carrier);
    P2_.giveShip(new Carrier);
  }
  for(int i=0; i<Battleships; i++){
    P1_.giveShip(new Battleship);
    P2_.giveShip(new Battleship);
  }
  for(int i=0; i<Cruisers; i++){
    P1_.giveShip(new Cruiser);
    P2_.giveShip(new Cruiser);
  }
  for(int i=0; i<Destroyers; i++){
    P1_.giveShip(new Destroyer);
    P2_.giveShip(new Destroyer);
  }
}
