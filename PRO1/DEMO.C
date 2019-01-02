/* Comments are sparse.  Use TUTOR1.C -> TUTOR5.C to get started */

#include "pro.h"
#include "xglobals.h"
#include "vs.h"
#include "colors.h"
#include "mouse.h"
#include "video.h"
#include "keyboard.h"
#include "xcodes.h"
#include <conio.h>
#include <string.h>

void main(void);
int runmenu(unsigned int, unsigned int, int, int);
void attributes(void);
void mouse_message(void);
void chgmethod(void);
int makebackground(void);
int makemenu(char **, int, char *, char *);
void panel1(unsigned int);
void panel2(unsigned int);
void panel3(unsigned int);
void panel4(unsigned int);
void panel5(unsigned int);
void panel6(unsigned int);
void panel7(unsigned int);
void panel8(unsigned int);
void panel9(unsigned int);
void panel10(unsigned int);

/* miscellaneous global variables */
unsigned int window_handle[20];

/* A buffer for use by sprintf */
char buffer[4000];

/* Some menu selections I use in a sample menu */
char *menu[6] = {"Move a file", "Copy a file", "Delete a file", "Load a file", "Save a file", "Exit to DOS"};

void main()
{

	int count, a, b, c, d, ox, oy;
	unsigned int handle;

	/* Setting various global parameters */
	active_attr = lightgray + (black << 4);
	inactive_attr = lightgray + (black << 4);
	active_tile_attr = lightgreen + (black << 4);
	inactive_tile_attr = white + (black << 4);
	scroll_bars_on = NO_BARS;
	thumbwheels_on = NO_BARS;
	mouse_installed = kb_ismouse();
	method = DMA;
	snowfree = FALSE;

	printf("Change video modes at any time by pressing\n\
(A) ANSI, (B) BIOS, (S) snowfree DMA, (D) DMA.\n\n\
Press any key to continue.");chgmethod();

	/* initialize the WINDOW PRO */
	wn_init();

	/* turn off the cursor */
	wn_hidecur();

	/* make a background */
	window_handle[0] = makebackground();

	/* set up a menu window to use later on in the demo */
	window_handle[11] = makemenu(menu, 6, "Files Menu","\021ÄÙ = confirm");

	/* set up a window to display the copyright notice */
	window_handle[12] = wn_createw(25, 80, 15, 10, 1, 1, 5, 49, FALSE,
		HEAD_ON, NULL, "Press any key to continue");
	vs_clrvs(window_handle[12], 0, white, blue);
	vs_printf(window_handle[12], 0, white, blue,
" This has been a presentation of The WINDOW PRO\n\n\
              Seabreeze Software\n\n\
            Copyright (c) 1986-1988");

	/* Make the ten windows we use in big opening number */
	window_handle[1] = wn_createw(18,50,1,1,1,1,5,8,FALSE,
		HEAD_ON,NULL,NULL);
	vs_fillattr(window_handle[1], 0, 1, 1, 50, 18, white, blue);
	vs_puts(window_handle[1], 0, 3, 1, 3, white, blue, "The");
	vs_puts(window_handle[1], 0, 2, 3, 6, white, blue, "WINDOW");
	vs_puts(window_handle[1], 0, 3, 5, 3, white, blue, "PRO");
	for (count = 2; count <= 10; count++) {
		window_handle[count] = wn_copyw(window_handle[1]);
	}

	/* set the position of the top 4 windows in the opener */
	a = 4;
	for (count = 1; count <= 4; count++) {
		handle = window_handle[count];
		WDW->physical_x = a;
		WDW->physical_y = 2;

		a += 21;
	}

	/* set the position of the bottom 4 windows in the opener */
	a = 67;
	for (count = 6; count <= 9; count++) {
		handle = window_handle[count];
		WDW->physical_x = a;
		WDW->physical_y = 18;
		a -= 21;
	}

	/* set the position of the middle windows in the opener */
	handle = window_handle[10];
	WDW->physical_x = 4;
	WDW->physical_y = 10;
	handle = window_handle[5];
	WDW->physical_x = 67;
	WDW->physical_y = 10;


        /* Bring out each window onto the screen */
	for (count = 1; count <= 10; count++) {
		handle = window_handle[count];
		wn_flybox(physical_columns/2, physical_rows/2, 1, 1,
			WDW->physical_x, WDW->physical_y, WDW->port_rows,
			WDW->port_columns, 10, 50, box4, black, black);
		wn_openw(window_handle[count]);
		if (kbhit()) chgmethod();
	}

	/* start distinguishing between the active and inactive windows */
	active_attr = white + (black << 4);

	/* Move each one to center stage, and blow it up */
	for (count = 1; count <= 10; count++) {
		/* lets us use the WDW macro */
		handle = window_handle[count];

		/* bring it to the top of the windows */
		wn_openw(handle);

		/* remember the original column position */
		ox = a = WDW->physical_x;

		/* move it to the center columns */
		while (a != 36) {
			if (a < 36) a++;
			else a--;
			wn_locatew(handle, a, WDW->physical_y);
			if (kbhit()) chgmethod();
		}

		handle = window_handle[count];

		/* remember the original row position */
		oy = a = WDW->physical_y;

		/* move it to the center rows */
		while (a != 10) {
			if (a < 10) a++;
			else a--;
			wn_locatew(handle, WDW->physical_x, a);
			if (kbhit()) chgmethod();
		}

		/* change the window background to red */
		vs_clrvs(handle, 0, white, red);


		/* move it up and to the left, so we can increase its size */
		for (a = 0; a < 6; a++) {
			wn_movew(handle, -3, -1);
			if (kbhit()) chgmethod();
		}

		/* increase its size */
		for (a = 0; a < 6; a++) {
			wn_sizet(handle, 0, 6, 2);
			if (kbhit()) chgmethod();
		}

		/* change the window name */
		wn_namet(handle, 0, "Press any key to continue");

		/* Each window is used to show off a different feature */
		switch (count) {
			case 1 : panel1(handle);
				 break;
			case 2 : panel2(handle);
				 break;
			case 3 : panel3(handle);
				 break;
			case 4 : panel4(handle);
				 break;
			case 5 : panel5(handle);
				 break;	
			case 6 : panel6(handle);
				 break;
			case 7 : panel7(handle);	
				 break;
			case 8 : panel8(handle);
				 break;
			case 9 : panel9(handle);
				break;
			case 10: panel10(handle);
		}

		/* get rid of the window name */
		wn_namet(handle, 0,NULL);


		/* shrink it back down */
		for (a = 0; a < 6; a++) {
			wn_sizet(handle, 0, -6, -2);
		}

		/* move it back to the center */
		for (a = 0; a < 6; a++) {
			wn_movew(handle, 3, 1);
			if (kbhit()) chgmethod();
		}

		/* move it back to its original row position */
		a = WDW->physical_y;
		while (a != oy) {
			if (a < oy) a++;
			else a--;
			wn_locatew(handle, WDW->physical_x, a);
			if (kbhit()) chgmethod();
		}

		/* move it back to its original column position */
		a = WDW->physical_x;
		while (a != ox) {
			if (a < ox) a++;
			else a--;
			wn_locatew(handle, a, WDW->physical_y);
			if (kbhit()) chgmethod();
		}
        }

	/* display the copyright notice */
	wn_openw(window_handle[12]);
	chgmethod();

	/* close each window */
	for (count = 1; count <=10; count++) {
		handle = window_handle[count];
		a = WDW->physical_x;
		b = WDW->physical_y;
		c = WDW->port_rows;
		d = WDW->port_columns;
		wn_delw(handle);
		wn_flybox(a, b, c, d, physical_columns / 2,
			physical_rows / 2, 1, 1, 10, 50, box4, black,
			black);
		if (kbhit()) chgmethod();
	}
	wn_delw(window_handle[12]);
	wn_delw(window_handle[11]);
	wn_delw(0);

	/* restore the background screen */
        wn_restorescr();

	/* restore the cursor position */
	v_gotoxy(oldx,oldy);

	/* restore the cursor shape */
	v_curshape(oldb, olde);
}


