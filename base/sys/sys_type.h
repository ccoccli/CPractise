#ifndef __SYS_TYPE_H__
#define __SYS_TYPE_H__
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <mqueue.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>


#include <sys_cfg.h>

#ifndef INVALID_VALUE
#define INVALID_VALUE 0xffffffff
#endif

typedef char sys_char;
typedef short sys_short;
typedef int sys_int;
typedef long sys_long;

typedef unsigned char sys_uchar;
typedef unsigned short sys_ushort;
typedef unsigned int sys_uint;
typedef unsigned long sys_ulong;

typedef signed char sys_schar;
typedef signed short sys_sshort;
typedef signed int sys_sint;
typedef signed long ssys_slong;

typedef double sys_double;
typedef long double sys_ldouble;
typedef float sys_float;

typedef bool sys_bool;
typedef void sys_void;
typedef void *sys_ptr;

#define sys_true true
#define sys_false false

#endif //__SYS_TYPE_H__