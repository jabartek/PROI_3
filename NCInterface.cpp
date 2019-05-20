#include "NCInterface.h"

Game* mainMenuInterface(){
  Game *result = nullptr;
  int pressedKey = 0;
  int currSelection = 1;
  char pressAny[] = "Press any key to start the program...";
  char welcome1[] = "Welcome to Battleship game!";
  char welcome2[] = "Choose an option:";
  char option1[] = "Start new game.";
  char option2[] = "Load a game.";
  char cursorInfo[] = "Use WASD to move cursor";
  char closeGame[] = "\"c\" to close game.";
  mvprintw(LINES/2, (COLS-strlen(pressAny))/2, pressAny);
  do{
    pressedKey = getch();
    clear();
    mvprintw(3, (COLS-strlen(welcome1))/2, welcome1);
    mvprintw(4, (COLS-strlen(welcome2))/2, welcome2);
    mvprintw(LINES - 4, (COLS-strlen(cursorInfo))/2, cursorInfo);
    mvprintw(LINES - 2, (COLS-strlen(closeGame))/2, closeGame);
    if(pressedKey == 'w' && currSelection == 2){
      currSelection--;
    }
    else if(pressedKey == 's' && currSelection == 1){
      currSelection++;
    }
    else if(pressedKey == 10 && currSelection == 1){
      result = new Game;
      newGameInterface(result);
      return result;
    }
    else if(pressedKey == 10 && currSelection == 2){
      result = nullptr;
      return result;
    }

    if(currSelection == 1){
      attron(A_REVERSE);
      mvprintw(LINES/2-1, (COLS-strlen(option1))/2, option1);
      attroff(A_REVERSE);
      mvprintw(LINES/2+1, (COLS-strlen(option2))/2, option2);
    }
    else if(currSelection == 2){
      mvprintw(LINES/2-1, (COLS-strlen(option1))/2, option1);
        attron(A_REVERSE);
      mvprintw(LINES/2+1, (COLS-strlen(option2))/2, option2);
    attroff(A_REVERSE);
    }


  } while(pressedKey!='c');

  return result;
}

void printNewGameInterface(int params[6]){
  char enterParams[] = "Enter desired parameters:";
  char downAnnotation1[] = "Enter the value, then confirm with RETURN key.";
  char param1[] = "Map width:";
  char param2[] = "Map height:";
  char param3[] = "Carriers:";
  char param4[] = "Battleships:";
  char param5[] = "Cruisers:";
  char param6[] = "Destroyers:";
  int paramLengths[6] = {10,11,9,12,9,11};
  clear();
  mvprintw(3, (COLS-strlen(enterParams))/2, enterParams);
  mvprintw(LINES - 2, (COLS-strlen(downAnnotation1))/2, downAnnotation1);
  mvprintw(LINES/2-5+0, (COLS-strlen(param1))/2-2, param1);
  mvprintw(LINES/2-5+2, (COLS-strlen(param2))/2-2, param2);
  mvprintw(LINES/2-5+4, (COLS-strlen(param3))/2-2, param3);
  mvprintw(LINES/2-5+6, (COLS-strlen(param4))/2-2, param4);
  mvprintw(LINES/2-5+8, (COLS-strlen(param5))/2-2, param5);
  mvprintw(LINES/2-5+10, (COLS-strlen(param6))/2-2, param6);
  for(int i =0; i<6; i++){
    if(params[i]!=-1){
      move(LINES/2-5+2*i, (COLS+paramLengths[i])/2);
      printw("%d",params[i]);
    }
  }
  return;
}

