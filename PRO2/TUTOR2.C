#include "pro.h"
#include "xglobals.h"
#include "vs.h"
#include "colors.h"
#include "video.h"
#include <conio.h>


int main()
{
	unsigned int window_handle[3], count;

	/*
	 * See tutor1.c for an explanation of this section.
	*/
	
	scroll_bars_on = BOTH_BARS;
	active_attr = white + (black << 4);
	inactive_attr = lightgray + (black << 4);

	wn_init();

	/* Let's turn off the cursor -- its annoying */
	wn_hidecur();

	window_handle[0] = wn_createw(25,80,2,3,1,1,15,20,FALSE,HEAD_ON,"1",NULL);
	vs_puts(window_handle[0],0,1,1,10,white,blue,"Window Pro");
	wn_openw(window_handle[0]);
	getch();

	/*
	 * Now let's create a second window that overlaps the first
	 *
	*/

	window_handle[1] = wn_createw(25,80,5,5,1,1,15,20,FALSE,HEAD_ON,"2",NULL);
	vs_puts(window_handle[1],0,1,1,10,white,blue,"Window Pro");
	wn_openw(window_handle[1]);
	getch();


	/*
	 * Now let's create a third window that overlaps the second
	 *
	*/

	window_handle[2] = wn_createw(25,80,12,7,1,1,11,24,FALSE,HEAD_ON,"3",NULL);
	vs_puts(window_handle[2],0,1,1,10,white,blue,"Window Pro");
	wn_openw(window_handle[2]);
	getch();

	/*
	 * Now that we've got some windows on the screen let's look at some of the
	 * ways we can manipulate windows.
	*/


	/*
	 * Lesson 1: Closing and Opening windows
	 *
	 * Closing a window takes it off of the screen, but does not
	 * delete it from memory.  So, it we close window_handle[1] it
	 * should remove it from the screen.
	*/

	wn_closew(window_handle[1]);
	getch();

	/*
	 * But, when we bring it back it will be on top of the screen.
	*/

	wn_openw(window_handle[1]);
	getch();

	/*
	 * We can even open windows which are already on the screen to
	 * bring them to the top.  So, if we want to bring window 3 back
	 * to the top we can also open it.
	*/

	wn_openw(window_handle[2]);
	getch();

	/*
	 * Lesson 2: Hiding Windows
	 *
	 * Hiding is similar to closing, except that the window retains
	 * its original position in the list.  So, if we hide and un-hide
	 * window 2, we'll get the same effect as in Lesson 1 but in fewer
	 * steps.
	*/

	wn_hidew(window_handle[1]);
	getch();

	wn_hidew(window_handle[1]);
	getch();

	/*
	 * Lesson 3: Sizing a window.
	 *
	 * Sizing a window is always performed relative to its current size.
	 * So the columns and rows parameters are indicate how many columns
	 * and rows to increase or decrease the window size by.
	 * Note that if the resulting size is larger than the physical screen
	 * or smaller than 1 row by 1 column that the function is executed
	 * but returns a value of MODIFIED.
	 *
	 * We are actually changin the size of a tile, so we'll have to
	 * specify a tile handle also (in a window with no tiles just use 0.)
	 *
	 *      window handle, tile handle, columns, rows
	 *	    |              |           |       |
	 *          |              |  +--------+       |
	 *          V              V  V   V----------- +
	*/

	wn_sizet(window_handle[2], 0, -5, -4);
	getch();

	/*
	 * You can also size ranges of windows using the wn_sizerng function.
	 * The function will apply itself to the first item in the range and
	 * work up towards the top of the screen until it applies itself to
	 * the second item in the range or reaches the top of screen.
	 *
	 * The syntax is very similar to the above.
	 * wn_sizerng(1st handle, 2nd handle, columns, rows)
	 *
	 * For example:
	*/

	for (count = 0; count < 5; count++) {
		wn_sizerng(window_handle[0],window_handle[2], 1, 1);
	}
	getch();

	/* And then back again */

	for (count = 0; count < 5; count++) {
		wn_sizerng(window_handle[0],window_handle[2], -1, -1);
	}
	getch();

	/*
	 * Lesson 4: scrolling a window
	 *
	 * Scrolling a window refers to repositioning the viewport over
	 * the virtual screen (giving the illusion of scrolling information
	 * through the window.)
	 *
	 * As with size, this is actually a tile function.  But, since
	 * there are no tiles we'll use 0 for the tile handle.
	 *
	 * Likewise, if the result of the function is to place the
	 * viewport so that it is not completely filled by the virtual
	 * screen the result of the function is modified, but executed
	 * and the function returns the value MODIFIED.
	 *
	 * The syntax of this function is identical to the wn_sizet, except
	 * that a postive columns parameter moves the virtual screen to
	 * the left, and a positive rows parameter moves the virtual screen
	 * up.
	 *
	 * We'll do it fifteen times so you get the effect.
	*/
	
	for (count = 0; count < 15; count++) {
		wn_scrollvs(window_handle[2], 0, 1, 0);
		wn_sync_tw_to_vs(window_handle[2], 0);
		getch();
	}

	/* And then back again */

	for (count = 0; count < 15; count++) {
		wn_scrollvs(window_handle[2], 0, -1, 0);
		wn_sync_tw_to_vs(window_handle[2], 0);
		getch();
	}
	
	/*
	 * Lesson 5: moving a window
	 *
	 * Again, moving a window is very similar to sizing a window.
	 * The columns parameter moves it to the right if positive, and
	 * the rows parameter moves the window down if positive.
	 *
	 * The syntax for the function is:
	 * wn_movew(window handle, columns, rows)
	 *
	 * For example:
	*/

	for (count = 0; count < 5; count++) {
		wn_movew(window_handle[2], 1, 1);
	}
	getch();

	/* and back again */

	for (count = 0; count < 5; count++) {
		wn_movew(window_handle[2], -1, -1);
	}
	getch();

	/*
	 * and again, exactly as with sizing a window there is a related
	 * range function with the syntax:
	 * wn_moverng(1st handle, 2nd handle, columns, rows)
	 *
	*/

	for (count = 0; count < 5; count++) {
		wn_moverng(window_handle[0], window_handle[2], 1, 1);
	}
	getch();

	/* and back again */

	for (count = 0; count < 5; count++) {
		wn_moverng(window_handle[0], window_handle[2], -1, -1);
	}
	getch();

	/*
	 * Lesson 6: flying boxes
	 *
	 * Flying boxes give the illusion that a box originates from a point
	 * on the screen, or that it retreats to a point on the screen.
	 * It is very effective at giving cognitive messages to the user
	 * that an action has been performed.  For example, in Ashton-Tate's
	 * Framework when the user saves a file you'll see a "ghost" box seem
	 * to move across the screen from the window to the file cabinets.
	 * It is also the technique used to make exploding boxes etc.
	 *
	 * Let's first look at how the basic function works, and then how
	 * to combine with other functions for different effects.
	 *
	 * The syntax is:
	 * wn_flybox(bx, by, br, bc, ex, ey, er, ec, granularity,
	 *	speed, boxchars, foreground, background)
         *
         * bx,by	define the upper left coordinate of the beginning box
	 * br,bc	define the outer dimensions of the beginning box
	 * ex,ey 	define the upper left coordinate of the ending box
	 * er,ec	define the outer dimensions of the ending box
	 * granularity	defines the number of boxes to display in between
	 * speed	indicates how long to wait after displaying a box
	 * boxchars	defines the characters to use when creating the boxes
	 *		We already have setup some box character pointers
	 *		called box0, box1, box2, and box3.  Later
	 *		we'll show you how to make your own.
	 * foreground 	the foreground color of the box
	 * background	the background color of the box
	 *
	 * So, to make a box of 1 row and column fly from the upper right
	 * hand corner and grow to a box of dimensions 10 by 10 in the
	 * lower left hand corner we execute the function with these
	 * parameters:
	*/

	 wn_flybox(78, 1, 1, 1, 1, 14, 10, 10, 10, 50, box4, lightgray, black);
	 getch();

	/*
	 * What we do is combine that with other features like opening a
	 * window for some special effects.
	 *
	 * So if we close window 2 but first precede it with
	 * with a flying box in front of it -- watch the effect.
	*/

	wn_flybox(wdw[window_handle[1]]->physical_x,
		wdw[window_handle[1]]->physical_y,
		wdw[window_handle[1]]->port_rows,
		wdw[window_handle[1]]->port_columns,
		78, 23, 1, 1, 10, 50, box4, lightgray, black);

	wn_hidew(window_handle[1]);
	getch();

	/* And of course we can bring it back again in the same way */

	wn_flybox(78, 23, 1, 1,
		wdw[window_handle[1]]->physical_x,
		wdw[window_handle[1]]->physical_y,
		wdw[window_handle[1]]->port_rows,
		wdw[window_handle[1]]->port_columns,
		10, 50, box4, lightgray, black);

	wn_hidew(window_handle[1]);
	getch();

	/*
	 * Lesson 7: Scroll Bars
	 *
	 * Scroll bars are generally used for the mouse to point to
	 * to perform certain actions.  You can learn more about
	 * using the mouse in tutor3.c.  But I can show you how to
	 * turn the scroll bars on and off.  This is actually a tile
	 * related function.  But, since we aren't using tiles in these
	 * windows we'll just use a tile handle of 0.
	 *
	 * The syntax is:
	 * wn_togscroll(window handle, tile handle, TRUE or FALSE);
	 *
	 * So, to turn the scroll bars on:
	*/
	
	wn_togscroll(window_handle[1], 0, TRUE);
	getch();

	/* and to turn them off */

	wn_togscroll(window_handle[1], 0, FALSE);
	getch();

	/* Once again we have a range function for this: */

	wn_togscrollrng(window_handle[0], window_handle[2], TRUE);
	getch();

	/* And to turn them all off */

	wn_togscrollrng(window_handle[0], window_handle[2], FALSE);
	getch();

	/*
	 * Note that you can also control whether windows are created
	 * by default with scroll bars.  If scroll_bars_on == FALSE
	 * windows are initially created without scroll bars.
	*/

	/*
	 * Lesson 8:  Changing border characters
	 *
	 * The border characters of a box are determined by a 13 char
	 * array that each box points to.  This 13 char array contains
	 * the characters used to draw the box.  See reference manual
	 * for a complete description of the array.  Here, we'll just
	 * use some defaults that come with Window Pro.
	 *
	 * Window Pro has five predefined box character sets: box0,
	 * box1, box2, box3, and box4.  The bax character set pointer
	 * default_box determines what box characters a box is initially
	 * given.  default_box is initialized to be equivalent to box0.
	 *
	 * The syntax of the command is:
	 * wn_chgbord(window handle, box character pointer)
	 *
	 * For example:
	*/

	wn_chgbord(window_handle[0], box1);
	getch();

	/* And as always, there is a range version of this function. */

	wn_chgbordrng(window_handle[0], window_handle[2], box1);
	getch();

	/*
	 * Lesson 9: changing the color of the borders
	 *
	 * The color of the border is set as it is activated and deactivated.
	 * When a window is activated its border color is set to the value
	 * of the global variable active_attr, when it is de-activated its
	 * border color is set to the value of inactive_attr.
	 *
	 * You can change these values using this syntax:
	 * active_attr = foreground + (background << 4)
	 *
	 * You can also temporarily change the color of a window using
	 * the window pro function wn_chgcolor(window handle, foreground,
	 * background).
	 *
	 * For example:
	*/

	wn_chgcolor(window_handle[2], red, black);
	getch();

	/* And of course there is a range version of this function also */

	wn_chgcolorrng(window_handle[0], window_handle[2], red, black);
	getch();

	/*
	 * Lesson 10: Changing the style of borders and freezing.
	 *
	 * This allows you to create shadowing effects.  My personal
	 * preference with this is to use box4 character set and to
	 * not use window names, although you can.
	 *
	 * In addition, since I am going to do a lot of radical things
	 * to the windows, I will frezze the screen and then flash the
	 * results of all operations on the screen.
	 *
	 * First, let's freeze the screen.
	*/
	wn_freeze();

	/* Now lets get rid of the names */

	for (count = 0; count < 3; count++) wn_namew(window_handle[count],NULL);

	/* Now lets change the box character sets */

	wn_chgbordrng(window_handle[0], window_handle[2], box4);

	/*
	 * We'll also need to fill the virtual screen with color to
	 * make this look decent.  See vs_fillattr in the reference
	 * manual for an explanation
	 *
	*/
	
	for (count = 0; count < 3; count++)
		vs_fillattr(window_handle[count], 0, 1, 1, 80, 25, black, lightgray);
	

	/*
	 * Now lets see what this looks like, before we do any shadowing.
	 * The defrost function needs an upper left and lower right coordinate
	 * of the portion of the screen to redraw.  It's safest to just use 1,1
	 * for the upper right and physical_columns, physical_rows for the
	 * lower left, although if you can limit the region to the portion
	 * of the physical screen which has changed you can spped up the
	 * operation (This doesn't matter too much unless you do a lot of
	 * freezing and defrosting in succession.)  You can also try
	 * suspending a window (if you are only working on one window) but
	 * this isn't too reliable if the window overlaps any other window,
	 * although it is faster than freeze/defrost.
	*/
	wn_defrost(1, 1, physical_columns, physical_rows);
	getch();

	/*
	 * OK, this is the real thing here.  There are five styles of window
	 * border, defined in PRO.H:
	 * UPPER_LEFT
	 * UPPER_RIGHT
	 * LOWER_LEFT
	 * LOWER_RIGHT
	 * NONE
	 * HEAD_ON
	 *
	 * These roughly represent some type of light source for a shadowing
	 * effect.
	 *
	 * You can see each of the different effects as follows:
	*/

	wn_togborder(window_handle[1], UPPER_LEFT);
	getch();

	wn_togborder(window_handle[1], UPPER_RIGHT);
	getch();

	wn_togborder(window_handle[1], LOWER_RIGHT);
	getch();

	wn_togborder(window_handle[1], LOWER_LEFT);
	getch();

	wn_togborder(window_handle[1], NONE);
	getch();

	wn_togborder(window_handle[1], HEAD_ON);
	getch();


	/* And of course there is a range function for this */

	wn_togbordrng(window_handle[0], window_handle[2], UPPER_LEFT);
	getch();

	wn_togbordrng(window_handle[0], window_handle[2], UPPER_RIGHT);
	getch();

	wn_togbordrng(window_handle[0], window_handle[2], LOWER_RIGHT);
	getch();

	wn_togbordrng(window_handle[0], window_handle[2], LOWER_LEFT);
	getch();

	wn_togbordrng(window_handle[0], window_handle[2], NONE);
	getch();

	wn_togbordrng(window_handle[0], window_handle[2], HEAD_ON);
	getch();


	/*
	 * Lesson 11: Zooming a window
	 *
	 * Zooming a window temporarily increases its size to the size of
	 * of the physical screen.  Zooming can only be done on the active
	 * window.
	 *
	 * For example, to zoom window 2:
	*/
	
	/* first activate it */	
	wn_actw(window_handle[1]);

	/* then zoom it */
	wn_zoomw();
	getch();

	/* zoom is a toggle.  To unzoom just call the function again */
	wn_zoomw();
	getch();
	
	/* And we'll bring back the little window */
	wn_actw(window_handle[2]);

	/*
	 * Lesson 12: The cursor.
	 *
	 * You can turn the cursor on and off using wn_hidecur and
	 * wn_showcur.  The cursor is turned on and off automatically
	 * by Window Pro during certain operations, but having used
	 * wn_hidecur suppresses turning the cursor on.  When Window
	 * Pro does turn the cursor on it uses the global variables
	 * cursor_e and cursor_b for the ending and beginning scan line
	 * values (So by doing this cursor_b = 1 and cursor_e = 14, for
	 * example, you can get a block cursor.)
	 *
	 * Let's change the values and then turn the cursor on and off
	 * a few times.
	*/

	cursor_b = 1;
	cursor_e = 14;
	wn_showcur();
	getch();

	cursor_b = 3;
	cursor_e = 14;
	wn_hidecur();
	wn_showcur();
	getch();

	cursor_b = 5;
	cursor_e = 14;
	wn_hidecur();
	wn_showcur();
	getch();


	cursor_b = 7;
	cursor_e = 14;
	wn_hidecur();
	wn_showcur();
	getch();


	/*
	 * Lesson 13: deleting windows
	 *
	 * Deleting windows is exactly like closing windows, except
	 * that the window is gone forever, deleted from memory, and
	 * its handle returned to the pool of assignable handles.
	 *
	 * Lets get rid of all of the windows with a little pizzazz.
	 *
	*/

	for (count = 0; count < 3; count++) {
		wn_flybox(wdw[window_handle[count]]->physical_x,
			wdw[window_handle[count]]->physical_y,
			wdw[window_handle[count]]->port_rows,
			wdw[window_handle[count]]->port_columns,
			wdw[window_handle[count]]->physical_x +
			wdw[window_handle[count]]->port_columns/2,
			wdw[window_handle[count]]->physical_y +
			wdw[window_handle[count]]->port_rows/2,
			1, 1, 5, 50, box4, white, black);
		wn_delw(window_handle[count]);
	}
	/*
	 * This is still only the beginning.  I haven't covered all of
	 * the functions.  Plus, once you understand the window record
	 * and the global variables you can do other "tricks."  Probably
	 * things that I never even conceived of.  This of course has not
	 * even discussed tile manipulation, or virtual screen manipulation.
	 * Proceed to TUTOR3.C for tile manipulation, TUTOR4.C for
	 * virtual screen manipulation, and TUTOR5.C for extended keyboard
	 * and mouse techniques.
	*/

	/* restore the characters to the original screen */
        wn_restorescr();

	/* restore the cursor position */
	v_gotoxy(oldx,oldy);

	/* restore the cursor shape */
	v_curshape(oldb, olde);

}
