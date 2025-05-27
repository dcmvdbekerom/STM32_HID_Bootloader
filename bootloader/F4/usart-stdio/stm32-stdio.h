


#ifndef STM32STDIO_H_
#define STM32STDIO_H_


//#include <libopencm3/stm32/usart.h>


/*
 * To implement the STDIO functions you need to create
 * the _read and _write functions and hook them to the
 * USART you are using. This example also has a buffered
 * read function for basic line editing.
 */
 
// int _close_r(struct _reent *r, int fd);

// int _fstat_r(struct _reent *r, int fd, struct stat *st);

// int _isatty_r(struct _reent *r, int fd);

// off_t _lseek_r(struct _reent *r, int fd, off_t pos, int whence);

 
 
int _write(int fd, char *ptr, int len);
int _read(int fd, char *ptr, int len);
void get_buffered_line(void);

#define BUFLEN 127

#endif // STM32STDIO_H_