void newGameInterface(Game *game){
  int limitDown = 1;
  int limitWidth=(COLS-10)/2;
  int limitHeight=(LINES-24);
  int params[6] = {-1,-1,-1,-1,-1,-1};
  char str[160];
  std::string str_new;
  char tryAgain[] = "Invalid value, try again!";
  char tooBig[] = "Value too big. Insert smaller one or expand viewport!";
  int paramLengths[6] = {10,11,9,12,9,11};
  printNewGameInterface(params);
  curs_set(1);
  echo();
  for(int i=0; i<6; i++){
    if(i>1) limitDown = 0;
    move(LINES/2-5+2*i, (COLS+paramLengths[i])/2);
    do{
      str[0] = '\0';
      getnstr(str, 159);
      str_new = str;
      if(readInt(str_new)<limitDown){
        printNewGameInterface(params);
        mvprintw(LINES/2-5+2*i-1, (COLS+paramLengths[i])/2, tryAgain);
        move(LINES/2-5+2*i, (COLS+paramLengths[i])/2);
      }
      else if(readInt(str_new)>limitWidth && i==0){
        printNewGameInterface(params);
        mvprintw(LINES/2-5+2*i-1, (COLS+paramLengths[i])/2, tooBig);
        move(LINES/2-5+2*i, (COLS+paramLengths[i])/2);
      }
      else if(readInt(str_new)>limitHeight && i==1){
        printNewGameInterface(params);
        mvprintw(LINES/2-5+2*i-1, (COLS+paramLengths[i])/2, tooBig);
        move(LINES/2-5+2*i, (COLS+paramLengths[i])/2);
      }
      else {
        params[i] = readInt(str_new);
        break;
      }
    } while (params[i] < limitDown);
    printNewGameInterface(params);
}
game->startGame(params[0],params[1],params[2],params[3],params[4],params[5]);

curs_set(0);
  noecho();
  return;
};

void printInventory(GUI *gameInterface, Game *game, int player){
  WINDOW *curr_win = gameInterface->inventory[player];
werase(curr_win);
box(curr_win,0,0);
char ships1[] = "Carriers: ";
char ships2[] = "Battleships: ";
char ships3[] = "Cruisers: ";
char ships4[] = "Destroyers: ";
  mvwprintw(curr_win,2,2,"Inventory of Player %d",player+1);
  mvwprintw(curr_win,4,2,ships1);
  wprintw(curr_win,"%d/%d",game->getP(player)->getPending(3),game->getP(player)->getPlaced(3));
  mvwprintw(curr_win,6,2,ships2);
  wprintw(curr_win,"%d/%d",game->getP(player)->getPending(2),game->getP(player)->getPlaced(2));
  mvwprintw(curr_win,8,2,ships3);
  wprintw(curr_win,"%d/%d",game->getP(player)->getPending(1),game->getP(player)->getPlaced(1));
  mvwprintw(curr_win,10,2,ships4);
  wprintw(curr_win,"%d/%d",game->getP(player)->getPending(0),game->getP(player)->getPlaced(0));
  mvwprintw(curr_win,12,2,"Pending/Placed");
  wrefresh(curr_win);
}



void playGameInterface(Game *game){
  return;
};

GUI* initializeGUI(Game* game){
  refresh();
  GUI* result = new GUI;
  int xSize = game->getP1()->getGrid()->getXSize();
  int ySize = game->getP1()->getGrid()->getYSize();
  result->maps[0] = newwin(ySize+4,xSize+4,4,COLS/4-xSize/2-2);
  result->maps[1] = newwin(ySize+4,xSize+4,4,3*COLS/4-xSize/2-2);
  result->inventory[0] = newwin(15,24,ySize+8,COLS/4-12);
  result->inventory[1] = newwin(15,24,ySize+8,3*COLS/4-12);
  result->mapX = xSize;
  result->mapY = ySize;
  box(result->maps[0],0,0);
  box(result->maps[1],0,0);
  wrefresh(result->maps[0]);
  wrefresh(result->maps[1]);
  return result;
};


