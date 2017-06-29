#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define BUFSIZE 2048
#define DIE(errnum) errno = errnum, perror("fatal"), exit(1);

#define CASE_CHARSET_SIZE 26
#define AFFINE_A 25 /*must be coprime with alphabet length*/
#define AFFINE_A_INVMOD 25 /*modular multiplicative inverse of AFFINE_A*/
#define AFFINE_B 3

#define MOD(a, m) (a % m + m) % m

#define AFFINE_ENCRYPT(x) (AFFINE_A * x + AFFINE_B)

#define AFFINE_DECRYPT(x) (AFFINE_A_INVMOD * (x - AFFINE_B))

#define NORMALIZE(c) MOD(abs(c - (c >= 'a'? 'a': 'A')), 26)
#define TRANSFORM(c, base)  (char)(c + (base >= 'a'? 'a':'A'))

#define BYPASS_NON_ALPHA(c) if (c < 'A' || 'Z' < c) { s[i] = c; continue; } 



void encrypt(char *s, int n) {
  register int i;
  register char c;

  for (i=0; i < n; ++i) {
    BYPASS_NON_ALPHA(s[i]);
    c = NORMALIZE(s[i]);
    c = AFFINE_ENCRYPT(c) % CASE_CHARSET_SIZE;
    c = TRANSFORM(c, s[i]);
    s[i] = c;
  }
}

void decrypt(char *s, int n) {
  register int i;
  register char c;

  for (i=0; i < n; ++i) {
    BYPASS_NON_ALPHA(s[i]);
    c = NORMALIZE(s[i]);
    c = MOD(AFFINE_DECRYPT(c), CASE_CHARSET_SIZE);
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
    if (**buf < 'A' || 'z' < **buf )
      break;
  }

  *n = i;
}

int main(void) {
  size_t n;
  char *buf = malloc(BUFSIZE);

  n = read(STDIN_FILENO, buf, BUFSIZE-1);
  if (n < 1) {
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
  write(STDOUT_FILENO, buf, n);
}