/* sets up a window to use as the backdrop for the entire demo */
int makebackground()
{
	unsigned int handle;
	unsigned char tile_handle = 0;

	handle = wn_createw(physical_rows, physical_columns, 1, 1, 1, 1,
		physical_rows - 2, physical_columns - 2, FALSE, NONE, NULL,
		NULL);
	vs_fillchar(handle, 0, 1, 1, TILE->vs_columns, TILE->vs_rows, '°',
		white, green);
	wn_openw(handle);
	return(handle);
}

/* display the introduction */
void panel1(handle)
unsigned int handle;
{
	wn_suspendw(handle);
	/* format the string */
	vs_printf(handle,0,white,red,
"\n\n               The WINDOW PRO\n\n\
                 version 1.4\n\n\
  Copyright (c) 1986, 1987 by Kenneth Stott\n\n\n\
              Seabreeze Software\n\
         397 Dal-Rich Village Suite 169\n\
           Richardson, Texas 75080\n\n\
                (214) 437-2729");

	/* flash the window contents onto the screen */
	wn_suspendw(handle);
	chgmethod();

	/* output trailer message */
	vs_clrvs(handle, 0, white, blue);
	vs_puts(handle, 0, 3, 1, 3, white, blue, "The");
	vs_puts(handle, 0, 2, 3, 6, white, blue, "WINDOW");
	vs_puts(handle, 0, 3, 5, 3, white, blue, "PRO");
}


/*
 * this routine outputs two different messages -- depending on whether
 * a mouse is or isn't installed
*/

void mouse_message()
{
	int aa;
	unsigned int handle;
	unsigned char *db;

	aa = active_attr;
	db = default_box;

	active_attr = lightgray + (black << 4);
	default_box = box0;
	
	/* create the window */
	handle = wn_createw(7,44,19,8,1,1,7,44,FALSE,HEAD_ON,NULL,NULL);	
	
	/* fill it with color */
	vs_fillattr(handle, 0, 1, 1, 44, 7, white, blue);

	/* select the appropriate message */	
	if (mouse_installed) sprintf(buffer,
"Since you've got a mouse, you can also\n\
try out the WINDOW PRO mouse support\n\
in this next example...\n\n\
Press any key to continue");
	else sprintf(buffer,
"Too bad you don't have a mouse installed.\n\
The WINDOW PRO has excellent mouse\n\
support for this next example...\n\n\
Press any key to continue");

	/* output it to the window */
	wn_suspendw(handle);	
	vs_format(handle, 0, white, blue, buffer);
	wn_suspendw(handle);

	/* display the window */
	wn_openw(handle);

	/* wait for a response */
	chgmethod();
	
	/* remove the window */
	wn_delw(handle);

	/* restore the global variables */
	active_attr = aa;
	default_box = db;
}

