#include <portable.h>
#include <stdio.h>

#define WDW 			wdw[handle]
#define TILE 			wdw[handle]->tiles[tile_handle]
#define A_WDW 			wdw[active_wdw]
#define A_TILE 			wdw[active_wdw]->tiles[wdw[active_wdw]->active_tile]
#define VID_ACCESS 		((inp(0x03DA) & 0x01) == 0x01)
#define RETRACE 		((inp(0x03DA) & 0x08) == 0x08)
#define DMA				1
#define BIOS			2
#define ANSI			3
#define ERROR(errnum, functnum)	{wn_errorhandler(errnum,functnum); return(errnum);}
#define upcase(ch)		(((ch >=97) && (ch <=122)) ? ch - 32 : ch)

#define TRUE 				1
#define FALSE 				0
#define MAX_WINDOWS 		256
#define MAX_TILES 			10
#define UPPER_LEFT			1
#define UPPER_RIGHT			2
#define LOWER_LEFT			3
#define LOWER_RIGHT			4
#define HEAD_ON				5
#define NONE				0
#define NO_BARS				0
#define HORIZONTAL_BAR		1
#define VERTICAL_BAR		2
#define	BOTH_BARS			3
#define LEFT_JUSTIFY		0
#define CENTER_JUSTIFY		1
#define RIGHT_JUSTIFY		2

/* standard return codes */
#define ABORTED								1
#define CONFIRMED    						2
#define ASCENDED							3
#define DESCENDED							4
#define MOUSED								5
#define EXIT1								6
#define EXIT2								7
#define EXIT3								8
#define EXIT4								9
#define EXIT5								10
#define MENUED								11


/* screen char record */
typedef struct {
	unsigned char character;
	unsigned char attribute;
} screen_char;

/* tile record */
typedef struct {
	screen_char far *virtual_screen;
	char *tile_name;
	unsigned char forward, backward, scroll_bars, thumbwheel,
		suspend, border_color;
	int hide, port_rows, vs_rows, vs_columns,
		cursor_x, cursor_y, virtual_x, virtual_y, offset_y;
	double vertical_thumb, horizontal_thumb;
	char justify;
} tile_rec;

/* wdw record */
typedef struct {
	unsigned physical_x, physical_y, suspend, hide, border,
		forward, backward;
	unsigned char first_tile, last_tile, active_tile;
	int port_columns, port_rows;
	unsigned char border_color, *border_chars;
	char *wdw_name;
	tile_rec far *tiles[MAX_TILES + 1];
	char justify;
} wdw_rec;


/* block record */
typedef struct {
	unsigned x, y, rows, columns;
	screen_char far *buffer;
} blkrec;

#define SCR_SIZE 		(physical_rows * physical_columns * sizeof(screen_char))

/* Window and tile manipulation functions */
extern void 	EXPORT wn_errorhandler(signed int, signed int);
extern int 		EXPORT wn_delt(unsigned, unsigned char);
extern int 		EXPORT wn_actt(unsigned, unsigned char);
extern int 		EXPORT wn_updatew(unsigned);
extern int 		EXPORT wn_updatet(unsigned, unsigned char);
extern int 		EXPORT wn_closet(unsigned, unsigned char);
extern int 		EXPORT wn_openw(unsigned);
extern void 	EXPORT wn_flybox(int, int, int, int, int, int, int, int,
				unsigned, unsigned, unsigned char *, unsigned char,
				unsigned char);
extern void 	EXPORT wn_flyboxfilled(int, int, int, int, int, int, int, int,
				unsigned, unsigned, unsigned char *, unsigned char,
				unsigned char, unsigned char, unsigned char);
extern int 		EXPORT wn_delw(unsigned);
extern void		EXPORT wn_freeze(void);
extern void 	EXPORT wn_defrost(unsigned, unsigned, unsigned,
				unsigned);
extern int		EXPORT wn_init(void);
extern int		EXPORT wn_suspendw(unsigned);
extern int		EXPORT wn_actw(unsigned);
extern void		EXPORT wn_redraw(void);
extern int		EXPORT wn_draww(unsigned);
extern int		EXPORT wn_movew(unsigned, signed int, signed int);
extern int		EXPORT wn_locatew(unsigned, signed int, signed int);
extern int		EXPORT wn_zoomw(void);
extern int		EXPORT wn_createw(unsigned, unsigned, unsigned,
				unsigned, unsigned, unsigned, unsigned,
				unsigned, unsigned, unsigned, char *, char *);
extern int		EXPORT wn_createt(unsigned, char *, unsigned, unsigned,
				unsigned, unsigned);
extern int		EXPORT wn_suspendt(unsigned, unsigned char);
extern int		EXPORT wn_opent(unsigned, unsigned char);
extern int		EXPORT wn_scrollvs(unsigned, unsigned char,  signed int,
				signed int);
extern int 		EXPORT wn_sizet(unsigned, unsigned char, signed int,
				signed int);
extern int		EXPORT wn_namew(unsigned, char *);
extern int		EXPORT wn_namet(unsigned, unsigned char, char *);
extern int		EXPORT wn_chgbord(unsigned, unsigned char *);
extern int		EXPORT wn_closew(unsigned);
extern int		EXPORT wn_hidew(unsigned);
extern int		EXPORT wn_swapt(unsigned, unsigned char, unsigned,
				unsigned char);
