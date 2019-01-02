#include "pro.h"
#include "xglobals.h"
#include "vs.h"
#include "colors.h"
#include "video.h"
#include <conio.h>


int main()
{
	unsigned int window_handle[3], count;
	unsigned char tile_handle[10];

	/*
	 * See tutor1.c for an explanation of this section.
	*/
	active_attr = white + (black << 4);
	inactive_attr = lightgray + (black << 4);
	active_tile_attr = lightgreen + (black << 4);
	inactive_tile_attr = red + (black << 4);
	scroll_bars_on = NO_BARS;
	thumbwheels_on = NO_BARS;
	method = DMA;
	wn_init();

	/* Let's turn off the cursor -- its annoying */
	wn_hidecur();

	window_handle[0] = wn_createw(25,80,2,3,1,1,20,70,FALSE,HEAD_ON,"TILE TUTORIAL",NULL);
	wn_openw(window_handle[0]);
	getch();


	/*
	 * Lesson 1:  Naming a tile
	 *
	 * Even though this window is not divided, it has one tile.  Every
	 * window has at least one tile.  If its divided it has at least two
	 * tiles.  We can give this tile a name using the
	 * wn_namet(window handle, tile handle, new name) function.
	 *
	*/

	/*
	 * We'll establish this as pointing to the first tile.
	 * The first tile in a new window always has a handle of 0
	*/

	tile_handle[0] = 0;

	/* and give it a name */
	wn_namet(window_handle[0], tile_handle[0], "tile number 1");
	getch();

	/*
	 * Lesson 2: Creating a tile
	 *
	 * You can create a second tile in a window using the wn_createt
	 * function.  This function is similar to the wn_createw function
	 * in that simply creating a tile does not put it onto the
	 * physical screen you will also have to open it.  For starters,
	 * lets just create one.  The syntax is:
	 * wn_createt(window handle, tile name, virtual screen columns,
	 * virtual screen rows, virtual x, virtual y)
	 *
	 * virtual x, virtual y refer to the coordinate of the virtual
	 * screen which will map to the upper left corner of the viewport
	 * (when it is displayed on the physical screen.)
	 *
	 * wn_createt returns a tile handle similar to the way wn_createw
	 * returns a window handle.
	*/

	tile_handle[1] = wn_createt(window_handle[0], "tile number 2", 80, 25, 1, 1);

	/*
	 * And now we can open it.  When it is opened the active tile
	 * will be split into two parts.  The lower half will be taken
	 * by the new tile.  This is the only real significance of the
	 * active tile.  You can change the active tile using the
	 * wn_actt function.
	 *
	*/

	wn_opent(window_handle[0], tile_handle[1]);
	getch();

	/*
	 * Notice that the name of the active tile is displayed in a
	 * different color.  When a tile is activated its name is given
	 * the attribute value of the global variable active_tile_attr.
	 * When it is de-activated it is given the value of the global
	 * variable inactive_tile_attr.
	*/

	/*
	 * Lesson 2: Sizing tiles
	 *
	 * If you increase or decrease the number of rows in a tile
	 * that has a tile below it.  The tile below the tile being sized
	 * is also adjusted in size so that the overall dimensions of the
	 * window do not change.
	 *
	 * If the size of any tile is adjusted columnwise the entire window
	 * is effected.  And if you ajust the size of the last tile rowwise
	 * the window is also increased or decreased in size.
	 *
	 * Watch---
	 *
	 * First, lets adjust the top tile row wise.
	*/

	for (count = 0; count < 5; count++) {
		wn_sizet(window_handle[0], tile_handle[0], 0, 1);
	}
	getch();

	/* And bring it back */

	for (count = 0; count < 5; count++) {
		wn_sizet(window_handle[0], tile_handle[0], 0, -1);
	}
	getch();

	/* Now we'll adjust it column wise */

	for (count = 0; count < 5; count++) {
		wn_sizet(window_handle[0], tile_handle[0], 1, 0);
	}
	getch();
	
	/* And bring it back */

	for (count = 0; count < 5; count++) {
		wn_sizet(window_handle[0], tile_handle[0], -1, 0);
	}
	getch();

	/* Now watch what happens when you adjust the last tile rowwise */


	for (count = 0; count < 2; count++) {
		wn_sizet(window_handle[0], tile_handle[1], 0, 1);
	}
	getch();
	
	/* And bring it back */

	for (count = 0; count < 2; count++) {
		wn_sizet(window_handle[0], tile_handle[1], 0, -1);
	}
	getch();

	/*
	 * Lesson 3: Swapping tiles.
	 *
	 * You can swap the name and virtual screen of any two tiles, even
	 * tiles in different windows.
	*/

	/* first lets put some color in each so we can tell then apart */
	vs_fillchar(window_handle[0], tile_handle[0], 1, 1, 80, 25, 'x', blue, red);
	vs_fillchar(window_handle[0], tile_handle[1], 1, 1, 80, 25, 'o', lightred, blue);
	getch();

	/* Now we'll swap them */
	wn_swapt(window_handle[0], tile_handle[0], window_handle[0], tile_handle[1]);
	getch();

	/*
	 * Lesson 4: Revisiting scroll bars
	 *
	 * Scroll bars can be turned on and off for individual tiles.
	 *
	*/
	wn_togscroll(window_handle[0], tile_handle[0], BOTH_BARS);
	wn_togthumb(window_handle[0], tile_handle[0], VERTICAL_BAR);
	getch();

	/* And off */
	wn_togscroll(window_handle[0], tile_handle[0], NO_BARS);
	wn_togthumb(window_handle[0], tile_handle[0], NO_BARS);
	getch();

	/*
	 * With imaginative use of the wn_togscrollrng function discussed
	 * in TUTOR2 you can also turn the scroll bars on and off for all
	 * tiles in a single window.
	*/

	wn_togscrollrng(window_handle[0], window_handle[0], TRUE);
	getch();

	/*
	 * Lesson 5: Using wn_redraw and wn_draww
	 *
	 * The effect of changing certain variables will not be immediately
	 * seen on the screen (unless you do it via a WINDOW PRO function.)
	 * So, to cover this situation we've included some functions to
	 * force redrawing of the windows.
	 * wn_redraw will redraw all of the windows and
	 * wn_draww will redraw a single window
	 *
	 * For example if we change the scroll bar characters to an
	 * alternate arrow type (let's say we're on a terminal that
	 * doesn't support the IBM extended character set.)
	*/
	sbu = '^';
	sbd = 'v';
	sbr = '>';
	sbl = '<';

	/*
	 * You won't see the effect of this until all of the windows are
	 * redrawn.  If you use wn_redraw you effectively redraw all of
	 * the windows.  You may do this in a buffer (to avoid blinking)
	 * and then selectively
	 * update a region of the physical screen from the buffer by freezing
	 * and defrosting before and after the wn_redraw.  The region
	 * is expressed as the upper left coordinate followed by the
	 * lower right coordinate.  To be safe we'll just use the upper
	 * and lower bounds of the whole screen.
	*/

	wn_freeze();
	wn_redraw();
	wn_defrost(1, 1, physical_columns, physical_rows);
	getch();
	
	/*
	 * And we can redefine the scroll bar characters again and
	 * then reforce the updating of just a single window
	*/

	sbu = 0x1E;
	sbd = 0x1F;
	sbr = 0x10;
	sbl = 0x11;

	wn_draww(window_handle[0]);

	/*
	 * Lesson 6: closing and deleting tiles
	 *
	 * When a tile is closed the tile below it inherits the
	 * left over space, except when there is no tile below.
	 * Then the tile above gets the left over space.  You can't close
	 * the last tile in a window.  A window must have at least one
	 * tile.
	 *
	 * Before we go on lets create one more tile and then we'll close it.
	*/

	scroll_bars_on = BOTH_BARS;
	thumbwheels_on = VERTICAL_BAR;
	tile_handle[2] = wn_createt(window_handle[0], "tile number 3", 80, 25, 1, 1);
	wn_opent(window_handle[0], tile_handle[2]);
	getch();

	wn_closet(window_handle[0], tile_handle[2]);
	getch();

	/* Now lets open it up in the other tile */
	
	/* first active tile 1 */
	wn_actt(window_handle[0], tile_handle[1]);
	getch();

	/* then open the new tile */
	wn_opent(window_handle[0], tile_handle[2]);
	getch();

	/* Now get rid of it for good! */
	wn_delt(window_handle[0], tile_handle[2]);
	getch();

	/* restore the characters to the original screen */
        wn_restorescr();

	/* restore the cursor position */
	v_gotoxy(oldx,oldy);

	/* restore the cursor shape */
	v_curshape(oldb, olde);

}
