#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define BUFSIZE 4096
#define IDX(i) (i % BUFSIZE)

static inline void
write_wchars(wchar_t buf[], size_t start, size_t end, bool escape,
             bool open_field, bool close_field) {
  size_t j;
  if (escape) {
    if (open_field)
      putwchar(L'"');
    for (j = start; j <= end; ++j) {
      if (buf[IDX(j)] == L'"')
        putwchar(L'"');
      if (putwchar(buf[IDX(j)]) == WEOF) {
        fprintf(stderr, "putwchar error");
        exit(1);
      }
    }
    if (close_field)
      putwchar(L'"');
  } else {
    for (j = start; j <= end; ++j) {
      if (putwchar(buf[IDX(j)]) == WEOF) {
        fprintf(stderr, "putwchar error");
        exit(1);
      }
    }
  }
}

int
main(int argc, char **argv) {
  wchar_t ch;
  wchar_t buf[BUFSIZE];
  size_t i = 0;
  size_t write_i = 0;
  bool escape_field = false;
  bool open_field = true;

  setlocale(LC_ALL, "");

  while ((ch = getwchar()) != WEOF) {
    switch(ch) {
    case L'\t':
      write_wchars(buf, write_i, i - 1, escape_field, open_field, true);
      putwchar(L',');
      write_i = i;
      open_field = true;
      escape_field = false;
      break;
    case L'\n':
      write_wchars(buf, write_i, i - 1, escape_field, open_field, true);
      putwchar(L'\r');
      putwchar(L'\n');
      write_i = i;
      open_field = true;
      escape_field = false;
      break;
    case L'"':
    case L',':
    case L'\r':
      escape_field = true;
    default:
      buf[IDX(i)] = ch;
      ++i;
      if (i - write_i >= BUFSIZE) {
        escape_field = true;
        write_wchars(buf, write_i, i - 1, escape_field, open_field, false);
        open_field = false;
        write_i = i;
      }
    }
  }

  if (ferror(stdin)) {
    perror("getwchar error: ");
    return 1;
  }
  return 0;
}
