#include <stdio.h> // decl. of FILE, __stdin, __stdout
#include <rt_sys.h> // declaration of _sys_exit, etc.

extern void sendchar_USART2(int);

FILEHANDLE _sys_open(const char *, int);
int _sys_istty(FILEHANDLE);
int _sys_write(FILEHANDLE, const unsigned char *, unsigned, int);
void _ttywrch (int);
int _sys_close (FILEHANDLE);

//int fputc(int c, FILE *f);
//int ferror(FILE *f);
__attribute__((noreturn)) void _sys_exit(int return_code);