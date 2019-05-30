#include "Ship.h"

#include "Grid.h"

void Ship::removeFromMap() {
        if (!isPlaced_)
                return;
        switch (heading_) {
        default:
                for (int i = -1; i <= size_; i++) {
                        for (int j = -1; j <= 1; j++) {
                                placedOn_->subAtXY(headX_ + i, headY_ + j);
                                if (placedOn_->getShip(headX_ + i, headY_ + j) != nullptr) {
                                        placedOn_->removeShip(headX_ + i, headY_ + j);
                                }
                        }
                }
                break;
        case 1:
                for (int i = -1; i <= size_; i++) {
                        for (int j = -1; j <= 1; j++) {
                                placedOn_->subAtXY(headX_ + j, headY_ - i);
                                if (placedOn_->getShip(headX_ + j, headY_ - i) != nullptr) {
                                        placedOn_->removeShip(headX_ + j, headY_ - i);
                                }
                        }
                }
                break;
        case 2:
                for (int i = -1; i <= size_; i++) {
                        for (int j = -1; j <= 1; j++) {
                                placedOn_->subAtXY(headX_ - i, headY_ + j);
                                if (placedOn_->getShip(headX_ - i, headY_ + j) != nullptr) {
                                        placedOn_->removeShip(headX_ - i, headY_ + j);
                                }
                        }
                }
                break;
        case 3:
                for (int i = -1; i <= size_; i++) {
                        for (int j = -1; j <= 1; j++) {
                                placedOn_->subAtXY(headX_ + j, headY_ + i);
                                if (placedOn_->getShip(headX_ + j, headY_ + i) != nullptr) {
                                        placedOn_->removeShip(headX_ + j, headY_ + i);
                                }
                        }
                }
                break;
        }
        headX_ = -1;
        headY_ = -1;
        heading_ = -1;
        isPlaced_ = false;
        placedOn_->delAlive();
        placedOn_ = nullptr;
}

bool Ship::placeAtXY(Grid * grid, int xPos, int yPos, int heading) {
        if (isPlaced_) removeFromMap();
        bool ifValid = false;
        if (grid->getNeighbors(xPos, yPos) != 0)
                return false;
        switch (heading) {
        default:
                for (int i = 0; i < size_; i++) {
                        if (grid->getNeighbors(xPos + i, yPos) != 0) {
                                ifValid = false;
                                break;
                        } else ifValid = true;
                }
                if (ifValid) {
                        for (int i = -1; i <= size_; i++) {
                                for (int j = -1; j <= 1; j++) {
                                        grid->addAtXY(xPos + i, yPos + j);
                                }
                        }
                        for (int i = 0; i < size_; i++) {
                                grid->setShip(this, i, xPos + i, yPos);
                        }
                }
                break;
        case 1:
                for (int i = 0; i < size_; i++) {
                        if (grid->getNeighbors(xPos, yPos - i) != 0) {
                                ifValid = false;
                                break;
                        } else ifValid = true;
                }
                if (ifValid) {
                        for (int i = -1; i <= size_; i++) {
                                for (int j = -1; j <= 1; j++) {
                                        grid->addAtXY(xPos + j, yPos - i);
                                }
                        }
                        for (int i = 0; i < size_; i++) {
                                grid->setShip(this, i, xPos, yPos - i);
                        }
                }
                break;
        case 2:
                for (int i = 0; i < size_; i++) {
                        if (grid->getNeighbors(xPos - i, yPos) != 0) {
                                ifValid = false;
                                break;
                        } else ifValid = true;
                }
                if (ifValid) {
                        for (int i = -1; i <= size_; i++) {
                                for (int j = -1; j <= 1; j++) {
                                        grid->addAtXY(xPos - i, yPos + j);
                                }
                        }
                        for (int i = 0; i < size_; i++) {
                                grid->setShip(this, i, xPos - i, yPos);
                        }
                }
                break;
        case 3:
                for (int i = 0; i < size_; i++) {
                        if (grid->getNeighbors(xPos, yPos + i) != 0) {
                                ifValid = false;
                                break;
                        } else ifValid = true;
                }
                if (ifValid) {
                        for (int i = -1; i <= size_; i++) {
                                for (int j = -1; j <= 1; j++) {
                                        grid->addAtXY(xPos + j, yPos + i);
                                }
                        }
                        for (int i = 0; i < size_; i++) {
                                grid->setShip(this, i, xPos, yPos + i);
                        }
                }
                break;
        }
        if (ifValid) {

                headX_ = xPos;
                headY_ = yPos;
                heading_ = heading;
                isPlaced_ = true;
                placedOn_ = grid;
                grid->addAlive();
        }
        return ifValid;
}

