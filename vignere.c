#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define KEY_CHARSET "QWERTYUIOPASDFGHJKLZXCVBNM"
#define MAX_MSG_SIZE 2048
#define BUFSIZE (MAX_MSG_SIZE * 2)
#define DIE(errnum) { errno = errnum; perror("fatal"); exit(1); };

static inline int _alpha_shift(int i, char *key, int keylen) {
  register int key_index, shift;
  key_index = i % keylen;
  shift = *(key + key_index)  - 'A';
  return shift;
}

void vi_encrypt(char *dest, char *key, char *msg_start) {
  char *msg_end =  msg_start + strnlen(msg_start, MAX_MSG_SIZE), 
       *msg = msg_start;
  int keylen = strnlen(key, MAX_MSG_SIZE);
  int i = 0;
  for (; msg < msg_end; ++msg, ++dest) {
    if (*msg < 'A' || 'Z' < *msg) {
      *dest = *msg;
      continue;
    }
    *dest = 'A' + (*msg - 'A' + _alpha_shift(i, key, keylen)) %26;
    ++i;
  }
}

void vi_decrypt(char *dest, char *key, char *msg_start) {
  char *msg_end =  msg_start + strnlen(msg_start, MAX_MSG_SIZE), 
       *msg = msg_start;
  int keylen = strnlen(key, MAX_MSG_SIZE);
  int i = 0;
  for (; msg < msg_end; ++msg, ++dest) {
    if (*msg < 'A' || 'Z' < *msg) {
      *dest = *msg;
      continue;
    }
    *dest = 'A' + ((*msg - 'A' - _alpha_shift(i, key, keylen)) % 26 + 26) % 26;
    ++i;
  }
}

void _parse_stdin(char **key, char **msg, char *buf) {
  char *sep, *bound = buf + BUFSIZE;
  ++buf;
  if (*buf != '\n' && *buf != ' ')
    DIE(EINVAL);
  ++buf;
  *key = buf;
  sep = buf + strspn(buf, KEY_CHARSET);
  if (!sep || sep > bound) {
    DIE(EINVAL);
  }
  *sep = 0;
  *msg = sep+1;
#ifdef DEBUG
  printf("msg %s\nkey %s\n", *msg, *key);
#endif
}

int main(void) {
  char *buf = calloc(2, MAX_MSG_SIZE), 
       *dest = calloc(1, MAX_MSG_SIZE),
       *key=0,
       *msg=0;
  if (!read(STDIN_FILENO, buf, MAX_MSG_SIZE*2))
    DIE(EAGAIN)

  switch (*buf) { 
    case 'e':
      _parse_stdin(&key, &msg, buf);
      vi_encrypt(dest, key, msg);
      break;
    case 'd':
      _parse_stdin(&key, &msg, buf);
      vi_decrypt(dest, key, msg);
      break;
    default:
      puts("stdin must be:\n  e KEY MESSAGE\n  -or-\n  d KEY MESSAGE");
      DIE(EINVAL);
      break;
  }
#ifdef DEBUG
  printf("%s\n", dest);
#else
  printf("%s\n", dest);
#endif
  return 0;
}
