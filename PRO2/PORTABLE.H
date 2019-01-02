/* define DOS or OS2 as target operating system */
#ifdef OS2

/* include the API call prototypes */
#define INCL_BASE

#endif

#include <os.h>

/* if compiling a DLL or compiling for use with a DLL use this */
#ifndef DL
#define EXPORT
#endif

#ifdef OS2
#ifdef DL
#define EXPORT	far _loadds
#endif
#endif
