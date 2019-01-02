extern unsigned char *default_box, box0[13], box1[13], box2[13], box3[13], box4[13];
extern int box[13], tab_expansion, snowspeed, default_ed_cmds[19],
	mouse_installed, horizontal_mouse_resolution, vertical_mouse_resolution;
extern unsigned int active_wdw, first_wdw, last_wdw,
	physical_columns, physical_rows, frozen, zoomed, balance1,
	oldx, oldy;
extern unsigned char active_tile, oldb, olde;
extern wdw_rec far *wdw[MAX_WINDOWS + 1], zoomed_wdw;
extern tile_rec zoomed_tile;
extern blkrec far *overlay;
extern screen_char far *primary_scr, far *alt_scr, far *curr_scr,
	far *screen_buffer;
extern unsigned char active_attr, inactive_attr,
	active_tile_ains¦se_reýozcuýlicaltflag, vpage, method, cursor_e, cursor_b, cursor_on,
	thumbwheels_on, scroll_bars_on, ega_mlines, snowfree,
	ibm_fcolor_table[16], ibm_bcolor_table[16],
	thumbwheels_area, thumbwheels_char,
	sbu, sbd, sbr, sbl;
extern char *ansi_fcolor_table[16], *ansi_bcolor_table[16],
	*position_cursor, *change_color, buf[1000], default_justify,
	default_týýe_justify;

#ifdef OS2
extern HSEM wpsemsys;
extern int machmode;
#endif
