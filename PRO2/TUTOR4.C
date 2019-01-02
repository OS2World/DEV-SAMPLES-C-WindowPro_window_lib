#include "pro.h"
#include "xglobals.h"
#include "vs.h"
#include "video.h"
#include "colors.h"

char string[2000];

int main()
{
	unsigned int window_handle[3], count, row, column, count1;
	unsigned char tile_handle[10];

	/*
	 * See tutors 1-3 for an explanation of this section.
	*/
	active_attr = white + (black << 4);
	inactive_attr = lightgray + (black << 4);
	active_tile_attr = lightgreen + (black << 4);
	inactive_tile_attr = red + (black << 4);
	scroll_bars_on = FALSE;
	method = ANSI;
	wn_init();

	window_handle[0] = wn_createw(25,80,2,3,1,1,20,70,FALSE,HEAD_ON,"Virtual Screen TUTORIAL",NULL);

	tile_handle[0] = 0;
	wn_namet(window_handle[0], tile_handle[0], "tile number 1");

	tile_handle[1] = wn_createt(window_handle[0], "tile number 2", 80, 25, 1, 1);
	wn_opent(window_handle[0], tile_handle[1]);
	wn_openw(window_handle[0]);
	getchar();


	/*
	 * Lesson 1: vs_printf, the logical cursor, and activating tiles
	 *
	 * vs_printf is similar to printf except that you specify a
	 * virtual screen and a foreground and background color.
	 * Printing begins at the virtual screen's logical cursor
	 * location and the cursor is advanced for each character output.
	 * TABS are expanded to 8, CR are ignored and LF puts the cursor
	 * at the beginning of the next row.  If the string extends beyond
	 * the right side of the virtual screen it wraps around, and if
	 * string extends beyond the bottom of the virtual screen the virtual
	 * screen is scrolled up.  Pretty much like using regular printf
	 * on the physical screen.
	 *
	 * Let's try counting to 5.
	 */

	for (count = 1; count < 6; count++) {

		vs_printf(window_handle[0], tile_handle[0], white, black,
			"This is the number %d\n", count);

	}
	getchar();

	/* and now in the other tile */

	for (count = 1; count < 6; count++) {

		vs_printf(window_handle[0], tile_handle[1], white, black,
			"This is the number %d\n", count);

	}
	getchar();

	/*
	 * Notice that the cursor doesn't move down to tile 2.  The logical
	 * was advanced, but the hardware cursor is only displayed in the
	 * active tile.  We can display the cursor by activating tile 2
	*/

	wn_actt(window_handle[0], tile_handle[1]);
	getchar();


	/*
	 * Lesson 2: vs_puts, vs_putc, and vs_clrvs.
	 *
	 * vs_puts is similar to vs_format.  It doesn't except a variable
	 * argument list, just a single string.  But, it also does not
	 * do TAB expansion or CR/LF conversion (it outputs the IBM
	 * extended character in its place.)  In addition although
	 * it does do wrapping at the right edge of the virtual screen
	 * it will not automatically scroll the virtual screen if the
	 * string extends beyond the bottom of the virtual screen.  Instead
	 * it merrily continues writing to whatever memory is above the virtual
	 * screen.  Because this is not a good idea, you can set a maximum
	 * string length, which will clip the string output if it goes
	 * beyond the maximum length.  If the string is less than the maximum
	 * length it pads spaces. Lastly, it is not dependent on the logical
	 * cursor location, nor does it advance the logical cursor.
	 *
	 * But, before we do that lets clear tile 1.
	 *
	 */

	vs_clrvs(window_handle[0], tile_handle[0], white, black);
	getchar();

	/*
	 * There are a whole series of vs_clr?? functions for clearing
	 * the virtual screen from the logical cursor to beginning of a line
	 * to the end of a line, etc.  See the reference manual for more
	 * info.
	*/

	#define MAXLEN		60
	#define ROW		1
	#define COLUMN		1

	vs_puts(window_handle[0], tile_handle[0], COLUMN, ROW, MAXLEN, black,
		lightgray, "vs_puts works \n <--- but newline looks funny");
	getchar();

	/*	
	 * vs_putc is identical to vs_puts except it outputs single characters.
	 * So, it doesn't need that maximum length stuff.
	 * Let's output the whole IBM character set
	*/

	row = column = 1;
	vs_clrvs(window_handle[0], tile_handle[1], white, black);

	for (count = 0; count < 255; count++) {
		vs_putc(window_handle[0], tile_handle[1], column++, row,
			black, lightgray, (char) count);
		if (column > wdw[window_handle[0]]->port_columns) {
			column =1;
			row++;
		}
	}
	getchar();

	/*
	 * Lesson 3: fill
	 *
	 * WINDOW PRO let's you define a rectangular region by its
	 * upper left and lower right coordinates.
	 *
	 * Then, with vs_fillchar you can fill in that region with both
	 * a character and an attribute, or with vs_fillattr you can keep
	 * the existing characters but fill in the region with a new
	 * attribute.
	 *
	 * Lets clear out the top tile and see how it works.
	 */

	vs_clrvs(window_handle[0], tile_handle[0], black, lightgray);
	getchar();
	
	vs_fillchar(window_handle[0], tile_handle[0],
		15,3, 30,8, 'x', white, black);
	getchar();

	/* now we can change the attribute of that same region */

	vs_fillattr(window_handle[0],tile_handle[0],15,3,30,8,lightgray,black);
	getchar();

	/*
	 * Lesson 4: Inserting and deleting rows and columns
	 *
	 * These functions: vs_insrow, vs_inscolumn, vs_delrow, vs_delcolumn,
	 * let you define a rectangular region as discussed in the fill
	 * functions and then insert and delete rows and columns in that
	 * region.
	 *
	 * First, vs_insrow, it inserts rows at the top of the rectangular
	 * region and pushes all of the other rows down.  The new blank
	 * row at the top of the region has an attribute of your choosing.
	 *
	 * For example,
	/*

	/* First lets file tile 2 with some text */
	for (count1 = 1; count1 <= 25; count1++) {
		for (count = 1; count <= 80; count++) {
			vs_putc(window_handle[0], tile_handle[1], count,
				count1, white, black,
				(char) (count1 + count + 63));
		}
	}
	getchar();

	/*
	 * And now change the attribute of the region so you can see it more
	 * clearly
	*/

	vs_fillattr(window_handle[0], tile_handle[1], 15,3, 30,8, lightgray, black);
	getchar();

	/* Now let's insert 5 rows one at a time */

	#define NUMBER_OF_ROWS			1

	for (count = 0; count < 5; count++) {
		vs_insrow(window_handle[0], tile_handle[1], 15,3,
			30,8, NUMBER_OF_ROWS, lightgray, black);
		getchar();
	}

	/*
	 * Deleting rows is inentical to inserting rows except that the
	 * rows at the top of the region are 'deleted' and the blank lines
	 * appear at the bottom of the region.
	 *
	 * Now lets setup tile 1 and delete 5 rows one at a time.
	*/

	for (count1 = 1; count1 <= 25; count1++) {
		for (count = 1; count <= 80; count++) {
			vs_putc(window_handle[0], tile_handle[0], count,
				count1, white, black,
				(char) (count1 + count + 63));
		}
	}
	getchar();

	/*
	 * And now change the attribute of the region so you can see it more
	 * clearly
	*/

	vs_fillattr(window_handle[0], tile_handle[0], 15,3, 30,8, lightgray, black);
	getchar();

	/* Now let's delete 5 rows one at a time */

	for (count = 0; count < 5; count++) {
		vs_delrow(window_handle[0], tile_handle[0], 15,3,
			30,8, NUMBER_OF_ROWS, lightgray, black);
		getchar();
	}

	/*
	 * vs_inscolumn works the same as vs_insrow except that it inserts
	 * a blank column at the left side of the region and pushes the rest
	 * of the columns in the region to the right.
	 *
	 * We'll use the same technique as before to demonstrate.
	*/

	/* here's a trick to speed up a bunch of vs_putc functions */
	wn_suspendt(window_handle[0], tile_handle[1]);

	for (count1 = 1; count1 <= 25; count1++) {
		for (count = 1; count <= 80; count++) {
			vs_putc(window_handle[0], tile_handle[1], count,
				count1, white, black,
				(char) (count1 + count + 63));
		}
	}
	wn_suspendt(window_handle[0], tile_handle[1]);
	getchar();

	/*
	 * And now change the attribute of the region so you can see it more
	 * clearly
	*/
	vs_fillattr(window_handle[0], tile_handle[1], 15,3, 30,8, lightgray, black);
	getchar();

	/* Now let's insert 10 columns one at a time */

	for (count = 0; count < 10; count++) {
		vs_inscolumn(window_handle[0], tile_handle[1], 15,3,
			30,8, NUMBER_OF_ROWS, lightgray, black);
		getchar();
	}

	/*
	 * And finally, the vs_delcolumn function (if you haven't already
	 * guessed) deletes the column on the left side of the region and
	 * leaves blank lines on the right side
	 *
	 * Let's see how that might work.
	*/

	wn_suspendt(window_handle[0], tile_handle[0]);

	for (count1 = 1; count1 <= 25; count1++) {
		for (count = 1; count <= 80; count++) {
			vs_putc(window_handle[0], tile_handle[0], count,
				count1, white, black,
				(char) (count1 + count + 63));
		}
	}
	wn_suspendt(window_handle[0], tile_handle[0]);
	getchar();

	/*
	 * And now change the attribute of the region so you can see it more
	 * clearly
	*/

	vs_fillattr(window_handle[0], tile_handle[0], 15,3, 30,8, lightgray, black);
	getchar();

	/* Now let's delete 10 columns one at a time */

	for (count = 0; count < 10; count++) {
		vs_delcolumn(window_handle[0], tile_handle[0], 15,3,
			30,8, NUMBER_OF_ROWS, lightgray, black);
		getchar();
	}

	/*
	 * Lesson 5: vs_gets
	 *
	 * vs_gets is a gets-like function for virtual screens.  It echoes
	 * characters typed at the keyboard to a virtual screen, starting at
	 * the virtual screen's logical cursor and for each character input
	 * outputs the character (in the attribute of your choice) and advances
	 * the logical cursor.  If the cursor is advanced to an area outside of
	 * the viewport you can elect to automatically readjust the viewport, or
	 * not.  If the string exceeds the length of the line it automatically
	 * wraps to the beginning of the next line.  If the string exceeds the
	 * number of rows in the virtual screen all of the text in the virtual
	 * screen scrolls up.  You must specify a pointer to the storage location
	 * and vs_gets does not determine if the pointer has sufficient
	 * memory allocated to it to hold the input string.  Instead you
	 * pass a maximum length parameter.
	 *
	 * For example:
	*/

	/* Lets set up the screen first */
	vs_clrvs(window_handle[0], tile_handle[0], white, black);
	wn_sizet(window_handle[0], tile_handle[0], -20, 0);
	vs_locatecur(window_handle[0], tile_handle[0], 1,2);
	vs_puts(window_handle[0], tile_handle[0], 1, 1, 50, white, black,
		"Type in a few sentences. (Scroll is on.)");
	
	/* You don't have to do this, but you won't see the cursor otherwise */
	wn_actt(window_handle[0], tile_handle[0]);

	#define SCROLL_OPTION_ON	1
	#define SCROLL_OPTION_OFF	0
	#define MAXIMUM_LENGTH		2000

	/* Here is vs_gets */
	vs_gets(window_handle[0], tile_handle[0], SCROLL_OPTION_ON, string,
		white, black, MAXIMUM_LENGTH);
	getchar();

	/* Now lets do the whole thing over again but with the scroll option off */

	/* Lets set up the screen first */
	vs_clrvs(window_handle[0], tile_handle[0], white, black);
	vs_locatecur(window_handle[0], tile_handle[0], 1,2);
	vs_puts(window_handle[0], tile_handle[0], 1, 1, 50, white, black,
		"Type in a few sentences. (Scroll is off.)");
	
	/* Here is vs_gets */
	vs_gets(window_handle[0], tile_handle[0], SCROLL_OPTION_OFF, string,
		white, black, MAXIMUM_LENGTH);
	getchar();


	/* finish up with some pizzazzzzzzzzzzzzzzzz............ */

	wn_flybox(wdw[window_handle[0]]->physical_x,
		wdw[window_handle[0]]->physical_y,
		wdw[window_handle[0]]->port_rows,
		wdw[window_handle[0]]->port_columns,
		wdw[window_handle[0]]->physical_x +
		wdw[window_handle[0]]->port_columns/2,
		wdw[window_handle[0]]->physical_y +
		wdw[window_handle[0]]->port_rows/2,
		1, 1, 5, 50, box4, white, black);
	wn_delw(window_handle[0]);

	/* restore the characters to the original screen */
        wn_restorescr();

	/* restore the cursor position */
	v_gotoxy(oldx,oldy);

	/* restore the cursor shape */
	v_curshape(oldb, olde);

}
