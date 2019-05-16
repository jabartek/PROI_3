#include "NCInterface.h"

void visualiseShip(bool ifValid,int xPos,int yPos,int hdg,int shipSize, WINDOW *win){
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        if(ifValid)
          attron(COLOR_PAIR(1));
        else
          attron(COLOR_PAIR(2));
        switch (hdg) {
          case 0:
          for(int i=0; i<shipSize; i++){
            mvwprintw(stdscr, 3+2*yPos, 1+2*xPos+2*i, "O");
          }
        break;
          case 1:
          for(int i=0; i<shipSize; i++){
            mvwprintw(stdscr, 3+2*yPos-2*i, 1+2*xPos, "O");
          }
        break;
          case 2:
          for(int i=0; i<shipSize; i++){
            mvwprintw(stdscr, 3+2*yPos, 1+2*xPos-2*i, "O");
          }
        break;
          case 3:
          for(int i=0; i<shipSize; i++){
            mvwprintw(stdscr, 3+2*yPos+2*i, 1+2*xPos, "O");
          }
        break;
      }

    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(2));
}
