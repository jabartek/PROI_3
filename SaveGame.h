#ifndef STATKI_SAVEGAME_H
#define STATKI_SAVEGAME_H

#include <fstream>
#include "NCInterface.h"

bool saveGame (Game*, std::string);
bool loadGame (Game*, std::string);

#endif //STATKI_SAVEGAME_H
