#ifndef _KPRINTF_H
#define _KPRINTF_H

typedef unsigned char *va_list;
#define _INTSIZEOF(n) ((sizeof(n) + sizeof(unsigned int) - 1) & ~(sizeof(unsigned int) - 1))
#define va_start(ap, v) (ap = (va_list)&v + _INTSIZEOF(v))
#define va_arg(ap, t) (*(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)))
#define va_end(ap) (ap = (va_list)0)


int kputint(int i, int try_scan_num);
int kvprintf(const char *format, va_list ap);
int kprintf(const char *format, ...);

int test_printf();

#endif //_KPRINTF_H
