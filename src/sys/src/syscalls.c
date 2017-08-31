/**
 * @Author: Diego Asanza <diego>
 * @Date:   December 09, 2016
 * @Email:  f.asanza@gmail.com
 * @Last modified by:   diego
 * @Last modified time: December 09, 2016
 * @License: * Copyright (c) 2015, Diego F. Asanza. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 */

/* Includes */
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

/* Reserve at least STACK_BUFFER bytes for stack usage */
#define MIN_STACK_SIZE 1024
#define STACK_BUFFER MIN_STACK_SIZE

static uint32_t avail_heap_space;

/* We use the errno variable used by the system dependent layer.  */
#undef errno
extern int errno;

int _getpid(void)
{
	return 1;
}

int _kill(int pid, int sig)
{
	errno = EINVAL;
	return -1;
}

void _exit(int status)
{
	_kill(status, -1);
	while (1) {
	}                       /* Make sure we hang here */
}

int _read(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		//*ptr++ = __io_getchar();
	}

	return len;
}

int _write(int file, char *ptr, int len)
{
	int DataIdx;

	// for (DataIdx = 0; DataIdx < len; DataIdx++)
	// 	brd_uart_write( HAL_UART_0, *ptr++ );
	return len;
}

int system_get_free_heap_size(void)
{
	int val;

	val = avail_heap_space - STACK_BUFFER;

	return val;
}

caddr_t _sbrk(int nbytes)
{
	extern uint32_t __stack;
	extern char end;

	/* The statically held previous end of the heap, with its initialization. */
	static char *heap_ptr = (char*)&end;    /* Previous end */
	static char *stack_ptr = (char*)&__stack;

	if ((stack_ptr - (heap_ptr + nbytes)) > STACK_BUFFER ) {
		caddr_t base  = heap_ptr;
		heap_ptr += nbytes;
		avail_heap_space = stack_ptr - heap_ptr;
		return base;
	}else {
		errno = ENOMEM;
		return (caddr_t)-1;
	}
}

int _close(int file)
{
	return -1;
}


int _fstat(int file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int _isatty(int file)
{
	return 1;
}

int _lseek(int file, int ptr, int dir)
{
	return 0;
}

int _open(char *path, int flags, ...)
{
	/* Pretend like we always fail */
	return -1;
}

int _wait(int *status)
{
	errno = ECHILD;
	return -1;
}

int _unlink(char *name)
{
	errno = ENOENT;
	return -1;
}

int _times(struct tms *buf)
{
	return -1;
}

int _stat(char *file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int _link(char *old, char *new)
{
	errno = EMLINK;
	return -1;
}

int _fork(void)
{
	errno = EAGAIN;
	return -1;
}

int _execve(char *name, char **argv, char **env)
{
	errno = ENOMEM;
	return -1;
}

#if DEBUG
void __error__(char *pcFilename, unsigned long ulLine)
{
	printf("%s, %ld\n", pcFilename, ulLine);
}
#else
void __error__(char *pcFilename, unsigned long ulLine)
{

}
#endif

void __cxa_pure_virtual()
{
	//assert(0 && "pure virtual func called");
}
