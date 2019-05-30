#include "Game.h"
#include "Player.h"
#include "Grid.h"
#include "Ship.h"
#include "NCInterface.h"



int main()
{
								initscr(); //screen initialisation for ncurses
								noecho(); //disables printing to std output
								curs_set(0); //hides cursor
								cbreak(); //enables special keys
								Game* game = mainMenuInterface();
								GUI* gameInterface = new GUI(game);
								if(!game->wasStarted()) {
																gameInterface->shipPlacing(game);
																game->runGame(0);
								}
								int winner = -1;
								while(winner==-1) {
																gameInterface->shootShips(game);
																winner = game->hasWon();
								}
								displayWinner(winner);
								delete gameInterface;
								delete game;
								endwin();
								return 0;
}
