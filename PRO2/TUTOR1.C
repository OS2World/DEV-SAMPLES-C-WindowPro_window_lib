#include <conio.h>
/*
 * We'll need this for type checking on the windows functions
*/
#include "pro.h"


/*
 * You've got to have this.  It will setup the Window Pro global
 * variables.
*/
#include "xglobals.h"


/*
 * We'll need this for type checking on the virtual screen
 * functions
*/
#include "vs.h"
#include "video.h"


/*
 * This is really handy, it defines the IBM-PC colors
*/
#include "colors.h"


int main()
{

	/*
	 * We'll use this to store the window and tile handle
	 * returned when we create a window.
	*/
	unsigned int window_handle;
	
	/*
	 * Initialize Window Pro.  If you don't do this -- forget
	 * it, everything blows up.
	*/
	method = DMA;
	wn_init();

	/*
	 * Let's turn off the scroll bars default -- We don't want
	 * to worry about those right now.
	*/

	scroll_bars_on = NO_BARS;

	/*
	 * Create a window and get a handle back.
         *
	 * The window's virtual screen will be 25 rows by 80
	 * columns,
	*/

	window_handle = wn_createw(25, 80,

	/*
	 * The upper left corner of the window will be located at the
	 * physical screen coordinates of (2,3); second column and
	 * third row.
	*/

	2, 3,

	/*
	 * The upper left corner of the window will map to the
	 * virtual screen coordinate (1,1); first column and
	 * first row.
	*/

	1, 1,

	/*
	 * The inner dimensions of the window will be 5,10;
	 * 5 rows by 5 columns.
	*/

	5, 10,

	/*
	 * The window will not be suspended, i.e. all output
	 * to the virtual screen will be immediately displayed
 	 * on the physical screen.
	*/

	FALSE,

	/*
	 * We won't use any shadowing effects.
	*/

	HEAD_ON,

	/*
	 * Nor will we assign a name to the tile or window.
	*/

	NULL, NULL);


	/*
	 * More simply put: 	
	 * wn_createw(25,80,2,3,1,1,5,10,FALSE,HEAD_ON,NULL,NULL);
	*/


	/*
	 * Here comes the confusing part:
	 * All windows, even those that aren't divided into tiles
	 * have tiles.  You really should think of windows as a
	 * way of grouping tiles together.  In the above case
	 * When we created the window, we also created a tile, and
	 * a virtual screen.  The first tile created in a new
	 * window always has a handle of 0 and every virtual
	 * screen is associated with a tile. We always
	 * reference a virtual screen by a pair of handles:
	 * A window handle (pointing to a group of tiles), and
	 * a tile handle.  In the window we just created the window
	 * has a handle of 'window_handle', the tile has a handle
	 * of 0, and we reference the virtual screen using
	 * {window_handle, 0}.
	*/

	/*
	 * Now let's put something in the virtual screen
	 *
	*/

	/*
	 * first we reference the virtual screen
	*/

	vs_puts(window_handle, 0,

	/*
	 * Then we say where we want the string put (column, row).
	*/

	1, 1,

	/*
	 * Now we indicate the maximum length of the string to output
	*/

	10,

	/* Now the foreground and background color of the string.
	 * Note, if the string is shorter than the maximum length
	 * The function pads spaces to the end.
	*/

	white, blue,

	/*
	 * And finally, the string to output.
	*/

	"Window Pro");

	/*
	 * More simply put:
	 * vs_puts(window_handle,0,1,1,10,blue,white,"Window Pro");
	*/

	/*
	 * However, before anything happens on the screen we need to
	 * open it.
	*/

	wn_openw(window_handle);
 	getch();

	/*
	 * If you want to restore the background screen before you exit
	 * just do a wn_restorescr().
	*/

	/* restore the characters to the original screen */
        wn_restorescr();

	/* restore the cursor position */
	v_gotoxy(oldx,oldy);

	/* restore the cursor shape */
	v_curshape(oldb, olde);

	/*
	 * That's it:

***********************************************************
* {                                                       *
* wn_init();                                              *
*                                                         *
* window_handle = 	                                  *
* wn_createw(25,80,2,3,1,1,5,10,FALSE,HEAD_ON,NULL,NULL); *
*                                                         *
* vs_puts(window_handle,0,1,1,10,white,blue               *
* "Window Pro");                                          *
*                                                         *
* wn_openw(window_handle);                                *
* getch();                                                *
* wn_restorescr();                                        *
* v_gotoxy(oldx, oldy)                                    *
* v_curshape(oldb, olde)                                  *
* }                                                       *
***********************************************************

	*/
}
