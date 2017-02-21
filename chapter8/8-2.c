#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include <unistd.h>

#define EOF (-1)
#define OPEN_MAX 20 // Maximum files that can be open
#define PERMS 0666

typedef struct _flags{
    int _READ;
    int _WRITE;
    int _UNBUF;
    int _EOF;
    int _ERR;
} flags;

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    struct _flags flags;
    int fd;
} FILEx;

FILEx _iob[OPEN_MAX];
int _fillbuffx(FILEx *f);

#define getcx(p) (--(p)->cnt >= 0? (unsigned char) *(p)->ptr++:_fillbufx(p))

int is_empty(struct _flags flags) {
    if(!flags._READ && !flags._WRITE && !flags._UNBUF &&
        !flags._EOF && !flags._ERR)
        return 1;
    return 0;
}

FILEx *fopenx(char *name, char *mode) {
    int fd;
    FILEx *fp;
    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    // Check for free slot
    for (fp= _iob; fp< _iob + OPEN_MAX ; fp++)
        if(is_empty(fp->flags))
            break;

    if (fp>= _iob+OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1) return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    if(*mode == 'r')
		fp->flags._READ = 1;
	else
		fp->flags._WRITE = 1;
	return fp;
}

int _fillbufx(FILEx *fp) {
    int bufsize;
    if (fp->flags._READ == 0) return EOF;
    bufsize = (fp->flags._UNBUF != 0) ? 1:BUFSIZ;
    if (fp->base == NULL)
        if((fp->base = (char *) malloc (bufsize))==NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp -> cnt < 0) {
        if(fp->cnt == -1)
			fp->flags._EOF=1;
		else
			fp->flags._ERR=1;
		fp->cnt = 0;
		return EOF;
    }
    return (unsigned char) *fp->ptr++;

}

int main(int argc, char const *argv[]) {
    FILEx *fp = fopenx("8-1.c","r");
	if(fp!=NULL){
		char c;
		// getcx is a macro defined above
		while((c=getcx(fp))!=EOF)
			putchar(c);
	}
	else
		puts("Error");
	return 0;
}
