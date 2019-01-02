extern unsigned EXPORT RetClrSem(unsigned);

#define REQ										DosSemRequest(wpsemsys,2000L)
#define CLR										DosSemClear(wpsemsys)
#ifdef MT
#define	vs_insrow(a,b,c,d,e,f,g,h,i)			(REQ,(int)RetClrSem((int)vs_insrow(a,b,c,d,e,f,g,h,i)))
#define	vs_inscolumn(a,b,c,d,e,f,g,h,i)			(REQ,(int)RetClrSem((int)vs_inscolumn(a,b,c,d,e,f,g,h,i)))
#define	vs_delcolumn(a,b,c,d,e,f,g,h,i)			(REQ,(int)RetClrSem((int)vs_delcolumn(a,b,c,d,e,f,g,h,i)))
#define	vs_delrow(a,b,c,d,e,f,g,h,i)			(REQ,(int)RetClrSem((int)vs_delrow(a,b,c,d,e,f,g,h,i)))
#define	vs_fill(a,b,c,d,e,f,g,h,i,j)			(REQ,(int)RetClrSem((int)vs_fill(a,b,c,d,e,f,g,h,i,j)))
#define	vs_puts(a,b,c,d,e,f,g,h)				(REQ,(int)RetClrSem((int)vs_puts(a,b,c,d,e,f,g,h)))
#define	vs_locatecur(a,b,c,d)					(REQ,(int)RetClrSem((int)vs_locatecur(a,b,c,d)))
#define	vs_clreol(a,b,c,d)						(REQ,(int)RetClrSem((int)vs_clreol(a,b,c,d)))
#define	vs_clrbol(a,b,c,d)						(REQ,(int)RetClrSem((int)vs_clrbol(a,b,c,d)))
#define	vs_clrtoend(a,b,c,d)					(REQ,(int)RetClrSem((int)vs_clrtoend(a,b,c,d)))
#define	vs_clrvs(a,b,c,d)						(REQ,(int)RetClrSem((int)vs_clrvs(a,b,c,d)))
#define vs_putc(a,b,c,d,e,f,g)					(REQ,(int)RetClrSem((int)vs_putc(a,b,c,d,e,f,g)))
#define	vs_gets(a,b,c,d,e,f,g)					(REQ,(int)RetClrSem((int)vs_gets(a,b,c,d,e,f,g)))
#define	vs_fillattr(a,b,c,d,e,f,g,h)			(REQ,(int)RetClrSem((int)vs_fillattr(a,b,c,d,e,f,g,h)))
#define	vs_format(a,b,c,d,e)					(REQ,(int)RetClrSem((int)vs_format(a,b,c,d,e)))
#define	vs_drawbox(a,b,c,d,e,f,g,h,i,j)			{REQ,vs_drawbox(a,b,c,d,e,f,g,h,i,j),CLR}
#define	vs_putscenter(a,b,c,d,e,f)				(REQ,(int)RetClrSem((int)vs_putscenter(a,b,c,d,e,f)))
#endif
