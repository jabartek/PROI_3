#include "Game.h"
#include "Player.h"
#include "Grid.h"
#include "Ship.h"
#include "NCInterface.h"

struct cursor{
	int x=0;
	int y=0;
	int hdg=0;
};

void aaa();

int main()
{
	Game game1;
	game1.startGame(10,10,10,10,10,10);
	Ship* abc = new Carrier;
	std::cout<<abc->placeAtXY(game1.getP2()->getGrid(), 3, 3, 0);
	abc = new Destroyer;
	cursor a;

    //start
    initscr();
		printw( "Press any key to start the program..." );
    noecho();
    //rozpoczynamy wyswietlanie menu!
    int znak;
		char ab[] = " ";
		curs_set(0);
    do
    {
        //pobieranie znaku
        znak = getch();
        clear();
        if( znak == 'w' && a.y >= 1 )
        {
            a.y--;
        }
        else if( znak == 'a' && a.x >= 1 )
        {
            a.x--;
        }
        else if( znak == 'd' && a.x < game1.getP2()->getGrid()->getXSize()-1)
        {
            a.x++;
        }
        else if( znak == 's' && a.y < game1.getP2()->getGrid()->getYSize()-1	)
        {
            a.y++;
        }
				else if( znak == 'r'){
					a.hdg++;
					a.hdg=a.hdg%4;
				}
				else if(znak == 'p' && abc->isValid(game1.getP2()->getGrid(), a.x, a.y, a.hdg)){
					abc->placeAtXY(game1.getP2()->getGrid(), a.x, a.y, a.hdg);
				}
        //reakcja
        if( znak == 10 )
        {
					game1.getP2()->getGrid()->shotAtXY(a.x, a.y);
        }

        //wyswietlanie
				for(int i=0; i<game1.getP2()->getGrid()->getYSize(); i++){
					for(int j=0; j<game1.getP2()->getGrid()->getXSize(); j++){
							ab[0] = game1.getP2()->getGrid()->renderXY(j,i);
		            mvprintw( 3 + 2*i, 1 + 2*j,  ab);
					}
				}
				attron( A_REVERSE );
				ab[0] = game1.getP2()->getGrid()->renderXY(a.x,a.y);
				mvprintw( 0,0, "WASD to move cursor. R to rotate. P to place. Enter to shoot.");
				mvprintw( 3+2*a.y, 1+2*a.x, ab);
        attroff( A_REVERSE );
				visualiseShip(abc->isValid(game1.getP2()->getGrid(), a.x, a.y, a.hdg), a.x, a.y, a.hdg, 2, curscr);

    } while( znak != 'c' );

    move( 9, 3 );
    printw( "Program stopped. Press any key to continue..." );
    getch();
    endwin();
		return 0;


}
