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
#include <SignalLight.h>

int main(void) {

    WINDOW * mainwin;

    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) {
		fprintf(stderr, "Error initialising ncurses.\n");
		exit(EXIT_FAILURE);
    }

    if(has_colors() == FALSE)
    	exit(EXIT_FAILURE);

    //dont show user input
    cbreak();
    noecho();

    //disable cursor
    curs_set(0);

    //allow colors
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);

    mvaddstr(0, COLS/2, "PKP");
    refresh();

    //TODO madrze to ustawic zeby obiekty zabijaly sie przed glownym oknem
    if(true){
		Queue que = Queue();
		SignalLight signalLight = SignalLight();
		Platforms platforms = Platforms(&signalLight);
		Booths booths = Booths(&platforms, &que);


		pthread_mutex_lock(&graphicMutex);
		int pressedKey = getch();
		pthread_mutex_unlock(&graphicMutex);

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
			// q dodanie pierwszy pociag od lewej
			case 113:
				platforms.addTrain(3);
				break;
			// a usuniecie pierwszy pociag od lewej
			case 97:
				platforms.removeTrain(3);
				break;
			// w dodanie drugi pociag od lewej
			case 119:
				platforms.addTrain(2);
				break;
			// s usuniecie drugi pociag od lewej
			case 115:
				platforms.removeTrain(2);
				break;
			// e dodanie trzeci pociag od lewej
			case 101:
				platforms.addTrain(1);
				break;
			// d usuniecie trzeci pociag od lewej
			case 100:
				platforms.removeTrain(1);
				break;
			// r dodanie czwarty pociag od lewej
			case 114:
				platforms.addTrain(0);
				break;
			// f usuniecie czwarty pociag od lewej
			case 102:
				platforms.removeTrain(0);
				break;
			//enter zmiana swiatla
			case 10:
				signalLight.changeColor();
				break;
			}

			pthread_mutex_lock(&graphicMutex);
			pressedKey = getch();
			pthread_mutex_unlock(&graphicMutex);
		}
    }

    delwin(mainwin);
    endwin();
	pthread_mutex_lock(&graphicMutex);
    refresh();
	pthread_mutex_unlock(&graphicMutex);


    return EXIT_SUCCESS;
}