void panel2(handle)
unsigned int handle;
{	

	int aa;

        /* format the string */
	sprintf(buffer,
"\n\
The WINDOW PRO is a\n\n\
       * fast,\n\
       * compact, and\n\
       * feature-packed,\n\n\
virtual screen manager that lets you create\n\
programs that look and feel like\n\n\
       * Framework,\n\
       * Lotus,\n\
       * dBase III, and\n\
       * other top-sellers.");

	/* output it to the window */
	wn_suspendw(handle);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);	
	chgmethod();

	/* format another string */	
	sprintf(buffer,
"You can quickly implement complex\n\n\
       * dialog boxes,\n\
       * context sensitive help,\n\
       * pop-up, and\n\
       * pull-down menus,\n\n\
The following was created completely with\n\
The WINDOW PRO.  No tricks-- just\n\
straight-forward WINDOW PRO functions.");

	/* clear the window and output new message */
	wn_suspendw(handle);
	vs_clrvs(handle, 0, white, red);
	vs_locatecur(handle, 0, 1, 1);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);	
	chgmethod();

	/* set the attributes */
	 aa = active_attr;
	 active_attr = white + (blue << 4);
	 active_tile_attr = yellow + (blue << 4);

	/* display the mouse message */
	mouse_message();

	/* display the menu */
	runmenu(window_handle[11], 1, 30, 5);

	/* restore active attribute to original value */
	active_attr = aa;

	/* output trailer message */
	vs_clrvs(handle, 0, white, green);
	vs_locatecur(handle, 0, 1, 1);
	sprintf(buffer,
"Complex\n\
Windows\n\n\
 Mouse\n\
Support\n");
	vs_format(handle, 0, white, green, buffer);
}


int makemenu(menu_choices, number_choices, name, help)
char **menu_choices, *name, *help;
int number_choices;
{
	unsigned int handle;
	unsigned char tile_handle, th[3];
	int maxwidth = 0, count, width, ita, namewidth, helpwidth;
	unsigned char *db;

	/* save the values of these global variables */
	db = default_box;
	ita = inactive_tile_attr;

	/* then change them to what we need */
	default_box =box3;
	inactive_tile_attr = yellow + (blue << 4);

        /* determine the width of the menu */
	for (count = 0; count < number_choices; count++) {
		width = strlen(menu_choices[count]) + 3;
		if (width > maxwidth) maxwidth = width;
	}

	namewidth = strlen(name);
	if (namewidth > maxwidth) maxwidth = namewidth;

	helpwidth = strlen(help);
	if (helpwidth > maxwidth) maxwidth = helpwidth;

	/* Make the window that will hold the menu */
	handle = wn_createw(number_choices + 4, maxwidth, 1, 1, 1, 1,
		number_choices + 4, maxwidth, FALSE, HEAD_ON, NULL, NULL);

	/* activate the tile in the window */
	th[0] = 0;
	wn_actt(handle,th[0]);

	/* make a second tile and put it in the window */
	th[1] = wn_createt(handle, NULL, maxwidth, number_choices + 4, 1, 1);
	wn_openabst(handle, th[1], 1);

	/* make a third tile and put it in the window */
	th[2] = wn_createt(handle, NULL, maxwidth, number_choices + 4, 1, 1);
	tile_handle = th[0];
	wn_openabst(handle, th[2], TILE->port_rows - 2);

	/* fill the tiles with color */
	vs_fillattr(handle, th[0], 1, 1, maxwidth, 1, yellow, blue);
	vs_fillattr(handle, th[1], 1, 1, maxwidth, 1, yellow, blue);
	vs_fillattr(handle, th[2], 1, 1, maxwidth, number_choices, green, black);

	/* put the strings in the top and bottom tiles */
	vs_puts(handle, th[0],1 + ((maxwidth - namewidth) / 2), 1, namewidth,
		yellow, blue, name);
	vs_puts(handle, th[1],1 + ((maxwidth - helpwidth) / 2), 1, helpwidth,
		yellow, blue, help);

	/* put the strings in the center tile */
	for (count = 0; count < number_choices; count++) {
		 vs_puts(handle, th[2], 3, 1 + count, maxwidth - 3, green,
			black, menu_choices[count]);
	}

	/* put the scroll bars on the center tile */
	wn_togscroll(handle, th[2], BOTH_BARS);
	wn_togthumb(handle, th[2], NO_BARS);

	/* reset the gobal variables back to their original values */
	inactive_tile_attr = ita;
	default_box = db;

	return(handle);
}

#define LOCATE		1

int runmenu(handle, default_choice, x1, y1)
unsigned int handle;
unsigned int default_choice;
int x1, y1;

