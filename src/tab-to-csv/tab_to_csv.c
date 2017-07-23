#include <errno.h>
#include <getopt.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int tab_to_csv(FILE *input_stream, bool unescape_char) {
  wchar_t ch;
  wchar_t buf[BUFSIZE];
  size_t i = 0;
  size_t write_i = 0;
  bool escape_field = false;
  bool open_field = true;
  bool last_char_backslash = false;

 while ((ch = fgetwc(input_stream)) != WEOF) {
    switch(ch) {

    case L'\\':
      if (last_char_backslash) {
        if (!unescape_char) {
          buf[IDX(i)] = L'\\';
          ++i;
          if (i - write_i >= BUFSIZE) {
            escape_field = true;
            write_wchars(buf, write_i, i - 1, escape_field, open_field, false);
            open_field = false;
            write_i = i;
          }
        }
        buf[IDX(i)] = L'\\';
        ++i;
        if (i - write_i >= BUFSIZE) {
          escape_field = true;
          write_wchars(buf, write_i, i - 1, escape_field, open_field, false);
          open_field = false;
          write_i = i;
        }
      }
      last_char_backslash = !last_char_backslash;
      break;

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

    case L't':
      if (unescape_char && last_char_backslash)
        buf[IDX(i)] = L'\t';
      else if (last_char_backslash) {
        buf[IDX(i)] = L'\\';
        ++i;
        if (i - write_i >= BUFSIZE) {
          escape_field = true;
          write_wchars(buf, write_i, i - 1, escape_field, open_field, false);
          open_field = false;
          write_i = i;
        }
        buf[IDX(i)] = L't';
      }
      else {
        buf[IDX(i)] = L't';
      }
      last_char_backslash = false;
      ++i;
      if (i - write_i >= BUFSIZE) {
        escape_field = true;
        write_wchars(buf, write_i, i - 1, escape_field, open_field, false);
        open_field = false;
        write_i = i;
      }
      break;

    case L'n':
      if (unescape_char && last_char_backslash) {
        buf[IDX(i)] = L'\n';
        escape_field = true;
      }
      else if (last_char_backslash) {
        buf[IDX(i)] = L'\\';
        ++i;
        if (i - write_i >= BUFSIZE) {
          escape_field = true;
          write_wchars(buf, write_i, i - 1, escape_field, open_field, false);
          open_field = false;
          write_i = i;
        }
        buf[IDX(i)] = L'n';
      }
      else {
        buf[IDX(i)] = L'n';
      }
      last_char_backslash = false;
      ++i;
      if (i - write_i >= BUFSIZE) {
        escape_field = true;
        write_wchars(buf, write_i, i - 1, escape_field, open_field, false);
        open_field = false;
        write_i = i;
      }
      break;

    case L'r':
      if (unescape_char && last_char_backslash) {
        buf[IDX(i)] = L'\r';
        escape_field = true;
      }
      else if (last_char_backslash) {
        buf[IDX(i)] = L'\\';
        ++i;
        if (i - write_i >= BUFSIZE) {
          escape_field = true;
          write_wchars(buf, write_i, i - 1, escape_field, open_field, false);
          open_field = false;
          write_i = i;
        }
        buf[IDX(i)] = L'r';
      }
      else {
        buf[IDX(i)] = L'r';
      }
      last_char_backslash = false;
      ++i;
      if (i - write_i >= BUFSIZE) {
        escape_field = true;
        write_wchars(buf, write_i, i - 1, escape_field, open_field, false);
        open_field = false;
        write_i = i;
      }
      break;

    case L'"':
    case L',':
    case L'\r':
      escape_field = true;
    default:
      if (last_char_backslash) {
        if (unescape_char) {
          fprintf(stderr, "unexpected backslash");
          exit(1);
        }
        else {
          buf[IDX(i)] = L'\\';
          ++i;
          if (i - write_i >= BUFSIZE) {
            escape_field = true;
            write_wchars(buf, write_i, i - 1, escape_field, open_field, false);
            open_field = false;
            write_i = i;
          }
        }
      }
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

int
main(int argc, char **argv) {
  static struct option long_opts[] = {
    {"unescape", no_argument, NULL, 'u'},
    {0, 0, 0, 0}
  };

  int opti;
  bool unescape_char = false;

  setlocale(LC_ALL, "");

  while (1) {
    int ch = getopt_long(argc, argv, "u", long_opts, &opti);
    if (-1 == ch) {
      break;
    }

    switch (ch) {
    case 'u':
      unescape_char = true;
      break;
    default:
      fprintf(stderr, "unexpected arg: %d\n", ch);
      exit(1);
    }
  }

  FILE *f;
  if (optind == argc)
    f = stdin;
  else if (optind == argc - 1) {
    f = fopen(argv[optind], "r");
    if (!f) {
      fprintf(stderr, "error opening %s: %s\n", argv[optind], strerror(errno));
      exit(1);
    }
  }
  else {
    fprintf(stderr, "USAGE: tab-to-csv [--unescape] [PATH]\n");
    exit(1);
  }

  return tab_to_csv(f, unescape_char);
}
