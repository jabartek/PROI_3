#include "Game.h"
#include "Ship.h"
#include "Player.h"
#include "Grid.h"

Game::Game(){

}

Game::~Game(){

}

void Game::startGame(int xSize, int ySize, int Carriers, int Battleships, int Cruisers, int Destroyers){
        xSize_ = xSize;
        ySize_ = ySize;
        shipCounts[3] = Carriers;
        shipCounts[2] = Battleships;
        shipCounts[1] = Cruisers;
        shipCounts[0] = Destroyers;
        for(int i =0; i<2; i++) {
                P_[i].setGrid(xSize, ySize);
        }
        for(int i=0; i<Carriers; i++) {
                for(int j=0; j<2; j++) {
                        Ship *s = new Carrier;
                        P_[j].giveShip(s);
                }
        }
        for(int i=0; i<Battleships; i++) {
                for(int j=0; j<2; j++) {
                        Ship *s = new Battleship;
                        P_[j].giveShip(s);
                }
        }
        for(int i=0; i<Cruisers; i++) {
                for(int j=0; j<2; j++) {
                        Ship *s = new Cruiser;
                        P_[j].giveShip(s);
                }
        }
        for(int i=0; i<Destroyers; i++) {
                for(int j=0; j<2; j++) {
                        Ship *s = new Destroyer;
                        P_[j].giveShip(s);
                }
        }
}

void Game::runGame(int startingPlayer){
        isRunning = true;
        currentPlayer = startingPlayer;
}

Player* Game::getP(int n){
        if (n==0) {
                return &P_[0];
        }
        else
                return &P_[1];
};

int Game::hasWon(){
        int result = -1;
        if(saved_)
                result = 0;
        else if(getP(0)->isDead())
                result = 2;
        else if(getP(1)->isDead())
                result = 1;
        return result;
}