void visualiseShip(bool ifValid,int xPos,int yPos,int hdg,int shipSize, WINDOW *win){
        //init_pair(1, COLOR_GREEN, COLOR_BLACK);
        //init_pair(2, COLOR_RED, COLOR_BLACK);
        char ch[2] = "";
        if(ifValid)
          //attron(COLOR_PAIR(1));
          ch[0] = 'O';
        else
          //attron(COLOR_PAIR(2));
          ch[0] = 'X';
        switch (hdg) {
          default:
          for(int i=0; i<shipSize; i++){
            mvwprintw(win, 2+yPos, 2+xPos+i, ch);
          }
        break;
          case 1:
          for(int i=0; i<shipSize; i++){
            mvwprintw(win, 2+yPos-i, 2+xPos, ch);
          }
        break;
          case 2:
          for(int i=0; i<shipSize; i++){
            mvwprintw(win, 2+yPos, 2+xPos-i, ch);
          }
        break;
          case 3:
          for(int i=0; i<shipSize; i++){
            mvwprintw(win, 2+yPos+i, 2+xPos, ch);
          }
        break;
      }

    //attroff(COLOR_PAIR(1));
    //attroff(COLOR_PAIR(2));
}

int readInt(std::string temp) {
    int value = 0;
    bool error = false;
        try {
            value = std::stoi(temp);
            error = false;
        }
        catch (std::invalid_argument) {
            error = true;
        }
    if(error) return -1;
    return value;
}

GUI::~GUI(){
  for(int i=0; i<2;i++){
    delete maps[i];
    delete inventory[i];
  }
}

void holdPlayer(int player){
  clear();
  int val;
  char title[] = "It is now turn of";
  char pressAny[] = "Press any key to continue...";
  int titleWidth = 17;
  mvprintw(LINES/2-3,COLS/2-strlen(title)/2,title);
  mvprintw(LINES/2-2,COLS/2-4, "Player %d",player+1);
  mvprintw(LINES/2+1,COLS/2-strlen(pressAny)/2,pressAny);
  val = getch();
  return;
}

void shipPlacing(Game *game, GUI *gameInterface){
for(int p = 0; p<2; p++){
  holdPlayer(p);
  placeShipsInterface(game, gameInterface, p);
}
}

void placeShipsInterface(Game* game, GUI *gameInterface, int player){
  Ship *s = nullptr; //ship to be placed
  Ship *d = nullptr; //ship to be deleted
  int otherPlayer = player+1;
  otherPlayer = otherPlayer%2;
  bool ifValid = 0;
  bool isPlacing = 0;
  char keyHelp1[] = "Move cursor with WASD. Use P to toggle placing mode.";
  char keyHelp2[] = "In placing mode use RETURN to place ships and R to rotate.";
  char keyHelp3[] = "You can remove ships with G. Confirm placement with C.";
  char keyHelp4[] = "To skip a ship and place it later use K.";
  Cursor cur;
  int ch = 0;
  clear();
  mvprintw(LINES-4,(COLS-strlen(keyHelp1))/2,keyHelp1);
  mvprintw(LINES-3,(COLS-strlen(keyHelp2))/2,keyHelp2);
  mvprintw(LINES-2,(COLS-strlen(keyHelp3))/2,keyHelp3);
  mvprintw(LINES-1,(COLS-strlen(keyHelp4))/2,keyHelp4);
  refresh();
  do{
    printMap(gameInterface, game, 0, player);
    printMap(gameInterface, game, 1, otherPlayer);
    printInventory(gameInterface, game, player);
    printInventory(gameInterface, game, otherPlayer);
    if(!isPlacing){
      mvwchgat(gameInterface->maps[player],cur.y+2,cur.x+2,1,A_REVERSE,0,nullptr);
    }
    else if(!game->getP(player)->getInventory()->empty()){
        s = game->getP(player)->getInventory()->front();
        ifValid = s->isValid(game->getP(player)->getGrid(), cur.x, cur.y, cur.hdg);
        visualiseShip(ifValid, cur.x, cur.y,cur.hdg,s->getSize(),gameInterface->maps[player]);
    }
    ch = wgetch(gameInterface->maps[player]);
    if(ch == 'w' && cur.y >0) {
      cur.y--;
    }
    else if(ch == 's' && cur.y < game->getP(1)->getGrid()->getYSize()-1) {
      cur.y++;
    }
    else if(ch == 'a' && cur.x > 0 ){
      cur.x--;
    }
    else if(ch == 'd' && cur.x < game->getP(1)->getGrid()->getXSize()-1){
      cur.x++;
    }
    else if(ch == 'r'){
      cur.hdg++;
      cur.hdg=cur.hdg%4;
    }
    else if(ch == 'p'){
      isPlacing = !isPlacing;
    }
    else if(isPlacing && ch == 10 && ifValid){
      game->getP(player)->placeShip(cur.x, cur.y, cur.hdg);
    }
    else if(!isPlacing && ch == 'g'){
      d = game->getP(player)->getGrid()->getShip(cur.x,cur.y);
      if(d!=nullptr){
        game->getP(player)->removeShip(d);
      }
    }
    else if(isPlacing && ch == 'k' && !game->getP(player)->getInventory()->empty()){
      game->getP(player)->skipInventory();
    }
  }while(ch!='c');


  return;
};

