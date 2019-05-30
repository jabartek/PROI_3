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
        do {
                pressedKey = getch();
                clear();
                mvprintw(3, (COLS-strlen(welcome1))/2, welcome1);
                mvprintw(4, (COLS-strlen(welcome2))/2, welcome2);
                mvprintw(LINES - 4, (COLS-strlen(cursorInfo))/2, cursorInfo);
                mvprintw(LINES - 2, (COLS-strlen(closeGame))/2, closeGame);
                if(pressedKey == 'w' && currSelection == 2) {
                        currSelection--;
                }
                else if(pressedKey == 's' && currSelection == 1) {
                        currSelection++;
                }
                else if(pressedKey == 10 && currSelection == 1) {
                        result = new Game;
                        newGameInterface(result);
                        return result;
                }
                else if(pressedKey == 10 && currSelection == 2) {
                        result = loadGameInterface();
                        return result;
                }

                if(currSelection == 1) {
                        attron(A_REVERSE);
                        mvprintw(LINES/2-1, (COLS-strlen(option1))/2, option1);
                        attroff(A_REVERSE);
                        mvprintw(LINES/2+1, (COLS-strlen(option2))/2, option2);
                }
                else if(currSelection == 2) {
                        mvprintw(LINES/2-1, (COLS-strlen(option1))/2, option1);
                        attron(A_REVERSE);
                        mvprintw(LINES/2+1, (COLS-strlen(option2))/2, option2);
                        attroff(A_REVERSE);
                }


        } while(pressedKey!='c');

        return result;
}

Game* loadGameInterface(){
        char loadingGame[] = "LOADING GAME";
        char insertPath[] = "INSERT FILEPATH: ";
        char failedLoading[] = "FAILED LOADING FROM INSERTED FILEPATH!";
        Game* result = new Game;
        std::string path = "";
        bool success = false;
        bool failedLoad = false;
        char str[159];
        while(!success) {
                clear();
                if(failedLoad) {
                        mvprintw(LINES/2-3,COLS/2-strlen(failedLoading)/2,failedLoading);
                }
                mvprintw(LINES/2-1,COLS/2-strlen(loadingGame)/2,loadingGame);
                mvprintw(LINES/2,COLS/2-strlen(insertPath)/2,insertPath);
                curs_set(1);
                echo();
                refresh();
                getnstr(str, 159);
                path = str;
                if(loadGame(result, path)) {
                        success = true;
                }
                else
                        failedLoad = true;
        }
        noecho();
        curs_set(0);
        return result;
}

void saveGameInterface(Game *game){
        char savingGame[] = "SAVING GAME";
        char insertPath[] = "INSERT FILEPATH: ";
        char failedSaving[] = "FAILED SAVING TO INSERTED FILEPATH!";
        std::string path = "";
        bool success = false;
        bool failedOpen = false;
        char str[159];
        while(!success) {
                clear();
                if(failedOpen) {
                        mvprintw(LINES/2-3,COLS/2-strlen(failedSaving)/2,failedSaving);
                }
                mvprintw(LINES/2-1,COLS/2-strlen(savingGame)/2,savingGame);
                mvprintw(LINES/2,COLS/2-strlen(insertPath)/2,insertPath);
                curs_set(1);
                echo();
                refresh();
                getnstr(str, 159);
                path = str;
                std::ofstream outFile (path);
                if(!outFile.is_open()) {
                        failedOpen = true;
                }
                else{
                        outFile.close();
                        saveGame(game, path);
                        success = true;
                }
        }
        noecho();
        curs_set(0);
        game->setSaved();
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
        for(int i =0; i<6; i++) {
                if(params[i]!=-1) {
                        move(LINES/2-5+2*i, (COLS+paramLengths[i])/2);
                        printw("%d",params[i]);
                }
        }
        return;
}


