//
// Created by Bartek on 15.05.2019.
//

#ifndef STATKI_GRID_H
#define STATKI_GRID_H

#include <iostream>

#include <cmath>

#include <memory>

#include <deque>

#include <string>

#include <stdexcept>

class Ship;

class Grid {
public:
Grid(int, int);

Grid();

~Grid();

int getNeighbors(int, int);

bool isRevealed(int,int);

Ship * getShip(int, int);

void setShip(Ship *, int, int, int);

void removeShip(int, int);

inline int addAlive() {
        return ++alive_;
};

inline int delAlive() {
        return --alive_;
};

inline int getAlive() {
        return alive_;
};

char renderXY(int, int, int param = 0);

void addAtXY(int, int);

void subAtXY(int, int);

inline int getXSize() {
        return xSize_;
};

inline int getYSize() {
        return ySize_;
};

int shotAtXY(int, int);

int getTileNum(int, int);

void printGrid();
void printGrid(int);

private:
void allocation();
int ownerId_;
int xSize_;
int ySize_;

int alive_;

Ship * ** ships_;
int ** neighbors_;
int ** tileNum_;
bool ** revealed_;
};

#endif //STATKI_GRID_H