void shootShips(Game *game, GUI *gameInterface){
  char congrats1[] = "Congratulations!";
  char congrats2[] = "You hit an opponent's ship!";
  char sad1[] = "Sad :(";
  char sad2[] = "You missed!";
  int player = game->currPlayer();
  int otherPlayer = (player+1)%2;
  Cursor cur;
  int ch = 0;
  int result = -1;
  holdPlayer(player);
  clear();
  refresh();
  do{
    printMap(gameInterface, game, 0, player);
    printMap(gameInterface, game, 1, otherPlayer);
    printInventory(gameInterface, game, player);
    printInventory(gameInterface, game, otherPlayer);
    mvwchgat(gameInterface->maps[otherPlayer],cur.y+2,cur.x+2,1,A_REVERSE,0,nullptr);
    ch = wgetch(gameInterface->maps[otherPlayer]);
    if(ch == 'w' && cur.y >0) {
      cur.y--;
    }
    else if(ch == 's' && cur.y < game->getP(1)->getGrid()->getYSize()-1) {
      cur.y++;
    }
    else if(ch == 'a' && cur.x > 0 ){
      cur.x--;
    }
    else if(ch == 'd' && cur.x < game->getP(1)->getGrid()->getXSize()-1){
      cur.x++;
    }
  }while(ch!=10);
  result = game->getP(otherPlayer)->getGrid()->shotAtXY(cur.x,cur.y);
  WINDOW *alertResult = newwin(6,30,LINES/2-3,COLS/2-15);
  switch(result){
    case (1):
    mvwprintw(alertResult,2,15-strlen(congrats1)/2,congrats1);
    mvwprintw(alertResult,3,15-strlen(congrats2)/2,congrats2);
    break;
    default:
    mvwprintw(alertResult,2,15-strlen(sad1)/2,sad1);
    mvwprintw(alertResult,3,15-strlen(sad2)/2,sad2);
    break;
  }
  box(alertResult,0,0);
  wrefresh(alertResult);
    printMap(gameInterface, game, 0, player);
    printMap(gameInterface, game, 1, otherPlayer);
    printInventory(gameInterface, game, player);
    printInventory(gameInterface, game, otherPlayer);
result = getch();
delwin(alertResult);
  game->togglePlayer();

}

void printMap(GUI *gameInterface, Game *game, int param, int player){
  wclear(gameInterface->maps[player]);
  box(gameInterface->maps[player],0,0);
  mvwprintw(gameInterface->maps[player],0,1,"Player %d",player+1);
  int xSize = game->getP(player)->getGrid()->getXSize();
  int ySize = game->getP(player)->getGrid()->getYSize();
  char toPrint[2]="";
  for(int i=0; i<gameInterface->mapY;i++){
    for(int j=0; j<gameInterface->mapX;j++){
      toPrint[0] = game->getP(player)->getGrid()->renderXY(j,i,param);
      mvwprintw(gameInterface->maps[player], i+2, j+2,toPrint);
    }
  }
  wrefresh(gameInterface->maps[player]);
}