void newGameInterface(Game *game){
        int limitDown = 1;
        int totalShips = 0;
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
        for(int i=0; i<6; i++) {
                if(i>1) limitDown = 0;
                move(LINES/2-5+2*i, (COLS+paramLengths[i])/2);
                do {
                        str[0] = '\0';
                        getnstr(str, 159);
                        str_new = str;
                        if(readInt(str_new)<limitDown || (i==5 && totalShips+readInt(str_new)==0)) {
                                printNewGameInterface(params);
                                mvprintw(LINES/2-5+2*i-1, (COLS+paramLengths[i])/2, tryAgain);
                                move(LINES/2-5+2*i, (COLS+paramLengths[i])/2);
                        }
                        else if(readInt(str_new)>limitWidth && i==0) {
                                printNewGameInterface(params);
                                mvprintw(LINES/2-5+2*i-1, (COLS+paramLengths[i])/2, tooBig);
                                move(LINES/2-5+2*i, (COLS+paramLengths[i])/2);
                        }
                        else if(readInt(str_new)>limitHeight && i==1) {
                                printNewGameInterface(params);
                                mvprintw(LINES/2-5+2*i-1, (COLS+paramLengths[i])/2, tooBig);
                                move(LINES/2-5+2*i, (COLS+paramLengths[i])/2);
                        }
                        else {
                                params[i] = readInt(str_new);
                                if(i>1) {
                                        totalShips+=params[i];
                                }
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

void GUI::printInventory(Game *game, int player){
        WINDOW *curr_win = this->inventory[player];
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


void GUI::printFleet(Game *game, int player){
        WINDOW *curr_win = this->inventory[player];
        werase(curr_win);
        box(curr_win,0,0);
        char ships1[] = "Carriers: ";
        char ships2[] = "Battleships: ";
        char ships3[] = "Cruisers: ";
        char ships4[] = "Destroyers: ";
        mvwprintw(curr_win,2,2,"Fleet of Player %d",player+1);
        mvwprintw(curr_win,4,2,ships1);
        wprintw(curr_win,"%d/%d",game->getP(player)->getPlaced(3)-game->getP(player)->getSunken(3),game->getP(player)->getSunken(3));
        mvwprintw(curr_win,6,2,ships2);
        wprintw(curr_win,"%d/%d",game->getP(player)->getPlaced(2)-game->getP(player)->getSunken(2),game->getP(player)->getSunken(2));
        mvwprintw(curr_win,8,2,ships3);
        wprintw(curr_win,"%d/%d",game->getP(player)->getPlaced(1)-game->getP(player)->getSunken(1),game->getP(player)->getSunken(1));
        mvwprintw(curr_win,10,2,ships4);
        wprintw(curr_win,"%d/%d",game->getP(player)->getPlaced(0)-game->getP(player)->getSunken(0),game->getP(player)->getSunken(0));
        mvwprintw(curr_win,12,2,"Alive/Sunken");
        wrefresh(curr_win);
}



GUI::GUI(){
        //default ctor;
}



GUI::GUI(Game* game){
        refresh();
        int xSize = game->getP(0)->getGrid()->getXSize();
        int ySize = game->getP(0)->getGrid()->getYSize();
        this->maps[0] = newwin(ySize+4,xSize+4,4,COLS/4-xSize/2-2);
        this->maps[1] = newwin(ySize+4,xSize+4,4,3*COLS/4-xSize/2-2);
        this->inventory[0] = newwin(15,24,ySize+8,COLS/4-12);
        this->inventory[1] = newwin(15,24,ySize+8,3*COLS/4-12);
        this->mapX = xSize;
        this->mapY = ySize;
        box(this->maps[0],0,0);
        box(this->maps[1],0,0);
        wrefresh(this->maps[0]);
        wrefresh(this->maps[1]);
}


void GUI::visualiseShip(bool ifValid,int xPos,int yPos,int hdg,int shipSize, WINDOW *win){
        char ch[2] = "";
        if(ifValid)
                ch[0] = 'O';
        else
                ch[0] = 'X';
        switch (hdg) {
        default:
                for(int i=0; i<shipSize; i++) {
                        mvwprintw(win, 2+yPos, 2+xPos+i, ch);
                }
                break;
        case 1:
                for(int i=0; i<shipSize; i++) {
                        mvwprintw(win, 2+yPos-i, 2+xPos, ch);
                }
                break;
        case 2:
                for(int i=0; i<shipSize; i++) {
                        mvwprintw(win, 2+yPos, 2+xPos-i, ch);
                }
                break;
        case 3:
                for(int i=0; i<shipSize; i++) {
                        mvwprintw(win, 2+yPos+i, 2+xPos, ch);
                }
                break;
        }
}



GUI::~GUI(){
        for(int i=0; i<2; i++) {
                delwin(maps[i]);
                delwin(inventory[i]);
        }
}

void holdPlayer(int player){
        clear();
        char title[] = "It is now turn of";
        char pressAny[] = "Press any key to continue...";
        mvprintw(LINES/2-3,COLS/2-strlen(title)/2,title);
        mvprintw(LINES/2-2,COLS/2-4, "Player %d",player+1);
        mvprintw(LINES/2+1,COLS/2-strlen(pressAny)/2,pressAny);
        getch();
        return;
}

void GUI::shipPlacing(Game *game){
        for(int p = 0; p<2; p++) {
                holdPlayer(p);
                placeShipsInterface(game, p);
        }
}

void GUI::placeShipsInterface(Game* game, int player){
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
        do {
                printMap(game, 0, player);
                printMap(game, 1, otherPlayer);
                printInventory(game, player);
                printInventory(game, otherPlayer);
                if(!isPlacing) {
                        mvwchgat(this->maps[player],cur.y+2,cur.x+2,1,A_REVERSE,0,nullptr);
                }
                else if(!game->getP(player)->getInventory()->empty()) {
                        s = game->getP(player)->getInventory()->front();
                        ifValid = s->isValid(game->getP(player)->getGrid(), cur.x, cur.y, cur.hdg);
                        visualiseShip(ifValid, cur.x, cur.y,cur.hdg,s->getSize(),this->maps[player]);
                }
                ch = wgetch(this->maps[player]);
                if(ch == 'w' && cur.y >0) {
                        cur.y--;
                }
                else if(ch == 's' && cur.y < game->getP(1)->getGrid()->getYSize()-1) {
                        cur.y++;
                }
                else if(ch == 'a' && cur.x > 0 ) {
                        cur.x--;
                }
                else if(ch == 'd' && cur.x < game->getP(1)->getGrid()->getXSize()-1) {
                        cur.x++;
                }
                else if(ch == 'r') {
                        cur.hdg++;
                        cur.hdg=cur.hdg%4;
                }
                else if(ch == 'p') {
                        isPlacing = !isPlacing;
                }
                else if(isPlacing && ch == 10 && ifValid) {
                        game->getP(player)->placeShip(cur.x, cur.y, cur.hdg);
                }
                else if(!isPlacing && ch == 'g') {
                        d = game->getP(player)->getGrid()->getShip(cur.x,cur.y);
                        if(d!=nullptr) {
                                game->getP(player)->removeShip(d);
                        }
                }
                else if(isPlacing && ch == 'k' && !game->getP(player)->getInventory()->empty()) {
                        game->getP(player)->skipInventory();
                }
        } while(ch!='c');


        return;
};

void GUI::shootShips(Game *game){
        WINDOW* alertResult = nullptr;
        char congrats1[] = "Congratulations!";
        char congrats2[] = "You hit an opponent's ship!";
        char congrats3[] = "You've sunken a ship!";
        char error1[] = "You already tried shooting";
        char error2[] = "that tile. Try other one.";
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
        do {
                printMap(game, 0, player);
                printMap(game, 1, otherPlayer);
                printFleet(game, player);
                printFleet(game, otherPlayer);
                mvwchgat(this->maps[otherPlayer],cur.y+2,cur.x+2,1,A_REVERSE,0,nullptr);
                ch = wgetch(this->maps[otherPlayer]);
                wclear(alertResult);
                wrefresh(alertResult);
                if(ch == 'v') {
                        saveGameInterface(game);
                        delwin(alertResult);
                        return;
                }
                if(ch == 'w' && cur.y >0) {
                        cur.y--;
                }
                else if(ch == 's' && cur.y < game->getP(1)->getGrid()->getYSize()-1) {
                        cur.y++;
                }
                else if(ch == 'a' && cur.x > 0 ) {
                        cur.x--;
                }
                else if(ch == 'd' && cur.x < game->getP(1)->getGrid()->getXSize()-1) {
                        cur.x++;
                }
                else if(ch==10 && game->getP(otherPlayer)->getGrid()->isRevealed(cur.x,cur.y)) {
                        delwin(alertResult);
                        alertResult = newwin(6,30,LINES/2-3,COLS/2-15);
                        box(alertResult,0,0);
                        mvwprintw(alertResult,2,15-strlen(error1)/2,error1);
                        mvwprintw(alertResult,3,15-strlen(error2)/2,error2);
                        wrefresh(alertResult);
                }
        } while(ch!=10 or game->getP(otherPlayer)->getGrid()->isRevealed(cur.x,cur.y));
        result = game->getP(otherPlayer)->shotAtGridXY(cur.x,cur.y);
        delwin(alertResult);
        alertResult = newwin(6,30,LINES/2-3,COLS/2-15);
        switch(result) {
        case (1):
                mvwprintw(alertResult,2,15-strlen(congrats1)/2,congrats1);
                mvwprintw(alertResult,3,15-strlen(congrats2)/2,congrats2);
                break;
        case (-1):
                mvwprintw(alertResult,2,15-strlen(congrats1)/2,congrats1);
                mvwprintw(alertResult,3,15-strlen(congrats3)/2,congrats3);
                break;
        default:
                mvwprintw(alertResult,2,15-strlen(sad1)/2,sad1);
                mvwprintw(alertResult,3,15-strlen(sad2)/2,sad2);
                break;
        }
        printMap(game, 0, player);
        printMap(game, 1, otherPlayer);
        printFleet(game, player);
        printFleet(game, otherPlayer);
        box(alertResult,0,0);
        wrefresh(alertResult);
        result = getch();
        delwin(alertResult);
        game->togglePlayer();

}

void GUI::printMap(Game *game, int param, int player){
        wclear(this->maps[player]);
        box(this->maps[player],0,0);
        mvwprintw(this->maps[player],0,1,"Player %d",player+1);
        char toPrint[2]="";
        for(int i=0; i<this->mapY; i++) {
                for(int j=0; j<this->mapX; j++) {
                        toPrint[0] = game->getP(player)->getGrid()->renderXY(j,i,param);
                        mvwprintw(this->maps[player], i+2, j+2,toPrint);
                }
        }
        wrefresh(this->maps[player]);
}


void displayWinner(int winner){
        clear();
        refresh();
        if(winner!=0)
                mvprintw(LINES/2,COLS/2-12,"THE WINNER IS PLAYER %d",winner);
        else{
                mvprintw(LINES/2-1,COLS/2-5,"GAME SAVED!");
                mvprintw(LINES/2,COLS/2-7,"SEE YOU LATER!");
        }
        getch();
}


int readInt(std::string temp) {
        int value = 0;
        bool error = false;
        try {
                value = std::stoi(temp);
                error = false;
        }
        catch (std::invalid_argument || std::out_of_range) {
                error = true;
        }
        if(error) return -1;
        return value;
}
