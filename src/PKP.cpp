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
int main(void) {

    WINDOW * mainwin;
    //disable cursor

    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) {
	fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }

    curs_set(0);

    mvaddstr(0, COLS/2, "PKP");
    refresh();

    Queue que = Queue();
    Booths booths = Booths();

    int pressedKey = getch();
    while(pressedKey != 27 ){
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
    	}

    	pressedKey = getch();
    }

    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}

