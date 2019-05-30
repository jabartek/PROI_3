#ifndef STATKI_NCINTERFACE_H
#define STATKI_NCINTERFACE_H

#include "ncurses.h"
#include "Game.h"
#include "Ship.h"
#include "SaveGame.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>


class GUI {
public:
GUI(Game*);
GUI();
~GUI();


void shipPlacing(Game*);
void shootShips(Game*);
void printMap(Game*, int,int);
void placeShipsInterface(Game*,int);
void printInventory(Game*, int);
void printFleet(Game*, int);
void visualiseShip(bool,int,int,int,int, WINDOW*);

//DATA. As used often and only in pounter form it's made public
WINDOW *maps[2] = {nullptr,nullptr};
WINDOW *inventory[2] = {nullptr,nullptr};
WINDOW *alert = nullptr;
int mapX=20;
int mapY=20;
};

class Cursor {
public:
int x=0;
int y=0;
int hdg=0;
};

//GUI initialiser
GUI* initializeGUI(Game*);











//helper functions for windows
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);


//independent intefraces
Game* mainMenuInterface();
void newGameInterface(Game*);
void printNewGameInterface(int*);
void displayWinner(int);
Game* loadGameInterface();
void saveGameInterface(Game*);
void holdPlayer(int);

//helper function for integer inputs
int readInt(std::string);


#endif //STATKI_NCINTERFACE_H
