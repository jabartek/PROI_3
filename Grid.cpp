#include "Ship.h"
#include "Grid.h"

Grid::Grid(int xSize, int ySize) : xSize_(xSize), ySize_(ySize) {
        allocation();
}

Grid::Grid() : xSize_(1), ySize_(1) {
        allocation();
}

Grid::~Grid() {

        for (int i = 0; i < ySize_; i++) {
                for (int j = 0; j < xSize_; j++) {
                        delete ships_[i][j];
                        ships_[i][j] = nullptr;
                }
        }
        for (int i = 0; i < ySize_; i++) {
                delete[] ships_[i];
                delete[] neighbors_[i];
                delete[] tileNum_[i];
                delete[] revealed_[i];
        }

        delete[] ships_;
        delete[] neighbors_;
        delete[] tileNum_;
        delete[] revealed_;
}




void Grid::addAtXY(int xPos, int yPos) {
        if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_)
                neighbors_[yPos][xPos]++;
}

void Grid::subAtXY(int xPos, int yPos) {
        if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_)
                neighbors_[yPos][xPos]--;
}

void Grid::setShip(Ship* s, int tile, int xPos, int yPos) {
        if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_) {
                ships_[yPos][xPos] = s;
                tileNum_[yPos][xPos] = tile;
        }
}


int Grid::getNeighbors(int xPos, int yPos) {
        if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_) {
                return neighbors_[yPos][xPos];
        } else return -1;
}

bool Grid::isRevealed(int xPos, int yPos) {
        if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_) {
                return revealed_[yPos][xPos];
        } else return -1;
}

int Grid::getTileNum(int xPos, int yPos) {
        if(yPos < ySize_ && xPos < xSize_ && yPos >= 0 && xPos>=0)
                return tileNum_[yPos][xPos];
        else
                return 0;
}

void Grid::removeShip(int xPos, int yPos) {
        if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_)
                ships_[yPos][xPos] = nullptr;
}

Ship* Grid::getShip(int xPos, int yPos) {
        if (xPos >= 0 && xPos < xSize_ && yPos >= 0 && yPos < ySize_)
                return ships_[yPos][xPos];
        else
                return nullptr;
}

char Grid::renderXY(int xPos, int yPos, int param){
        bool isThere = false;
        if(xPos < xSize_ && yPos < ySize_ && xPos >= 0 && yPos >= 0) {
                isThere = (ships_[yPos][xPos] != nullptr);
                switch (param) {
                case 1:
                        if(revealed_[yPos][xPos]) {
                                if (isThere) {
                                        return ships_[yPos][xPos]->renderTile(tileNum_[yPos][xPos], param);
                                }
                                else return '=';
                        }
                        else
                                return '?';
                        break;

                default:
                        if (isThere) {
                                return ships_[yPos][xPos]->renderTile(tileNum_[yPos][xPos], param);
                        }
                        else if(revealed_[yPos][xPos])
                                return '#';
                        return '=';
                        break;
                }
        }
        return '?';
}



int Grid::shotAtXY(int xPos, int yPos) {
        int res = 0;
        bool sunken = false;
        if(getShip(xPos, yPos) != nullptr) {
                res = getShip(xPos, yPos)->shotAtTile(getTileNum(xPos,yPos));
                sunken = getShip(xPos, yPos)->isDead();
        }
        if(yPos<ySize_ && xPos<xSize_ && yPos>=0 && xPos>=0)
                revealed_[yPos][xPos] = true;
        if(sunken && res == 1) {
                delAlive();
                return -1;
        }
        else return (int) (res>0);
}


void Grid::allocation() {
        ships_ = new Ship* *[ySize_];
        neighbors_ = new int *[ySize_];
        tileNum_ = new int *[ySize_];
        revealed_ = new bool *[ySize_];
        for (int i = 0; i < ySize_; i++) {
                ships_[i] = new Ship* [xSize_];
                neighbors_[i] = new int [xSize_];
                tileNum_[i] = new int [xSize_];
                revealed_[i] = new bool [xSize_];
        }
        for (int i = 0; i < ySize_; i++) {
                for (int j = 0; j < xSize_; j++) {
                        ships_[i][j] = nullptr;
                        neighbors_[i][j] = 0;
                        tileNum_[i][j] = 0;
                        revealed_[i][j] = false;
                }
        }
}