{
	int curr_choice, cb, ce, button_event, new_location, event, co, timeout;
	unsigned int x, y, mx, my;
	unsigned char tile_handle;

        /* position and open the menu on the screen */
	wn_locatew(handle, x1, y1);
	wn_openw(handle);

	/* highlight default choice */
	curr_choice = default_choice;

	/* initialize event */
	event  = 0;

	/* change the cursor size */
	cb = cursor_b;
	ce = cursor_e;
	co = cursor_on;
	cursor_b = 0;
	cursor_e = 15;

	/* display the cursor */
	wn_showcur();
	if (mouse_installed) kb_showmouse();

	/* set tile handle to center tile */
	tile_handle = WDW->tiles[WDW->first_tile]->forward;

	/* set the center tile as the active tile */
	wn_actt(handle, tile_handle);

	/* forces highlighting of default choice */
	TILE->cursor_y = 0;
	timeout = 15;

	/* command loop */
	while (event != XENTER) {

		/* reset the event */
		event = 0;

		/* reset new_location */
		new_location = curr_choice;

		/* put the cursor on the current item */
		if (TILE->cursor_y != curr_choice) {
			vs_locatecur(handle, tile_handle, 1, curr_choice);
			if (mouse_installed) kb_hidemouse();
			vs_fillattr(handle, tile_handle, 1, curr_choice,
				WDW->port_columns, curr_choice, black, lightgray);
			if(mouse_installed) kb_showmouse();
		}

		/* if there is a key in the buffer get it */
		if (kbhit()) {
			event = kb_getxc();
		}

		else if (mouse_installed) {

			button_event = kb_mouseclicks(1, timeout, &mx, &my);

			/* convert mouse coordinates to physical screen coordinates */
			x = mx;
			y = my;
			kb_convertcoords(&x,&y);

			/*
			 * if it is a click in the active tile then set a to point
			 * to new row to highlight  and set event to indicate mouse event
			 * if a DOUBECLICK exit.
			*/

			/* these three button events translate into actions */
			if ((button_event == CLICK) ||
			    (button_event == DOUBLECLICK) ||
			    (button_event == HOLDING)) {

				/*
				 * clicking in a location or holding and
				 * positioning the cursor moves the selected
				 * item.  double-clicking on an item selects
				 * it and confirms
				*/
				if (wn_isonvs(handle, tile_handle, &x, &y)) {
					new_location = y;
					if ((button_event == CLICK) ||
					    (button_event == HOLDING))
						event = LOCATE;
					else event = XENTER;
					}

				/*
				 * doing any of these things on a scroll bar
				 * is the the same as hitting the up or down
				 * key
				*/
				if ((wn_isonsbd(handle, tile_handle, x, y)) ||
				    (wn_isonsbr(handle, tile_handle, x, y))) {
					event = XDOWN;
				}
				if ((wn_isonsbu(handle, tile_handle, x, y)) ||
				    (wn_isonsbl(handle, tile_handle, x, y))) {
					event = XUP;
				}
				if ((wn_isonvs(handle, WDW->last_tile, &x, &y)) &&
				    (button_event == CLICK)) {
					event = XENTER;
				}

			}

			/*
			 * if it is a button press then lower timeout rate
			 * to speed up scrolling rate
			*/
			if (button_event == PRESS) {

				/* use maximum sampling rate if dragging a selection */
				if (wn_isonvs(handle,
					WDW->tiles[WDW->first_tile]->forward,
					&x, &y)) timeout = -1;

				/* use a little slower sampling rate if in the scroll bar area */
				else if (
					(wn_isonvrbar(handle,
					WDW->tiles[WDW->first_tile]->forward,
					x, y)) ||
					(wn_isonhbar(handle,
					WDW->tiles[WDW->first_tile]->forward,
					x, y))) timeout = 2;
			}

			/*
			 * If the user releases the button then up time out
			 * rate to something suitable for clicking
			*/
			if (button_event == RELEASE) timeout = 10;
		}

		/* if there is an event .... */
		if (event != 0) {

			/* interpret the event into a new current item */
			if ((event == XUP) || (event == XLEFT)) curr_choice--;
			if ((event == XDOWN) || (event == XRIGHT)) curr_choice++;
			if (event == XHOME) curr_choice = 1;
			if (event == XEND) curr_choice = 6;
			if ((event == LOCATE) || (event == XENTER)) {
				curr_choice = new_location;
			}

			/* check for wrap around */
			if (curr_choice < 1) curr_choice = TILE->port_rows;
			if (curr_choice > TILE->port_rows) curr_choice = 1;

			if (curr_choice != TILE->cursor_y) {

				/* de-highlight the current item */
				if (mouse_installed) kb_hidemouse();
				vs_fillattr(handle, tile_handle, 1, TILE->cursor_y,
					WDW->port_columns, TILE->cursor_y,
					green, black);
				if (mouse_installed) kb_showmouse();
			}
		}
	}

	/* reset cursor size */
	cursor_b = cb;
	cursor_e = ce;
	if (mouse_installed) kb_hidemouse();

	/* close the window */
	wn_closew(handle);

	/* reset the cursor */
	if (!co) wn_hidecur();

	/* return results */
	return(curr_choice);
}

void panel3(handle)
unsigned int handle;
{
	int key = 0, x, y;

	/* format a string */
	sprintf(buffer,
"The WINDOW PRO is a\n\n\
          * virtual screen manager.\n\n\
Virtual screens are the basis of most\n\
editors, providing the support for\n\n\
          * horizontal scrolling, and\n\
          * windowing.\n\n\
Let me give you an example. I'll shrink\n\
this window, and you pan through it with\n\
the arrow keys.  I'll also activate scroll\n\
bars (with a simple function call) to\n\
remind the user of what keys to use.");

	/* output to window */
	wn_suspendw(handle);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	chgmethod();

	/* shrink it down and put on scroll bars and a message */
	wn_sizet(handle, 0, -10, -10);
	wn_togscroll(handle, 0, BOTH_BARS);
	wn_togthumb(handle, 0, BOTH_BARS);
	wn_namet(handle, 0, "Press ENTER to continue");

	/* stay in command loop until ENTER is pressed */
	while (key != XENTER) {
		/* get the keypress */
		key = kb_getxc();

		/* set scroll indicators to 0 */
		x = y = 0;

		/* interpret each keypress into scrolling values */
		switch (key) {
			case XUP   : y = -1;
				    break;
			case XDOWN : y = 1;
				    break;
			case XLEFT : x = -1;
				    break;
			case XRIGHT: x = 1;
				    break;
			case XHOME : wn_locatevs(handle, 0, 1, 1);
				    break;
			case XEND  : wn_locatevs(handle, 0, 100, 100);
				    break;
			}

		/* scroll the virtual screen */
		wn_scrollvs(handle, 0, x, y);
		wn_sync_tw_to_vs(handle, 0);
		}

	/* expand it back out again, change the message & turn off scroll bars */
	wn_sizet(handle, 0, 10, 10);
	wn_namet(handle, 0, "Press any key to continue");
	wn_togscroll(handle, 0, NO_BARS);
	wn_togthumb(handle, 0, NO_BARS);

	/* set the virtual screen to the top left corner */
	wn_locatevs(handle, 0, 1, 1);

	/* output trailer message */
	vs_clrvs(handle, 0, white, magenta);
	vs_locatecur(handle, 0, 1, 1);
	sprintf(buffer,
"Virtual\n\
Screens\n\n\
Scroll\n\
Bars");
	vs_format(handle, 0, white, magenta, buffer);
}