extern int		EXPORT wn_togborder(unsigned, unsigned char);
extern void		EXPORT wn_restorescr(void);
extern void		EXPORT wn_savescr(void);
extern int		EXPORT wn_locatevs(unsigned, unsigned char, signed int,
				signed int);
extern int		EXPORT wn_moverng(unsigned, unsigned, signed int,
				signed int);
extern int		EXPORT wn_chgbordrng(unsigned, unsigned, unsigned char *);
extern int		EXPORT wn_sizerng(unsigned, unsigned, signed int,
				signed int);
extern int		EXPORT wn_chgcolor(unsigned, unsigned char,
				unsigned char);
extern int		EXPORT wn_chgcolorrng(unsigned, unsigned, unsigned char,
				unsigned char);
extern int		EXPORT wn_togbordrng(unsigned, unsigned, unsigned char);
extern void		EXPORT wn_hidecur(void);
extern void		EXPORT wn_showcur(void);
extern unsigned	EXPORT wn_isonwdw(unsigned, unsigned, unsigned *);
extern int 		EXPORT wn_togscrollrng(unsigned, unsigned, unsigned char);
extern int 		EXPORT wn_togscroll(unsigned, unsigned char, unsigned char);
extern int		EXPORT wn_isontile(unsigned, unsigned char *, unsigned,
				unsigned);
extern int		EXPORT wn_isonsbl(unsigned, unsigned char, unsigned,
				unsigned);
extern int		EXPORT wn_isonsbr(unsigned, unsigned char, unsigned,
				unsigned);
extern int		EXPORT wn_isonsbu(unsigned, unsigned char, unsigned,
				unsigned);
extern int		EXPORT wn_isonsbd(unsigned, unsigned char, unsigned,
				unsigned);
extern int		EXPORT wn_isonvlbar(unsigned, unsigned char, unsigned,
				unsigned);
extern int		EXPORT wn_isonvrbar(unsigned, unsigned char, unsigned,
				unsigned);
extern int		EXPORT wn_isonhbar(unsigned, unsigned char, unsigned,
				unsigned);
extern int		EXPORT wn_isonvs (unsigned, unsigned char, unsigned *,
				unsigned *);
extern int		EXPORT wn_isonurc(unsigned, unsigned, unsigned);
extern int		EXPORT wn_isonulc(unsigned, unsigned, unsigned);
extern int		EXPORT wn_isonlrc(unsigned, unsigned, unsigned);
extern int		EXPORT wn_isonllc(unsigned, unsigned, unsigned);
extern int		EXPORT wn_isonubar(unsigned, unsigned, unsigned);
extern int		EXPORT wn_isonlbar(unsigned, unsigned, unsigned);
extern int		EXPORT wn_isonrelb(unsigned, unsigned char, unsigned,
				unsigned);
extern int		EXPORT wn_isonlelb(unsigned, unsigned char, unsigned,
				unsigned);
extern int		EXPORT wn_isonnamew(unsigned, unsigned, unsigned);
extern int		EXPORT wn_isonnamet(unsigned, unsigned char, unsigned,
				unsigned);
extern int      EXPORT wn_isonhtw(unsigned, unsigned char, unsigned,
				unsigned);
extern int      EXPORT wn_isonvtw(unsigned, unsigned char, unsigned,
				unsigned);
extern int		EXPORT wn_whereon(unsigned *, unsigned char *, unsigned *,
				unsigned *);
extern int		EXPORT wn_edlin(unsigned, unsigned char, char **, char,
				int, int, int, int, int, unsigned char, unsigned char,
				int *);
extern int 		EXPORT wn_togscrollallt(unsigned, unsigned char);

/* release 1.3 functions */
extern int		EXPORT wn_movetwrel(unsigned, unsigned char, double, double);
extern int		EXPORT wn_movetwabs(unsigned, unsigned char, int, int);
extern int		EXPORT wn_locatetwrel(unsigned, unsigned char, double, double);
extern int		EXPORT wn_locatetwabs(unsigned, unsigned char, signed int, signed int);
extern int		EXPORT wn_sync_vs_to_tw(unsigned, unsigned char);
extern int		EXPORT wn_sync_tw_to_vs(unsigned, unsigned char);
extern int		EXPORT wn_togthumb(unsigned, unsigned char, unsigned char);

/* release 1.4 functions */
extern int 		EXPORT wn_copyw(unsigned);
extern int 		EXPORT wn_copyt(unsigned, unsigned char, unsigned);
extern int		EXPORT wn_openabst(unsigned, unsigned char, unsigned);
extern int		EXPORT wn_openrelt(unsigned, unsigned char, double);
extern int 		EXPORT wn_delrng(unsigned, unsigned);
extern int 		EXPORT wn_closerng(unsigned, unsigned);
extern int 		EXPORT wn_swapw(unsigned, unsigned);
extern int 		EXPORT wn_swapt2(unsigned, unsigned char, unsigned char);
extern int		EXPORT wn_draww_on_vs(unsigned, unsigned, unsigned char);
extern int 		EXPORT wn_putslist(char *[], unsigned char, unsigned char, int,
				int, int, char *, char*);

/* release 1.5 functions */
extern int		EXPORT vs_putattrs(unsigned, unsigned char, unsigned,
				unsigned, unsigned, screen_char far *);

/* release 1.6 functions */
extern void	EXPORT sleepmilli(unsigned long);

#ifdef OS2
#include "pro.mt"
#define kbhit	my_kbhit
#endif
