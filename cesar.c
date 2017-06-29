#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 2048
#define CASE_CHARSET_SIZE 26

#define MOD(a, m) ((a % m + m) % m)
#define SHIFT_OF(i) (1)
#define NORMALIZE(c) (c - ('a' <= c? 'a' : 'A'))
#define TRANSFORM(c, base)  (c + ('a' <= base? 'a' : 'A'))
#define DIE(errnum) errno = errnum, perror("fatal"), exit(1);

void encrypt(char *s, int n) {
  register int i;
  register char c;

  for (i=0; i < n; ++i) {
    c = NORMALIZE(s[i]);
    c = MOD(c + SHIFT_OF(i), CASE_CHARSET_SIZE);
    c = TRANSFORM(c, s[i]);
    s[i] = c;
  }
}

void decrypt(char *s, int n) {
  register int i;
  register char c;

  for (i=0; i < n; ++i) {
    c = NORMALIZE(s[i]);
    c = MOD(c - SHIFT_OF(i), CASE_CHARSET_SIZE);
    c = TRANSFORM(c, s[i]);
    s[i] = c;
  }

}

void parse_stdin(char **buf, size_t *n) {  
  size_t i;

  /* strip first byte */
  *n -= 1;
  *buf += 1;

  /* set n to num of alpha chars from 0 */
  for (i=0; i < *n; ++i) {
    if (**buf < 'A' || **buf > 'z')
      break;
  }

  *n = --i;
}

int main(void) {
  size_t n;
  char *buf = malloc(BUFSIZE);

  n = read(STDIN_FILENO, buf, BUFSIZE-1);
  if (!n) {
    DIE(EINVAL);
  }
  *(buf+n+1) = 0;

  switch(*buf) {
    case 'e':
      parse_stdin(&buf, &n);
      encrypt(buf, n);
      break;
    case 'd':
      parse_stdin(&buf, &n);
      decrypt(buf, n);
      break;
    default:
      DIE(EINVAL);
  }
  puts(buf);
}
