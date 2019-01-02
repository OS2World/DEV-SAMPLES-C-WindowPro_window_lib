#include <stdarg.h>

extern int 	EXPORT vs_insrow(unsigned int, unsigned char, int, int, int, int,
			int, unsigned char, unsigned char);
extern int 	EXPORT vs_inscolumn(unsigned int, unsigned char, int, int, int, int,
			int, unsigned char, unsigned char);
extern int 	EXPORT vs_delcolumn(unsigned int, unsigned char, int, int, int, int,
			int, unsigned char, unsigned char);
extern int 	EXPORT vs_delrow(unsigned int, unsigned char, int, int, int, int,
			int, unsigned char, unsigned char);
extern int 	EXPORT vs_fillchar(unsigned int, unsigned char, int, int, int, int,
			unsigned char, unsigned char, unsigned char);
extern int 	EXPORT vs_puts(unsigned int, unsigned char, unsigned int,
			unsigned int, unsigned int, unsigned char, unsigned char, char *);
extern int 	EXPORT vs_locatecur(unsigned int, unsigned char, unsigned int,
			unsigned int);
extern int 	EXPORT vs_clreol(unsigned int, unsigned char, unsigned char,
			unsigned char);
extern int 	EXPORT vs_clrbol(unsigned int, unsigned char, unsigned char,
			unsigned char);
extern int 	EXPORT vs_clrtoend(unsigned int, unsigned char, unsigned char,
			unsigned char);
extern int 	EXPORT vs_clrvs(unsigned int, unsigned char, unsigned char,
			unsigned char);
extern int 	EXPORT vs_printf(unsigned int, unsigned char, unsigned char,
			unsigned char, char *, ...);
extern int	EXPORT vs_putc(unsigned int, unsigned char, unsigned int,
			unsigned int, unsigned char, unsigned char, unsigned char);
extern int	EXPORT vs_gets(unsigned int, unsigned char, char, char *,
			unsigned char, unsigned char, int);
extern int 	EXPORT vs_fillattr(unsigned int, unsigned char, int, int, int, int,
			unsigned char, unsigned char);
extern int 	EXPORT vs_format(unsigned int, unsigned char, unsigned char,
			unsigned char, char *);
extern void EXPORT vs_drawbox(unsigned int, unsigned char, int, int, int, int,
			char, unsigned char *, unsigned char, unsigned char);

/*********** release 1.4 functions *************/
extern int 	EXPORT vs_putscenter(unsigned int, unsigned char, char *,
			unsigned char, unsigned char, int);

#ifdef OS2
#include "vs.mt"
#endif
