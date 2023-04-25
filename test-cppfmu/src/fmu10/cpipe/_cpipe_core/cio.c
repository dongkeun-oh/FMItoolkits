#include <stdio.h>
#include <string.h>

#if defined (_WIN32) || defined (WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
  #include <io.h>
  #include <fcntl.h>
#endif

#if defined (NOT_GFOTRAN) 
  #define FNAME(a)  a
#else
  #define FNAME(a)  a ## _
#endif

void FNAME(ioclear)(void);
void FNAME(iobinmode)(void);
void FNAME(iotxtmode)(void);
void FNAME(iordint)(int *, int *);
void FNAME(iowtint)(int *, int *);
void FNAME(iorddata)(double *, int *, int *);
void FNAME(iowtdata)(double *, int *, int *);


void FNAME(ioclear)(void) {
	FNAME(iotxtmode)();
	fflush(stdin);
	fflush(stdout);
	return;
}


void FNAME(iobinmode)(void) {
#if defined (_WIN32) || defined (WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    _setmode(_fileno(stdin), _O_BINARY);    
    _setmode(_fileno(stdout), _O_BINARY);
#endif
    return;
}


void FNAME(iotxtmode)(void) {
#if defined (_WIN32) || defined (WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    _setmode(_fileno(stdin), _O_TEXT);
    _setmode(_fileno(stdout), _O_TEXT);
#endif
    return;
}


void FNAME(iordint)(int *data, int *status) {
#if defined (_WIN32) || defined (WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    _setmode(_fileno(stdin), _O_BINARY);
#endif
    *status = fread( (void *) data, sizeof(int), 1, stdin);	
	if (*status ==  1) *status = 0;
    else *status = -1;
#if defined (_WIN32) || defined (WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    _setmode(_fileno(stdin), _O_TEXT);
#endif
    return;
    }


void FNAME(iowtint)(int *data, int *status) {
#if defined (_WIN32) || defined (WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    _setmode(_fileno(stdout), _O_BINARY);
#endif
    *status = fwrite( (void *) data, sizeof(int), 1, stdout);	
    fflush(stdout);
    if (*status ==  1) *status = 0;
    else *status = -1;
#if defined (_WIN32) || defined (WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    _setmode(_fileno(stdout), _O_TEXT);
#endif
    return;
    }


void FNAME(iorddata)(double *data, int *n, int *status) {
#if defined (_WIN32) || defined (WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    _setmode(_fileno(stdin), _O_BINARY);
#endif
    *status = fread( (void *) data, sizeof(double), *n, stdin);
    if (*status ==  *n)  *status = 0;
    else *status = -1;
#if defined (_WIN32) || defined (WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    _setmode(_fileno(stdout), _O_TEXT);
#endif    
    return;
}


void FNAME(iowtdata)(double *data, int *n, int *status) {
#if defined (_WIN32) || defined (WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    _setmode(_fileno(stdout), _O_BINARY);
#endif
    *status = fwrite( (void *) data, sizeof(double), *n, stdout);
    fflush(stdout);
    if (*status ==  *n) *status = 0;
    else *status = -1;
#if defined (_WIN32) || defined (WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    _setmode(_fileno(stdout), _O_TEXT);
#endif     
    return;
}
