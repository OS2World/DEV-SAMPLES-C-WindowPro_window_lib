extern int       EXPORT kb_ismouse(void);
extern void      EXPORT kb_resetmouse(void);
extern void      EXPORT kb_showmouse(void);
extern void      EXPORT kb_hidemouse(void);
extern void      EXPORT kb_mousestatus(int *, int *, int *);
extern void      EXPORT kb_putmouse(int, int);
extern void      EXPORT kb_mousepressed(int *, int *, int *, int *);
extern void      EXPORT kb_mousereleased(int *, int *, int *, int *);
extern void      EXPORT kb_setmousexrange(int, int);
extern void      EXPORT kb_setmouseyrange(int, int);
extern void      EXPORT kb_setgraphicsicon(int *, int *, int *);
extern void      EXPORT kb_settextcursor(int, int, int);
extern void      EXPORT kb_mousemotion(int *, int *);
extern void      EXPORT kb_mousemickeys(int, int);
extern void      EXPORT kb_mousedst(int);
extern int 	 EXPORT kb_mouseclicks(int, int, unsigned int *, unsigned int *);
extern void	 EXPORT kb_convertcoords(unsigned int *,unsigned int *);

extern int prev_click;
extern unsigned int prev_x, prev_y;

#define DOUBLECLICK			1
#define CLICK				2
#define PRESS				3
#define RELEASE				4
#define HOLDING				5


#ifdef OS2
extern USHORT mouse_handle;
#endif
