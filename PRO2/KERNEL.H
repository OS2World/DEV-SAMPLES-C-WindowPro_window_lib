/*
Warning !! WINDOW PRO kernel functions -- applications programmers should
not use these without a thorough understanding of the design.
*/
extern void	 EXPORT k_fmemcpy(void far *, void far *, unsigned int);
extern void	far * EXPORT k_malloc(unsigned int);
extern int	 EXPORT k_free(void far *);
extern int	 EXPORT k_freet(unsigned int, unsigned char);
extern int	 EXPORT k_freeallt(unsigned int);
extern int	 EXPORT k_dispcur(void);
extern int	 EXPORT k_restoreblk(blkrec far *);
extern blkrec	far * EXPORT k_saveblk(unsigned int, unsigned int, unsigned int,
				unsigned int);
extern void	 EXPORT k_restorew(void);
extern int	 EXPORT k_drawbordw(unsigned int);
extern int	 EXPORT k_drawbordt(unsigned int, unsigned char);
extern int	 EXPORT k_savew(void);
extern int	 EXPORT k_gethdlt(unsigned int);
extern int	 EXPORT k_gethdlw(void);
extern void  EXPORT k_drawbox(int, int, int, int, unsigned char, unsigned char *,
			unsigned char, unsigned char);
extern int	 EXPORT k_scrmemcpy(void far *, void far *, unsigned int, unsigned int,
			unsigned int);
extern int	 EXPORT k_scrmemcpyout(void far *, unsigned int, unsigned int, void far *,
			unsigned int);
extern int 	 EXPORT k_invport(unsigned int, unsigned char, unsigned int,
			unsigned int);
extern int 	 EXPORT k_coveredw(unsigned int);
extern int 	 EXPORT k_coveredt(unsigned int, unsigned char);
extern int 	 EXPORT k_showsw(unsigned int);
extern int 	 EXPORT k_showst(unsigned int, unsigned char);
extern int 	 EXPORT k_coveredlp(unsigned int, unsigned char, unsigned int,
			unsigned int);
extern int 	 EXPORT k_showslp(unsigned int, unsigned char, unsigned int,
			unsigned int);
extern void  EXPORT k_setcoordw(unsigned int, int *, int *, int *, int *);
extern int 	 EXPORT k_in(int, int, int, int, int, int, int, int);
extern int 	 EXPORT k_out(int, int, int, int, int, int, int, int);
extern int	 EXPORT k_checklocw(unsigned int);
extern int	 EXPORT k_checkvcoord(unsigned int, unsigned char);
extern void  EXPORT k_freeblk(blkrec far *);
extern void  EXPORT k_hidecur(void);
extern void  EXPORT k_showcur(void);
extern int   EXPORT k_getcoordsrng(unsigned int, unsigned int, unsigned int *,
			unsigned int *, unsigned int *, unsigned int *);
extern void  EXPORT k_updatescr(unsigned int, unsigned char, signed int,
			signed int, signed int, signed int, char);
extern int 	 EXPORT k_drawscrollbars(unsigned int, unsigned char);
extern int	 EXPORT k_copyt(unsigned int, unsigned char, unsigned int);
extern long int  EXPORT k_getsyscount(void);