void panel4(handle)
unsigned int handle;
{
        unsigned int mhandle, timer;
        int count;

	/* print the basic text */
	sprintf(buffer,
"The WINDOW PRO is easy to use.  It\n\
has a windows-like printf that works\n\
just like regular printf but adds\n\
some extras like color support.\n\n\
Watch I'll count to 10 like this:\n\n\
for (count = 1; count <= 10; count++)\n\
  vs_printf(wdw,tile,fgcolor, bgcolor,\n\
  \042count %%d\\n\042,count);\n\n");
	wn_suspendw(handle);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	chgmethod();

	/* set up a window to count in  and open it */
	mhandle = wn_createw(15, 20, 29, 5, 1, 1, 15, 20, FALSE, HEAD_ON,
		"vs_printf","Press any key");
	wn_namet(handle, 0, NULL);
	wn_openw(mhandle);

	/* print a little message */
	sprintf(buffer,"First slowly...\n\n");
	vs_format(mhandle, 0, white, red, buffer);

	/*
	 * count from one to ten -- slowly
	*/
	for (count = 1; count <= 10; count++) {
		sprintf(buffer,"count %d.\n",count);
		vs_format(mhandle, 0, green, black, buffer);
		for (timer = 0; timer < (unsigned int) 50000; timer++);
	}
	chgmethod();

	/* clear the window */
	vs_clrvs(mhandle, 0, white, black);
	vs_locatecur(mhandle, 0, 1, 1);

	/* print a little message */
	sprintf(buffer,"And now quickly....\n\n");
	vs_format(mhandle, 0, white, red, buffer);

	/* count fast */
	for (count = 1; count <= 10; count++) {
		sprintf(buffer,"count %d.\n",count);
		vs_format(mhandle, 0, yellow, black, buffer);
	}
	chgmethod();

	/* get rid of the counting window */
	wn_delw(mhandle);

	/* format a string */
	sprintf(buffer,
"The WINDOW PRO also supports a windows-like\n\
gets.  It works the same as the gets that\n\
you're used to but adds support for color\n\
and scrolling.  Watch how vs_gets works.");

	/* clear the window and output the string */
	wn_suspendw(handle);
	vs_clrvs(handle, 0, white, red);
	vs_locatecur(handle, 0, 1, 1);
	vs_format(handle, 0, white, red, buffer);
	wn_namet(handle, 0, "Press any key to continue");
	wn_suspendw(handle);
	chgmethod();

	/* turn off the window name */
	wn_namet(handle, 0, NULL);

	/* set up a new window for demonstrating vs_gets */
	mhandle = wn_createw(3, 45, 29, 5, 1, 1, 2, 35, FALSE, HEAD_ON,
		"vs_gets --- scrolling ON","Press ENTER to terminate vs_gets");

	/* clear the window */
	vs_clrvs(mhandle, 0, white, blue);

	/* display the window */
	wn_openw(mhandle);

	/* turn on the cursor */
	wn_showcur();

	/* use vs_gets */
	vs_gets(mhandle, 0, TRUE, buffer, white, blue, 200);

	/* turn off the cursor */
	wn_hidecur();

	/* change the window name */
	wn_namet(mhandle, 0, "Press any key to continue");
	chgmethod();

	/* suspend the window while we fix a few things */
	wn_suspendw(mhandle);

	/* change the window name */
	wn_namew(mhandle, "vs_gets --- scrolling OFF");

	/* change the name on the bottom of the window */
	wn_namet(mhandle, 0, "Press ENTER to terminate vs_gets");

	/* erase everything in the window */
	vs_clrvs(mhandle, 0, white, blue);

	/*
	 * set the upper left corner of the window = to the upper left
	 * corner of the virtual screen
	*/
	wn_locatevs(mhandle, 0, 1, 1);

	/* reset the cursor position */
	vs_locatecur(mhandle, 0, 1, 1);

	/* turn on the cursor */
	wn_showcur();

	/* flash the results of the above to the screen */
	wn_suspendw(mhandle);

	/* demonstrate vs_gets without scrolling */
	vs_gets(mhandle, 0, FALSE, buffer, white, blue, 200);

	/* turn off the cursor */
	wn_hidecur();

	/* change the name of the window */
	wn_namet(mhandle, 0, "Press any key to continue");
	chgmethod();

	/* get rid of the demonstration window */
	wn_delw(mhandle);

	/* output the trailer message */
	vs_clrvs(handle, 0, white, brown);
	vs_locatecur(handle, 0, 1, 1);
	sprintf(buffer,
"  Easy\n\n\
   to\n\n\
   use");
	vs_format(handle, 0, white, brown, buffer);
}

