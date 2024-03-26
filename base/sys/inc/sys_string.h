#ifndef __SYS_STRING_H__
#define __SYS_STRING_H__

#include <sys_type.h>

sys_void *sys_memcpy(sys_void *dest, sys_void *src, sys_uint len);
sys_int sys_atoi(sys_char *nptr);
sys_void *sys_memset(sys_void *s, sys_int ch, size_t n);
sys_int sys_memcmp(sys_void *buf1, sys_void *buf2, sys_uint count);
sys_void *sys_memmove(sys_void *dest, sys_void *src, sys_uint count);
sys_char *sys_strcpy(sys_char *dest, sys_char *src);
sys_char *sys_strncpy(sys_char *dest, sys_char *src, sys_uint count);
sys_int sys_strncmp(const sys_char *s1, const sys_char *s2, sys_int count);
sys_int sys_strcmp(const sys_char *s1, const sys_char *s2);
sys_void sys_strcat(sys_char *to, sys_char *from);
sys_char *sys_strstr(const sys_char *s1, const sys_char *s2);
sys_int sys_abs(sys_int j);
sys_uint sys_strlen(sys_char *s);
sys_int sys_sprintf(sys_char *str, sys_char *format, ...);
sys_int sys_snprintf(sys_char *str, sys_uint nsize, sys_char *format, ...);
sys_int sys_sscanf(sys_char *buf, sys_char *fmt, sys_uint *val);
sys_int sys_tolower(sys_int ch);
#endif //__SYS_STRING_H__