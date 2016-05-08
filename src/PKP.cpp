/*

  CURHELLO.C
  ==========
  (c) Copyright Paul Griffiths 1999
  Email: mail@paulgriffiths.net

  "Hello, world!", ncurses style.

*/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */

#include <Graphics.h>
#include <Queue.h>
#include <Booths.h>
#include <Platforms.h>
#include <Train.h>

int main(void) {

    WINDOW * mainwin;

    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) {
		fprintf(stderr, "Error initialising ncurses.\n");
		exit(EXIT_FAILURE);
    }

    //dont show user input
    cbreak();
    noecho();

    //disable cursor
    curs_set(0);

    mvaddstr(0, COLS/2, "PKP");
    refresh();

    Queue que = Queue();
    Booths booths = Booths();
    Platforms platforms = Platforms();
    Train train1 = Train(0, 0);
    Train train2 = Train(1, 0);
    Train train3 = Train(0, 1);
    Train train4 = Train(1, 1);

    int pressedKey = getch();
    while(pressedKey != 27 ){
    	int x = 0;

    	switch(pressedKey)
    	{
    	//spacja dodanie ludzi do kolejki
    	case 32:
    		que.addPeople();
    		break;
    	//+ dodanie budki z biletami
    	case 43:
    		booths.addBooth();
    		break;
    	//- usuniecie budki z biletami
    	case 45:
    		booths.removeBooth();
    		break;
    	// q pierwszy pociag od lewej
    	case 113:
    		x = 1;
    		break;
    	// w drugi pociag od lewej
    	case 119:
    		x = 2;
    		break;
    	// e trzeci pociag od lewej
    	case 101:
    		x = 3;
    		break;
    	// r czwarty pociag od lewej
    	case 114:
    		x = 4;
    		break;
    	}


    	pressedKey = getch();
    }

    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}