void panel5(handle)
unsigned int handle;
{
	unsigned int mhandle, count, b;

	/* format a string */
	sprintf(buffer,
"The WINDOW PRO uses 3 screen update methods:\n\n\
          * DMA,\n\
          * BIOS, and\n\
          * ANSI.\n\n\
Each is available at runtime.  You can even\n\
switch in mid-application.\n\n\
These features give your products a\n\n\
          * wider customer base,\n\
          * reduce hardware dependence, and\n\
          * provide a built-in approach to\n\
            user customization.");

	/* output a string */
	wn_suspendw(handle);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	chgmethod();

	/* format another string */
	sprintf(buffer,
"More specifically\n\n\
** DMA is fast, but causes snow on some\n\
   old CGA cards, and is ill-behaved by\n\
   MS-WINDOWS' and DESQVIEW's standards.\n\n\
** BIOS makes your programs compatible with\n\
   MS-WINDOWS and DESQVIEW.\n\n\
** ANSI makes you programs more hardware\n\
   independent, running from remote\n\
   terminals, on DEC PC's, and other\n\
   equipment is very feasible.  You can even\n\
   modify the command sequences to support\n\
   additional equipment.");

	/* clear the screen and output the string */
	wn_suspendw(handle);
	vs_clrvs(handle, 0, white, red);
	vs_locatecur(handle, 0, 1, 1);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	chgmethod();

	/* format another string */
	sprintf(buffer,
"See what kind of performance difference\n\
you can detect.  I'll count to ten again.\n\
First, I'll use the DMA approach and then\n\
I'll use the BIOS method.\n\n\n");

	/* output the string */
	wn_suspendw(handle);
	vs_clrvs(handle, 0, white, red);
	vs_locatecur(handle, 0, 1, 1);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	chgmethod();

	b = method;

	/* set up a window to count in  and open it */
	mhandle = wn_createw(15, 20, 29, 5, 1, 1, 15, 20, FALSE, HEAD_ON,
		"DMA updating","Press any key");
	wn_namet(handle, 0, NULL);
	wn_openw(mhandle);

	method = DMA;

	/* count */
	for (count = 1; count <= 10; count++) {
		sprintf(buffer,"count %d.\n",count);
		vs_format(mhandle, 0, red, black, buffer);
	}
	chgmethod();

	/* clear the window */
	vs_clrvs(mhandle, 0, white, black);
	vs_locatecur(mhandle, 0, 1, 1);

	/* change the window name */
	wn_namew(mhandle, "BIOS updating");

	/* change to the BIOS update method */
	method = BIOS;

	/* count */
	for (count = 1; count <= 10; count++) {
		sprintf(buffer,"count %d.\n",count);
		vs_format(mhandle, 0, magenta, black, buffer);
	}
	chgmethod();

	/* change back to default updating */
	method = b;

	/* get rid of the window */
	wn_delw(mhandle);

	/* output the trailer message */
	vs_clrvs(handle, 0, white, black);
	vs_locatecur(handle, 0, 1, 1);
	sprintf(buffer,
"  BIOS\n\n\
  DMA\n\n\
  ANSI");
	vs_format(handle, 0, white, black, buffer);
}

void panel6(handle)
unsigned int handle;
{
	/* format a string */
	sprintf(buffer,
"The WINDOW PRO provides complete\n\
control over colors...\n\n");

	/* output the string */
	wn_suspendw(handle);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	chgmethod();

	/* display the attributes window */
	attributes();

	/* output the string */
	wn_suspendw(handle);
	vs_clrvs(handle, 0, white, red);
	vs_locatecur(handle, 0, 1, 1);
	vs_format(handle, 0, white, red,
"The WINDOW PRO uses logical colors.  No\n\
matter how you write your programs The\n\
WINDOW PRO stores the actual attribute\n\
values in a single location.  This \n\n\
     * Lets you easily give your\n\
       end-users customizable color\n\
       schemes (like BORLAND and\n\
       MICROSOFT products,) and\n\n");

	vs_format(handle, 0, white, red,
"     * Makes porting applications\n\
       simpler.  You can create color\n\
       keys for several terminals and,\n\
       video boards, making your\n\
       application look consistent on\n\
       all hardware.");

	wn_suspendw(handle);
	chgmethod();

	/* output the trailer message */
	vs_clrvs(handle, 0, yellow, black);
	vs_locatecur(handle, 0, 1, 1);
	sprintf(buffer,
" Custom\n\n\
 Color\n\n\
 Support");
	vs_format(handle, 0, yellow, black, buffer);


}

void attributes()
{

	unsigned int window_handle, count1, count2;
	char *bg = "Background||v    ";

	/* set up ta window to display the attributes in */
	window_handle = wn_createw(25, 80, 35, 2, 1, 1, 20, 20, FALSE,
		HEAD_ON, "Video Attributes", NULL);

	/* position the cursor */
	vs_locatecur(window_handle,0,2,1);

	/* output the horizontal titles */
	vs_format(window_handle, 0, white, black, "Foreground-->");
	vs_locatecur(window_handle,0,4,3);
	for (count1 = 0; count1 < 16; count1++) {
		sprintf(buffer, "%X", count1);
		vs_format(window_handle, 0, white, black, buffer);
	}

	/* output the rest line by line */
	for (count1 = 0; count1 < 16; count1++) {

		/* output the vertical title */
		vs_locatecur(window_handle, 0, 1, count1+4);
		sprintf(buffer, "%c %X", bg[count1], count1);
		vs_format(window_handle, 0, white, black, buffer);
		
		/* output the attribute display for the current line */
		for (count2 = 0; count2 < 16; count2++) {
			vs_putc(window_handle, 0, count2 + 4, count1 + 4, count2, count1, 'x');
		}
	}
	
	/* display the window */
	wn_openw(window_handle);
 	chgmethod();

	/* get rid of the window */
 	wn_delw(window_handle);
}

