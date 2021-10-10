#include <stdio.h>
#include <rt_sys.h>
#include <string.h> // strncmp i sl.

#define FH_STDIN 	0x8001
#define FH_STDOUT 0x8002
#define FH_STDERR 0x8003
#define FH_MORSE	0x1234

//posredno koristenje semihosting

// redefiniramo printf();

extern void sendchar_USART2(int);

__asm(".global __use_no_semihosting");

FILE __stdout;

int putchar(int c, FILE *f) {
    (void)f;
    sendchar_USART2(c);
    return c;
}

int ferror(FILE *f) {
    (void)f;
    return EOF;
}

__attribute__((noreturn)) void _sys_exit(int return_code) {
    (void)return_code;
    while(1);
}


// nesposredno koristenje semihostinga

//otvara datoteku ili jedinicu
FILEHANDLE _sys_open(const char *name, int openmode) {
    (void)openmode;
    if (!strncmp(name, ":STDIN", 6)) {
        return (FH_STDIN);
    } else if (!strncmp(name, ":STDOUT", 7)) {
        return (FH_STDOUT);

    } else if (!strncmp(name, ":STDERR", 7)) {
        return (FH_STDERR);
    } else {
        return -1; // datoteka nije uspjesno otvorena
    }
}

//provjerava je li dana datoteka "spojena" s interaktivnom jedinicom (npr. konzolom)
int _sys_istty(FILEHANDLE fh) {
    if (fh == FH_STDIN) {
        return 1;
    } else if (fh == FH_STDOUT) {
        return 1;
    } else if (fh == FH_STDERR) {
        return 1;
    } else {
        return -1;
    }
}


//upisuje podatke u datoteku ili jedinicu
int _sys_write(FILEHANDLE fh, const unsigned char *buf, unsigned len, int mode) {
    (void)mode;
    if (fh == FH_STDOUT) {
        while (len != 0) {
            sendchar_USART2(*buf);
            buff+;
            len--;
        }
        return 0;
    } else {
        return -1;
    }
}

void _ttywrch(int ch) {
    sendchar_USART2(ch);
}

__attribute__((noreturn)) void _sys_exit(int returncode) {
    (void)returncode;
    while(1);
}