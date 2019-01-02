/* data associated with a keypress */
typedef struct {
	unsigned char ascii, scan, shift1, shift2;
} keypress;

extern unsigned int      EXPORT kb_getshift(void);
extern unsigned int      EXPORT kb_getxc(void);

/**** release 1.4 additions *****/
extern int 		 EXPORT kb_reset_keyboard_driver(void);
extern keypress 	 EXPORT kb_get_keypress(void);
extern int 		 EXPORT kb_set_keyboard_driver(void);
extern int 		 EXPORT kb_keypress_waiting(void);
