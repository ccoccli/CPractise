#include <sys_string.h>

sys_void *sys_memcpy(sys_void *dest, sys_void *src, sys_uint len)
{
  return memcpy(dest, src, len);
}

sys_int sys_atoi(sys_char *nptr)
{
  return atoi(nptr);
}

sys_void *sys_memset(sys_void *s, sys_int ch, size_t n)
{
  return memset(s, ch, n);
}

sys_int sys_memcmp(sys_void *buf1, sys_void *buf2, sys_uint count)
{
  return memcmp(buf1, buf2, count);
}

sys_void *sys_memmove(sys_void *dest, sys_void *src, sys_uint count)
{
  return memmove(dest, src, count);
}

sys_char *sys_strcpy(sys_char *dest, sys_char *src)
{
  return strcpy(dest, src);
}

sys_char *sys_strncpy(sys_char *dest, sys_char *src, sys_uint count)
{
  return strncpy(dest, src, count);
}

sys_int sys_strncmp(const sys_char *s1, const sys_char *s2, sys_int count)
{
  return strncmp(s1, s2, count);
}

sys_int sys_strcmp(const sys_char *s1, const sys_char *s2)
{
  return strcmp(s1, s2);
}

sys_void sys_strcat(sys_char *to, sys_char *from)
{
  strcat(to, from);
}

sys_char *sys_strstr(const sys_char *s1, const sys_char *s2)
{
  return strstr(s1, s2);
}

sys_int sys_abs(sys_int j)
{
  if (j >= 0)
  {
    return j;
  }
  else
  {
    return -j;
  }
}

sys_uint sys_strlen(sys_char *s)
{
  return strlen(s);
}

sys_int sys_sprintf(sys_char *str, sys_char *format, ...)
{
  va_list arg;
  sys_int rv;
  va_start(arg, format);
  rv = vsnprintf(str, 128, format, arg);
  va_end(arg);
  return rv;
}

sys_int sys_snprintf(sys_char *str, sys_uint nsize, sys_char *format, ...)
{
  va_list arg;
  sys_int rv;
  va_start(arg, format);
  rv = vsnprintf(str, nsize, format, arg);
  va_end(arg);
  return rv;
}

sys_int sys_sscanf(sys_char *buf, sys_char *fmt, sys_uint *val)
{
  return sscanf(buf, fmt, val);
}

sys_int sys_tolower(sys_int ch)
{
  return tolower(ch);
}
