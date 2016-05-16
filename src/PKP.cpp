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

    //Initialize ncurses
    if((mainwin = initscr()) == NULL) {
		fprintf(stderr, "Error initialising ncurses.\n");
		exit(EXIT_FAILURE);
    }

    //check if colors are supported by console
    if(FALSE == has_colors())
    	exit(EXIT_FAILURE);

    //dont show user input
    cbreak();
    noecho();

    //disable cursor
    curs_set(0);

    //getch will now signal when key is not pressed instead of waiting
    nodelay(stdscr, TRUE);

    //allow colors
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);

    //title
    mvaddstr(0, COLS/2, "PKP");
    refresh();

    //initialize static graphic mutex
	pthread_mutex_init(&graphicMutex, NULL);

	//initialize objects
	SignalLight* signalLight = new SignalLight();
	Queue* que = new Queue();
	Platforms* platforms = new Platforms(signalLight, que);
	Booths* booths = new Booths(platforms, que);

	int pressedKey;

	do{
		//getch will refresh window even if input is disabled
		//so it need to be locked
		Graphics::graphicLock();
		pressedKey = getch();
		Graphics::graphicUnlock();

		switch(pressedKey)
		{
		//spacja dodanie ludzi do kolejki
		case 32:
			que->addPeople();
			break;
		//+ dodanie budki z biletami
		case 43:
			booths->addBooth();
			break;
		//- usuniecie budki z biletami
		case 45:
			booths->removeBooth();
			break;
		// q dodanie pierwszy pociag od lewej
		case 113:
			platforms->addTrain(3);
			break;
		// a usuniecie pierwszy pociag od lewej
		case 97:
			platforms->removeTrain(3);
			break;
		// w dodanie drugi pociag od lewej
		case 119:
			platforms->addTrain(2);
			break;
		// s usuniecie drugi pociag od lewej
		case 115:
			platforms->removeTrain(2);
			break;
		// e dodanie trzeci pociag od lewej
		case 101:
			platforms->addTrain(1);
			break;
		// d usuniecie trzeci pociag od lewej
		case 100:
			platforms->removeTrain(1);
			break;
		// r dodanie czwarty pociag od lewej
		case 114:
			platforms->addTrain(0);
			break;
		// f usuniecie czwarty pociag od lewej
		case 102:
			platforms->removeTrain(0);
			break;
		//enter zmiana swiatla
		case 10:
			signalLight->changeColor();
			break;
		}
	}while(pressedKey != 27 );

	//delete objects
	delete booths;
	delete platforms;
	delete que;
	delete signalLight;

	//delete static graphic mutex
	pthread_mutex_destroy(&graphicMutex);

	//delete main window
    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}

