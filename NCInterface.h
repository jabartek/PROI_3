#ifndef NCINTERFACE
#define NCINTERFACE

#include "ncurses.h"
#include "Game.h"
#include "Ship.h"
#include <cstring>
#include <iostream>
#include <vector>



class GUI{
public:
  ~GUI();
  WINDOW *maps[2] = {nullptr,nullptr};
  WINDOW *inventory[2] = {nullptr,nullptr};
  int mapX=20;
  int mapY=20;
};

class Cursor{
public:
	int x=0;
	int y=0;
	int hdg=0;
};

Game* mainMenuInterface();

void printNewGameInterface(int*);
void newGameInterface(Game*);

void printInventory(GUI*, Game*, int);

void placeShipsInterface(Game*, GUI*,int);
void printPlaceShipsInterface(Game*, int);

void playGameInterface(Game*);

GUI* initializeGUI(Game*);

void shipPlacing(Game*, GUI*);

void printMap(GUI*, Game*, int,int);

void holdPlayer(int);

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

void visualiseShip(bool,int,int,int,int, WINDOW*);

int readInt(std::string);

#endif //STATKI_NCINTERFACE_H