bool Ship::isValid(Grid * grid, int xPos, int yPos, int heading) {
        bool ifValid = false;
        if (grid->getNeighbors(xPos, yPos) != 0)
                return false;
        switch (heading) {
        default:
                for (int i = 0; i < size_; i++) {
                        if (grid->getNeighbors(xPos + i, yPos) != 0) {
                                ifValid = false;
                                break;
                        } else ifValid = true;
                }
                break;
        case 1:
                for (int i = 0; i < size_; i++) {
                        if (grid->getNeighbors(xPos, yPos - i) != 0) {
                                ifValid = false;
                                break;
                        } else ifValid = true;
                }
                break;
        case 2:
                for (int i = 0; i < size_; i++) {
                        if (grid->getNeighbors(xPos - i, yPos) != 0) {
                                ifValid = false;
                                break;
                        } else ifValid = true;
                }
                break;
        case 3:
                for (int i = 0; i < size_; i++) {
                        if (grid->getNeighbors(xPos, yPos + i) != 0) {
                                ifValid = false;
                                break;
                        } else ifValid = true;
                }
                break;
        }
        return ifValid;
}


int Ship::shotAtTile(int shotTile) {
        if (shotTile >= 0 && shotTile < size_) {
                if (getTile(shotTile) == 0) {
                        health_--;
                }
                damageTile(shotTile);
                return getTile(shotTile);
        }
        return 0;
}

char Ship::renderTile(int tileToRender, int param) {
        switch (param) {
        default:
                if (tileToRender >= 0 && tileToRender < size_) {
                        if (getTile(tileToRender) == 0) {
                                return 'O';
                        }
                        return 'X';
                }
                return '=';
        case 1:
                if (tileToRender >= 0 && tileToRender < size_) {
                        if (getTile(tileToRender) != 0) {
                                return 'X';
                        }
                }
                return '=';
        }
}

bool Ship::isDead() {
        return (health_ <= 0);
}

Ship::Ship() {
        //empty
}

Ship::~Ship() {
        removeFromMap();
}

void Ship::damageTile(int s) {
        std::cout << "Wtf";
}

int Ship::getTile(int s) {
        return 0;
}

Carrier::Carrier() {
        size_ = 5;
        health_ = 5;
        for (int i = 0; i < 5; i++) {
                hitTiles_[i] = 0;
        }
}

Battleship::Battleship() {
        size_ = 4;
        health_ = 4;
        for (int i = 0; i < 4; i++) {
                hitTiles_[i] = 0;
        }
}

Cruiser::Cruiser() {
        size_ = 3;
        health_ = 3;
        for (int i = 0; i < 3; i++) {
                hitTiles_[i] = 0;
        }
}

Destroyer::Destroyer() {
        size_ = 2;
        health_ = 2;
        for (int i = 0; i < 2; i++) {
                hitTiles_[i] = 0;
        }
}

int Carrier::getTile(int tile) {
        if (tile >= 0 && tile < 5)
                return hitTiles_[tile];
        else
                return 0;
}

int Battleship::getTile(int tile) {
        if (tile >= 0 && tile < 4)
                return hitTiles_[tile];
        else
                return 0;
}

int Cruiser::getTile(int tile) {
        if (tile >= 0 && tile < 3)
                return hitTiles_[tile];
        else
                return 0;
}

int Destroyer::getTile(int tile) {
        if (tile >= 0 && tile < 2)
                return hitTiles_[tile];
        else
                return 0;
}

void Carrier::damageTile(int tile) {
        if (tile >= 0 && tile < 5)
                hitTiles_[tile]++;
}

void Battleship::damageTile(int tile) {
        if (tile >= 0 && tile < 4)
                hitTiles_[tile]++;
}

void Cruiser::damageTile(int tile) {
        if (tile >= 0 && tile < 3)
                hitTiles_[tile]++;
}

void Destroyer::damageTile(int tile) {
        if (tile >= 0 && tile < 2)
                hitTiles_[tile]++;
}


Carrier::~Carrier() {
  removeFromMap();
}

Battleship::~Battleship() {
  removeFromMap();
}

Cruiser::~Cruiser() {
  removeFromMap();
}

Destroyer::~Destroyer() {
  removeFromMap();
}
