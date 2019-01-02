/* lowlevel video functions */
extern void 	EXPORT v_gotoxy(unsigned int, unsigned int);
extern void 	EXPORT v_curshape(char, char);
extern int      EXPORT v_getmode(void);
extern int      EXPORT v_getpage(void);
extern int      EXPORT v_getwidth(void);
extern int 		EXPORT v_setmode(char);
extern void 	EXPORT v_putchar(int, int, char, char);
extern int 		EXPORT v_getchar(int, int);
extern void 	EXPORT v_cursor_report(unsigned int *, unsigned int *,
		unsigned char *, unsigned char *);

/**** release 1.4 functions ******/
extern void		EXPORT v_setega43(void);
extern void		EXPORT v_setega25(void);
extern void     EXPORT v_fixupega25cursor(char, char);
extern void     EXPORT v_fixupega43cursor(char, char);

