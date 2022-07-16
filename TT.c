#include <ncurses.h>
#include <unistd.h>

WINDOW *createwin(int height, int width, int starty, int startx);
int main()
{
	int i=1,first=1, y,x,maxX,maxY,flag=1,startX,hit = 0,miss=0, startY, ch,ch2, y2 = 0, x2 = 147, y3 = 0, x3 = 10, left=1,right=0;
	char hitpos, point = ' ';
	WINDOW *newwin, *twowin, *threewin; //  new window pointers
	initscr(); // initialize the curses library
	cbreak(); // disable line buffering
	keypad(stdscr, TRUE); // enable keyboard mapping
	noecho(); // disable echoing of key presses
	timeout(1); // set a timeout period of 10ms, to remove blocking nature of getch() and player input so it 
	refresh(); // update the screen
	getmaxyx(stdscr, maxY, maxX); // get the number of rows and columns of the terminal window.
	// printf("maxY%d maxX%d", maxY, maxX);


	startX = (COLS - 3)/2; // set the starting x coordinate of the window.
	startY = (LINES - 3)/2; // set the starting y coordinate of the window. coordinates to be in the middle of the screen.
	 
	newwin = createwin(3,3,startY, startX); // create a new window for ball. (height, width, Y, X) of the window
	twowin = createwin(10,5, y2, x2); // create a new window for paddle. (height, width, Y, X) of the window
	threewin = createwin(10,5, y3, x3); // create a new window for paddle. (height, width, Y, X) of the window

	while(1){ // event loop

		
                
		refresh();	
		if (ch = getch()) // control input for Paddle A
		{
			switch(ch) // switching between actions based on the control input
				{   
					case KEY_DOWN: // if the key pressed is down, move the paddle down

						wborder(twowin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // clear the window
						wrefresh(twowin); // update the window passed as parameter to the function.
						delwin(twowin); // delete the window instance. deallocates memory assigned.
						twowin = createwin(10, 5, ++y2, x2); // re-create window at new coordinates.
						refresh(); // update the screen
						break;
					case KEY_UP:
						wborder(twowin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
						wrefresh(twowin);
						delwin(twowin);
						twowin = createwin(10, 5, --y2, x2);
						refresh();
						break;
					case KEY_F(1):
						return 0;
				}
		}
		if (ch2 = getch()) // control input for Paddle B
		{
			switch ((char)ch2) // w to move up and s to move down
			{
			case 's':

				wborder(threewin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
				wrefresh(threewin);
				delwin(threewin);
				threewin = createwin(10, 5, ++y3, x3);
				refresh();
				break;
			case 'w':
				wborder(threewin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
				wrefresh(threewin);
				delwin(threewin);
				threewin = createwin(10, 5, --y3, x3);
				refresh();
				break;


			}
		}
		if(startX == 14 && (startY - y3) <= 10 && (startY - y3)>=0) // logic for ball hitting paddle A
		{ 
			hitpos = 'l';
			hit = 1;
			miss = 0;
		}
		else if(startX <= 13){ // logic for ball missing at paddle A
			miss = 1;
			point = 'b';
			hit = 0;
		}

		else if(startX == 144 && (startY - y2) <= 10 && (startY- y2 )>= 0){ // logic for ball hitting paddle B
			hitpos = 'r';
			hit = 1;
			miss = 0;
		}
		else if(startX >= 147){ // logic for ball missing at paddle B
			miss = 1;
			hit = 0;
			point = 'a';
		}

		mvprintw(0,0,"hit %d miss %d hitpos %c point %c", hit, miss, hitpos, point); // debug the hit and miss values
		
		if (startX != 13 && flag) // ball movement logic
		{

			wborder(newwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                        wrefresh(newwin);
                        delwin(newwin);
			newwin = createwin(3, 3, startY,--startX);
			usleep(3000);
		}
		else{
			wborder(newwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
			wrefresh(newwin);
			delwin(newwin);
			newwin = createwin(3, 3, startY, ++startX);
			usleep(3000);
			flag = 0;
			if(startX == 144)
				flag = 1;
		}
		
		
	}
	getch(); 
	endwin(); // q
	return 0;
}

// function to create a new window
WINDOW *createwin(int height, int width, int starty, int startx) // funciton to create new window.
{
	WINDOW *mywin;
	mywin = newwin(height, width, starty, startx); // newwin is the curses function to create a new window.
	box(mywin, 0, 0); // create a boxed layout for the specified window
	wrefresh(mywin); // update the window passed as parameter to the function.
	return mywin; 
} 
