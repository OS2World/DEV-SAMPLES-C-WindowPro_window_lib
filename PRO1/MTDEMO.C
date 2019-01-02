#include "pro.h"
#include "xglobals.h"
#include "colors.h"
#include "vs.h"
#include "video.h"
#include "werrors.h"
#include <process.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void far p1(void far *);
void far p2(void far *);
void far p3(void far *);

#define STACKSIZE 	2048
#define NUMWDWS 	3

main()
{
	void far *stackbottom[NUMWDWS * 3];
	int i;
	unsigned handle[NUMWDWS];
	char name[3];

	v_gotoxy(0,24);
	printf("Press any key to stop ...");

	wn_init();

	/* output to virtual screens */
	for(i = 0; i < NUMWDWS; i++) {
		stackbottom[i] = _fmalloc(STACKSIZE);
		sprintf(name,"%d",i);
		handle[i] = wn_createw(20,24, (i * (physical_columns/NUMWDWS))+1,1,1,1,10,12,FALSE,HEAD_ON,strdup(name),NULL);
		wn_openw(handle[i]);
		_beginthread(p1,stackbottom[i],STACKSIZE,(void far *) handle[i]);
	}

	/* move windows */
	for(i = 0; i < NUMWDWS; i++) {
		stackbottom[i+NUMWDWS] = _fmalloc(STACKSIZE);
		_beginthread(p2,stackbottom[i+NUMWDWS],STACKSIZE,(void far *) handle[i]);
	}

	/* scroll virtual screens */
	for(i = 0; i < NUMWDWS; i++) {
		stackbottom[i+NUMWDWS*2] = _fmalloc(STACKSIZE);
		_beginthread(p3,stackbottom[i+NUMWDWS*2],STACKSIZE,(void far *) handle[i]);
	}
	getch();
	v_gotoxy(oldx,oldy);
	wn_restorescr();
}

void p1(v)
void far *v;
{
	int count = 0;
	while(1) {
		REQ;
		vs_printf((unsigned) v,0,white,black,"count = %d\n",count++);
		CLR;
	}
}

void p2(v)
void far *v;
{
	int a;
	unsigned handle = (unsigned) v;

	a = 1;
	while(1) {
		switch(a) {
			case 1 :
				if (wn_movew(handle, 0, 1) == MODIFIED) a = 2;
				break;
			case 2 :
				if (wn_movew(handle, 1, 0) == MODIFIED) a = 3;
				break;
			case 3 :
				if (wn_movew(handle, 0, -1) == MODIFIED) a = 4;
				break;
			case 4 :
				if (wn_movew(handle, -1, 0) == MODIFIED) a = 1;
				break;
		}
	}
}

void p3(v)
void far *v;
{
	int a;
	unsigned handle = (unsigned) v;

	a = 1;
	while(1) {
		switch(a) {
			case 1 :
				if (wn_scrollvs(handle, 0, 0, 1) == MODIFIED) a = 2;
				break;
			case 2 :
				if (wn_scrollvs(handle, 0, 1, 0) == MODIFIED) a = 3;
				break;
			case 3 :
				if (wn_scrollvs(handle, 0, 0, -1) == MODIFIED) a = 4;
				break;
			case 4 :
				if (wn_scrollvs(handle, 0, -1, 0) == MODIFIED) a = 1;
				break;
		}
		wn_sync_tw_to_vs(handle,0);
	}
}

