#include <errno.h>
#include <sys/stat.h>

extern unsigned long _ebss;
char *__brkval = (char *)&_ebss;

#ifndef STACK_MARGIN
#define STACK_MARGIN  8192
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

__attribute__((weak)) 
void * _sbrk(int incr)
{
	char *prev, *stack;

	prev = __brkval;
	if (incr != 0) {
		__asm__ volatile("mov %0, sp" : "=r" (stack) ::);
		if (prev + incr >= stack - STACK_MARGIN) {
			errno = ENOMEM;
			return (void *)-1;
		}
		__brkval = prev + incr;
	}
	return prev;
}

__attribute__((weak)) 
int _read(int file, char *ptr, int len)
{
	return 0;
}
__attribute__((weak))
int _write(int file, char *ptr, int len)
{
	return 0;
}

__attribute__((weak)) 
int _close(int fd)
{
	return -1;
}

__attribute__((weak)) 
int _fstat(int fd, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

__attribute__((weak)) 
int _isatty(int fd)
{
	return 1;
}

__attribute__((weak)) 
int _lseek(int fd, long long offset, int whence)
{
	return -1;
}

__attribute__((weak)) 
void _exit(int status)
{
	while (1);
}

__attribute__((weak)) 
void __cxa_pure_virtual()
{
	while (1);
}

__attribute__((weak)) 
int __cxa_guard_acquire (char *g) 
{
	return !(*g);
}

__attribute__((weak)) 
void __cxa_guard_release(char *g)
{
	*g = 1;
}

__attribute__((weak))
void abort(void)
{
	while (1) ;
}

#pragma GCC diagnostic pop
