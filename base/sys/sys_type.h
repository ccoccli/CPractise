#ifndef __SYS_TYPE_H__
#define __SYS_TYPE_H__
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
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

#endif //__SYS_TYPE_H__