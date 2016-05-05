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
#include <curses.h>


int main(void) {

    WINDOW * mainwin;


    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) {
	fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }


    /*  Display "Hello, world!" in the centre of the
	screen, call refresh() to show our changes, and
	sleep() for a few seconds to get the full screen effect  */

    mvaddstr(13, 33, "Hello, world!");
    refresh();

    WINDOW * smallwin;
    smallwin = newwin(20, 20, 20, 20);
    box(smallwin, '|', '-');
	touchwin(smallwin);
	wrefresh(smallwin);

    getchar();

    /*  Clean up after ourselves  */

    delwin(smallwin);
    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}