void panel7(handle)
unsigned int handle;
{
        unsigned char th[3];
	int event = 0;
	
	th[0] = 0;
	active_tile_attr = lightgreen + (black << 4);
	inactive_tile_attr = white + (black << 4);

	/* format a string */
	sprintf(buffer,
"The WINDOW PRO lets you associate several\n\
virtual screens with a single window.  You\n\
can\n\n\
        * split windows and display\n\
          multiple virtual screens in\n\
          in a single split-window\n\
        * swap virtual screens in and out\n\
        * and change the sizes of split\n\
          window areas (we call them tiles)\n\n\
This is the basis for things like segmented\n\
pull-down menus, and other sophisticated\n\
screen effects.\n\n\
Watch this example.");

	/* output the string */
	wn_suspendw(handle);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	chgmethod();

	/* change the tile name */
	wn_namet(handle, th[0], "first virtual screen");

	/* create a second tile */
	th[1] = wn_createt(handle, "second virtual screen", 80, 25, 1, 1);

	/* fill in the second tile with color */
	vs_clrvs(handle, th[1], white, green);

	/* format a string and output it to the second tile */
	sprintf(buffer,
"This is a second virtual screen.  It is\n\
completely independent of the first\n\
virtual screen.\n\n\
-- Pan using the arrow keys\n\
-- Swap virtual screens HOME\n\
-- Switch virtual screens END\n\
-- Size using PgUp/PgDn\n\
-- ENTER to continue");

	wn_suspendw(handle);
	vs_format(handle, th[1], white, green, buffer);

	/* display the second tile */
	wn_opent(handle, th[1]);

	/* make the second tile a little bigger */
	wn_sizet(handle, th[0], 0, -3);

	/* make the second tile the active tile */
	wn_actt(handle, th[1]);

	/* turn on the scroll bars */
	wn_togscroll(handle, th[1], BOTH_BARS);

	/* flash all changes to the screen */
	wn_suspendw(handle);

	/* main command loop: exits on pressing ENTER */
	while (event != XENTER) {

		/* get keystroke */
		event = kb_getxc();

		/* select an action */
		switch (event) {
			case XUP 	: wn_scrollvs(handle, WDW->active_tile, 0, -1);
				  	break;
			case XDOWN 	: wn_scrollvs(handle, WDW->active_tile, 0, 1);
					break;
			case XLEFT	: wn_scrollvs(handle, WDW->active_tile, -1, 0);
					break;
			case XRIGHT	: wn_scrollvs(handle, WDW->active_tile, 1, 0);
					break;
			case XPGUP	: wn_sizet(handle, WDW->first_tile, 0, -1);
					break;
			case XPGDN	: wn_sizet(handle, WDW->first_tile, 0, 1);
					break;
			case XHOME	: wn_swapt(handle, th[0], handle, th[1]);
					  event = XEND;
			case XEND	: if (WDW->active_tile == th[0]) {
						wn_suspendw(handle);
						wn_togscroll(handle, th[0], NO_BARS);
						wn_togscroll(handle, th[1], BOTH_BARS);
						wn_actt(handle, th[1]);
						wn_suspendw(handle);
					}
					else {
						wn_suspendw(handle);
						wn_togscroll(handle, th[1], NO_BARS);
						wn_togscroll(handle, th[0], BOTH_BARS);
						wn_actt(handle, th[0]);
						wn_suspendw(handle);
					}
					break;
		}
	}

	/* close up the second tile */
	wn_closet(handle, th[1]);

	/* turn off the scroll bars */
	wn_togscroll(handle, th[0], NO_BARS);

	/* output the trailer message */
	vs_clrvs(handle, th[0], black, red);
	wn_locatevs(handle, th[0], 1, 1);
	vs_locatecur(handle, th[0], 1, 1);
	sprintf(buffer,"\n\n Tiles");
	vs_format(handle, th[0], black, red, buffer);
}

void panel8(handle)
unsigned int handle;
{
	unsigned int mhandle;
	unsigned char th;

	/* format a string */
	sprintf(buffer,
"The WINDOW PRO gives you complete control\n\
over\n\n\
         * border characters, and\n\
         * border styles.\n\n\
Border characters are up to you.  You can\n\
use any of the several built-in sets of\n\
border characters, or create your own.\n\n\
Border styles let you create shadowing\n\
effects.\n\n\
Look at the following example for an idea\n\
of the flexibility of The WINDOW PRO.");

	/* output the string */
	wn_suspendw(handle);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	chgmethod();

	/* setup a window to demonstrate border stuff */
	mhandle = wn_createw(25, 80, 29, 5, 1, 1, 12, 25, FALSE, HEAD_ON,
		"BORDER CHARACTERS",NULL);

	/* create a second tile -- to show the full effect of certain changes */
	th = wn_createt(mhandle, "Press any key", 80, 25, 1, 1);

	/* fill both tiles with color */
	vs_clrvs(mhandle, 0, black, lightgray);
	vs_clrvs(mhandle, th, black, lightgray);

	/* display the second tile */
	wn_opent(mhandle, th);

	/* display the window */
	wn_openw(mhandle);

	/* display various border styles */
	wn_chgbord(mhandle, box1);
	chgmethod();
	wn_chgbord(mhandle, box2);
	chgmethod();
	wn_chgbord(mhandle, box3);
	chgmethod();
	wn_chgbord(mhandle, box4);
	chgmethod();
	sprintf(buffer,
"\n\n    Border Styles");
	vs_format(mhandle, 0, black, lightgray, buffer);
	wn_namet(mhandle, th, NULL);
	wn_namew(mhandle, NULL);
	wn_togborder(mhandle, UPPER_LEFT);
	chgmethod();
	wn_togborder(mhandle, UPPER_RIGHT);
	chgmethod();
	wn_togborder(mhandle, LOWER_RIGHT);
	chgmethod();
	wn_togborder(mhandle, LOWER_LEFT);
	chgmethod();
	wn_togborder(mhandle, NONE);
	chgmethod();
	wn_togborder(mhandle, HEAD_ON);
	wn_chgbord(mhandle, box0);
	chgmethod();

	/* get rid of the demonstration window */
	wn_delw(mhandle);

	/* output the trailer message */
	vs_clrvs(handle, 0, black, green);
	vs_locatecur(handle, 0, 1, 1);

	sprintf(buffer,
"Flexible\n\n\
 Border\n\n\
 Styles");
	vs_format(handle, 0, black, green, buffer);
}

