#include "SaveGame.h"

bool saveGame (Game *game, std::string filePath){
        std::ofstream outFile (filePath);
        if (!outFile.is_open())
                return 0;
        else{
                outFile << game->getXSize()<<" "<<game->getYSize()<<" "<<game->currPlayer()<<"\n";
                for(int i=0; i<2; i++) {
                        for(int j=0; j<game->getYSize(); j++) {
                                for(int k=0; k<game->getXSize(); k++) {
                                        if(game->getP(i)->getGrid()->getShip(k,j) != nullptr) {
                                                outFile << game->getP(i)->getGrid()->getShip(k,j)->getSize()<< " "
                                                        << game->getP(i)->getGrid()->getShip(k,j)->getHeadX() << " "
                                                        << game->getP(i)->getGrid()->getShip(k,j)->getHeadY()<< " "
                                                        << game->getP(i)->getGrid()->getShip(k,j)->getHeading()<< "\n";
                                                Ship *temp = game->getP(i)->getGrid()->getShip(k,j);
                                                temp->removeFromMap();
                                                delete temp;
                                        }
                                }
                        }
                        outFile << "\nP\n";
                        for(int j=0; j<game->getP(i)->getGrid()->getYSize(); j++) {
                                for(int k=0; k<game->getP(i)->getGrid()->getXSize(); k++) {
                                        outFile << game->getP(i)->getGrid()->isRevealed(k,j) << " ";
                                }
                                outFile <<"\n";
                        }
                }
        }
        outFile.close();
        game->setSaved();
        return 1;
}

bool loadGame(Game *game, std::string filePath){
        std::ifstream inFile(filePath);
        if (!inFile.is_open())
                return 0;
        int xSize, ySize, sPlayer;
        int tempX,tempY,tempH,tempS;
        std::string temp = "";
        bool wasError = false;
        inFile >> temp;
        if(readInt(temp)<0) {
                inFile.close();
                return 0;
        }
        else
                xSize = readInt(temp);
        inFile >> temp;
        if(readInt(temp)<0) {
                inFile.close();
                return 0;
        }
        else
                ySize = readInt(temp);

        inFile >> temp;
        if(readInt(temp)<0) {
                inFile.close();
                return 0;
        }
        else
                sPlayer = readInt(temp);
        game->startGame(xSize, ySize, 0,0,0,0);
        game->setPlayer(sPlayer);
        temp = "";
        for(int i = 0; i<2; i++) {
                inFile >> temp;
                while(temp != "P") {
                        try{
                                if(readInt(temp)>=2 && readInt(temp) <=5) {
                                        tempS = readInt(temp);
                                }
                                else{
                                        throw -1;
                                }
                                inFile >> temp;
                                if(readInt(temp)>=0) {
                                        tempX = readInt(temp);
                                }
                                else{
                                        throw -1;
                                }
                                inFile >> temp;
                                if(readInt(temp)>=0) {
                                        tempY = readInt(temp);
                                }
                                else{
                                        throw -1;
                                }
                                inFile >> temp;
                                if(readInt(temp)>=0) {
                                        tempH = readInt(temp);
                                }
                                else{
                                        throw -1;
                                }
                        }
                        catch(int) {
                                wasError = true;
                        }
                        if (wasError) {
                                break;
                        }

                        Ship *s = nullptr;
                        if(tempS == 2)
                                s = new Destroyer;
                        else if(tempS == 3 )
                                s = new Cruiser;
                        else if(tempS == 4 )
                                s = new Battleship;
                        else if(tempS == 5)
                                s = new Carrier;
                        else{
                                wasError = true;
                                break;
                        }
                        if(s != nullptr) {
                                if(!s->placeAtXY(game->getP(i)->getGrid(), tempX, tempY, tempH)) {
                                        delete s;
                                        wasError = true;
                                        break;
                                }
                                else{
                                        game->getP(i)->addPlaced(s->getSize());
                                }
                        }
                        else{
                                wasError = true;
                                break;
                        }
                        inFile >> temp;
                }
                for(int j = 0; j<xSize; j++) {
                        for(int k = 0; k<ySize; k++) {
                                inFile>>temp;
                                if(readInt(temp)<0) {
                                        wasError=true;
                                        break;
                                }
                                else if(readInt(temp)>0) {
                                        game->getP(i)->shotAtGridXY(j,k);
                                }
                        }
                        if(wasError) break;
                }
                if(wasError) break;

        }

        inFile.close();
        if(!wasError) {
                game->toggleRunning();
        }
        else{
                delete game;
                game = new Game;
        }
        return !wasError;
}
