#include "lp_libc.h"

int lp_memcmp(const void *, const void *, size_t);
char * lp_strdup(char *s);
void lp_strcpy(char *, char *);
int lp_strcmp(const char *, const char *);
int lp_strncmp(const char *s1, const char *s2, size_t n);
int lp_memcmp(const void *s1, const void *s2, unsigned int n);
char * lp_strrchr(const char *cp, int ch);
char *lp_strchr(const char *s, int c);
void lp_memcpy(void *, void *, unsigned int);
void lp_memset(void *, unsigned char, unsigned int);
int lp_printf(char *fmt, ...);
int lp_sprintf(char *, char *, ...);
char * lp_itoa(long x, char *t);
char * lp_itox(long x, char *t);
int lp_puts(char *str);
size_t lp_strlen(char *s);
void lp_exit(long);
void *lp_mmap(unsigned long, unsigned long, unsigned long, unsigned long,  long, unsigned long);
long lp_open(char *, unsigned long);
long lp_write(long, char *, unsigned long);
int lp_read(long, char *, unsigned long);
int lp_getpid(void);
int lp_getppid(void);
int lp_prctl(long, unsigned long, unsigned long, unsigned long, unsigned long);
void lp_exit(long);

int lp_printf(char *fmt, ...)
{
	int in_p;
	unsigned long dword;
	unsigned int word;
	char numbuf[26] = {0};
	__builtin_va_list alist;

	in_p;

	__builtin_va_start((alist), (fmt));

	in_p = 0;
	while(*fmt) {
		if (*fmt!='%' && !in_p) {
			_write(1, fmt, 1);
			in_p = 0;
		}
		else if (*fmt!='%') {
			switch(*fmt) {
				case 's':
					dword = (unsigned long) __builtin_va_arg(alist, long);
					_puts((char *)dword);
					break;
				case 'u':
					word = (unsigned int) __builtin_va_arg(alist, int);
					_puts(itoa(word, numbuf));
					break;
				case 'd':
					word = (unsigned int) __builtin_va_arg(alist, int);
					_puts(itoa(word, numbuf));
					break;
				case 'x':
					dword = (unsigned long) __builtin_va_arg(alist, long);
					_puts(itox(dword, numbuf));
					break;
				default:
					_write(1, fmt, 1);
					break;
			}
			in_p = 0;
		}
		else {
			in_p = 1;
		}
	    fmt++;
	}
	return 1;
}



char * lp_itoa(long x, char *t)
{
	int i;
	int j;

	i = 0;
	do
	{
		t[i] = (x % 10) + '0';
		x /= 10;
		i++;
	} while (x!=0);

	t[i] = 0;

	for (j=0; j < i / 2; j++) {
		t[j] ^= t[i - j - 1];
		t[i - j - 1] ^= t[j];
		t[j] ^= t[i - j - 1];
	}

	return t;
}


char * lp_itox(long x, char *t)
{
	int i;
	int j;

	i = 0;
	do
	{
		t[i] = (x % 16);

		/* char conversion */
		if (t[i] > 9)
			t[i] = (t[i] - 10) + 'a';
		else
			t[i] += '0';

		x /= 16;
		i++;
	} while (x != 0);

	t[i] = 0;

	for (j=0; j < i / 2; j++) {
		t[j] ^= t[i - j - 1];
		t[i - j - 1] ^= t[j];
		t[j] ^= t[i - j - 1];
	}

	return t;
}
long lp_write(long fd, char *buf, unsigned long len)
{
	long ret;
	__asm__ volatile(
			"mov %0, %%rdi\n"
			"mov %1, %%rsi\n"
			"mov %2, %%rdx\n"
			"mov $1, %%rax\n"
			"syscall" : : "g"(fd), "g"(buf), "g"(len));
	asm volatile("mov %%rax, %0" : "=r"(ret));
	return ret;
}

int lp_read(long fd, char *buf, unsigned long len)
{
	 long ret;
	__asm__ volatile(
			"mov %0, %%rdi\n"
			"mov %1, %%rsi\n"
			"mov %2, %%rdx\n"
			"mov $0, %%rax\n"
			"syscall" : : "g"(fd), "g"(buf), "g"(len));
	asm volatile ("mov %%rax, %0" : "=r"(ret));
	return (int)ret;
}

void lp_strcpy(char *dst, char *src)
{
	char *s = src;
	char *d = dst;
	
	while (*s) {
		*d = *s;
		d++, s++;
	}
	*d = '\0';
}
   
	
int lp_fsync(int fd)
{
	long ret;
	long scn = 74;

	asm volatile("syscall" : "=D"(fd), "=a"(scn));
	asm ("ret" : "=a"(ret)); 
	return (int)ret;
}

int lp_puts(char *str)
{
	_write(1, str, _strlen(str));
	_fsync(1);

	return 1;
}

size_t lp_strlen(char *s)
{
	size_t sz;

	for (sz=0;s[sz];sz++);
	return sz;
}

     
char *lp_strchr(const char *s, int c)
{
    const char ch = c;

    for ( ; *s != ch; s++)
	if (*s == '\0')
	    return 0;
    return (char *)s;
}

int lp_strncmp(const char *s1, const char *s2, size_t n)
{
    for ( ; n > 0; s1++, s2++, --n)
	if (*s1 != *s2)
	    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
	else if (*s1 == '\0')
	    return 0;
    return 0;
}

int lp_strcmp(const char *s1, const char *s2)
{
	int r = 0;

	while (!(r = (*s1 - *s2) && *s2))
		s1++, s2++;
	if (!r)
		return r;
	return r = (r < 0) ? -1 : 1;
}