void panel9(handle)
unsigned int handle;
{

	unsigned int mhandle[3];
	int count;

	sprintf(buffer,
"The WINDOW PRO provides several methods of\n\
controlling overlapping of windows\n\n\
First, some overlapping windows...");
	wn_suspendw(handle);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	chgmethod();

	for (count = 0; count < 3; count++) {
		mhandle[count] = wn_createw(25, 80, 20 + (count * 3),
			4 + (count * 3), 1, 1, 10, 15, FALSE, HEAD_ON,
			NULL,NULL);
		vs_clrvs(mhandle[count], 0, white, black + 3 + count);
		wn_openw(mhandle[count]);
	}
	chgmethod();

	sprintf(buffer,
"Popular programs like Framework & Symphony\n\
actually use several methods of manipulating\n\
overlapping windows like\n\n\
          * activation,\n\
          * hiding,\n\
          * opening, and\n\
          * closing.\n\n\
The differences are subtle but important.\n\
Particularly important when you commit to\n\
BRAND X and find out that the subtleties\n\
escaped you, the client wants changes made,\n\
BRAND X won't do it, and the deadline\n\
looms closer.  See if you can pick up on\n\
the differences.");

	wn_suspendw(handle);
	vs_clrvs(handle, 0, white, red);
	vs_locatecur(handle, 0, 1, 1);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	wn_actw(handle);
	chgmethod();

	sprintf(buffer,
"Activating a window temporarily brings it\n\
it to the top and reinserts the previously\n\
active window back into the stack at its\n\
original position.\n\n\
Watch what happens when a window is\n\
activated.  (For future reference, the\n\
bright bordered window is the active window,\n\
and there is always an active window on the\n\
screen.)");
	wn_suspendw(handle);
	vs_clrvs(handle, 0, white, red);
	vs_locatecur(handle, 0, 1, 1);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	chgmethod();
	wn_actw(mhandle[2]);
	chgmethod();

	for (count = 0; count < 2; count++) {
		wn_actw(mhandle[count]);
		chgmethod();
		wn_actw(mhandle[2]);
		chgmethod();
	}

	sprintf(buffer,
"Hiding a window supresses its display\n\
'Un-hiding' it reinserts it back into its\n\
original position in the stack\n\n\
Watch closely as I hide and un-hide each\n\
window.");
	wn_suspendw(handle);
	vs_clrvs(handle, 0, white, red);
	vs_locatecur(handle, 0, 1, 1);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	wn_actw(handle);
	chgmethod();
	wn_actw(mhandle[2]);
	chgmethod();

	for (count = 0; count < 3; count++) {
		wn_hidew(mhandle[count]);
		chgmethod();
		wn_hidew(mhandle[count]);
		if (count == 2) wn_actw(mhandle[count]);
		chgmethod();
	}

	sprintf(buffer,
"Opening a window places it permanently on\n\
top of the stack of windows.\n\n\
Closing a window removes it from the screen.\n\n\
Notice what happens as I close and open\n\
each window.");
	wn_suspendw(handle);
	vs_clrvs(handle, 0, white, red);
	vs_locatecur(handle, 0, 1, 1);
	vs_format(handle, 0, white, red, buffer);
	wn_suspendw(handle);
	wn_actw(handle);
	chgmethod();
	wn_actw(mhandle[2]);
	chgmethod();

	for (count = 2; count >= 0; count--) {
		wn_closew(mhandle[count]);
		chgmethod();
		wn_openw(mhandle[count]);
		chgmethod();
	}

	for (count = 0; count < 3 ; count++) wn_closew(mhandle[count]);

	vs_clrvs(handle, 0, red, black);
	vs_locatecur(handle, 0, 1, 1);

	sprintf(buffer,
"  Over\n\n\
 lapping\n\n\
 Windows");
	vs_format(handle, 0, red, black, buffer);
}

void panel10(handle)
unsigned int handle;
{
	wn_suspendw(handle);
	vs_format(handle, 0, white, red,
"The WINDOW PRO is distributed under the\n\
shareware marketing concept.  You are free\n\
to incorporate The WINDOW PRO shareware\n\
version into your applications programs and\n\
may distribute those programs royalty free.\n\n\
To get the full benefit of The WINDOW PRO,\n");

	vs_format(handle, 0, white, red,
"register with Seabreeze for updates and\n\
technical support. The shareware users\n\
manual contains additional information on\n\
registering, or you can contact:\n\n\
             Kenneth Stott\n\
          Seabreeze Software\n\
   397 Dal-Rich Village Suite 169\n\
      Richardson, Texas 75080\n\n\
          (214) 437-2729");

	wn_suspendw(handle);
	chgmethod();

	vs_clrvs(handle, 0, magenta, black);
	vs_locatecur(handle, 0, 1, 1);

	sprintf(buffer,
"\n\
 Share-\n\
  ware");
	vs_format(handle, 0, magenta, black, buffer);
}

void chgmethod()
{
	char a;

	a = getch();
	switch (upcase(a)) {
	case 'A' : method = ANSI;
		   break;
	case 'B' : method = BIOS;
		   break;
	case 'S' : method = DMA;
		   snowfree = TRUE;
		   break;
	case 'D' : method = DMA;
		   snowfree = FALSE;
		   break;
	}
}