int lp_memcmp(const void *s1, const void *s2, unsigned int n)
{
	unsigned char u1, u2;

	for ( ; n-- ; s1++, s2++) {
		u1 = * (unsigned char *) s1;
		u2 = * (unsigned char *) s2;
	if ( u1 != u2) {
		return (u1-u2);
	}
    }
    return 0;
}

void lp_memset(void *mem, unsigned char byte, unsigned int len)
{
	unsigned char *p = (unsigned char *)mem; 
	int i = len;
	while (i--) {
		*p = byte;
		p++;
	}
}


void lp_memcpy(void *dst, void *src, unsigned int len)
{
	int i;
	unsigned char *s = (unsigned char *)src;
	unsigned char *d = (unsigned char *)dst;

	for (i = 0; i < len; i++) {
		*d = *s;
		s++, d++;
	}

}

void lp_exit(long status)
{
	__asm__ volatile("mov %0, %%rdi\n"
			 "mov $60, %%rax\n"
			 "syscall" : : "r"(status));
}

long lp_open(char *path, unsigned long flags)
{
	long ret;
	__asm__ volatile(
			"mov %0, %%rdi\n"
			"mov %1, %%rsi\n"
			"mov $2, %%rax\n"
			"syscall" : : "g"(path), "g"(flags));
	asm __volatile__("mov %%rax, %0" : "=r"(ret));		    
	
	return ret;
}

int lp_close(unsigned int fd)
{
	long ret;
	long scn = 3;

	asm volatile("syscall" : "=D"(fd), "=a"(scn));
	asm volatile("mov %%rax, %0" : "=r"(ret));  
	return (int)ret;
} 



int lp_getuid(void)
{
	long ret;
	__asm__ volatile(
			"mov $102, %rax\n"
			"syscall");
	asm __volatile__("mov %%rax, %0" : "=r"(ret));

	return (int)ret;
}




int lp_getgid(void)
{
	long ret;
	__asm__ volatile(
			"mov $104, %rax\n"
			"syscall");
	asm __volatile__ ("mov %%rax, %0" : "=r"(ret));

	return (int)ret;
}



int lp_getegid(void)
{
	long ret;
	__asm__ volatile(
			"mov $108, %rax\n"
			"syscall");
	asm __volatile__ ("mov %%rax, %0" : "=r"(ret));

	return (int)ret;
}



int lp_geteuid(void)
{
	long ret;
	__asm__ volatile(
			"mov $107, %rax\n"
			"syscall");
	asm __volatile__ ("mov %%rax, %0" : "=r"(ret));
	
	return (int)ret;
}

long lp_lseek(long fd, long offset, unsigned int whence)
{
	long ret;
	long scn = 8;
  
	asm volatile("syscall" : "=D"(fd), "=S"(offset), "=d"(whence), "=a"(scn));
	asm __volatile__ ("mov %%rax, %0" : "=r"(ret));
	return ret;

}
	
int lp_mprotect(void * addr, unsigned int len, unsigned int prot)
{
	unsigned long ret;
	long scn = 10;

	asm volatile("syscall" : "=D"(addr), "=S"(len), "=d"(prot), "=a"(scn));
	asm __volatile__ ("mov %%rax, %0" : "=r"(ret));
	
	return (int)ret;
}

int lp_brk(void *addr)
{
	long ret;
	__asm__ volatile("mov %0, %%rdi\n"
			 "mov $12, %%rax\n"
			 "syscall" : : "g"(addr));
	asm __volatile__("mov %%rax, %0" : "=r"(ret));
	return (int)ret;
}

int lp_stat(char *path, struct stat *buf)
{
	long ret;
	__asm__ volatile(
			"mov %0, %%rdi\n"
			"mov %1, %%rsi\n"
			"mov $4, %%rax\n"
			"syscall\n" : : "g"(path), "g"(buf));
	asm __volatile__("mov %%rax, %0" : "=r"(ret));
	return (int)ret;
}


void *lp_mmap(unsigned long addr, unsigned long len, unsigned long prot,
	unsigned long flags, long fd, unsigned long off)
{
	long mmap_fd = fd;
	unsigned long mmap_off = off;
	unsigned long mmap_flags = flags;
	unsigned long ret;
	
	__asm__ volatile(
			 "mov %0, %%rdi\n"
			 "mov %1, %%rsi\n"
			 "mov %2, %%rdx\n"
			 "mov %3, %%r10\n"
			 "mov %4, %%r8\n"
			 "mov %5, %%r9\n"
			 "mov $9, %%rax\n"
			 "syscall\n" : : "g"(addr), "g"(len), "g"(prot), "g"(flags), "g"(mmap_fd), "g"(mmap_off));
	asm __volatile__ ("mov %%rax, %0" : "=r"(ret));		     
	return (void *)ret;
}

int lp_getpid(void)
{
	long ret;
	__asm__ volatile(
			"mov $39, %%rax\n"
			"syscall\n"
			"mov %%rax, %0" : "=g"(ret));
	return (int)ret;
}

int lp_getppid(void)
{
	long ret;
	__asm__ volatile(
			"mov $110, %%rax\n"
			"syscall\n" 
			"mov %%rax, %0" : "=g"(ret));
	return (int)ret;
}

void lp_exit(long status)
{
	 __asm__ volatile("mov %0, %%rdi\n"
			 "mov $60, %%rax\n"
			 "syscall" : : "r"(status));
}
