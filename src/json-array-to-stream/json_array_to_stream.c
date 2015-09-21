#include <getopt.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

void
fatal(char *msg, size_t lineno, size_t offsetno) {
  fprintf(stderr, "ERROR: line: %lu: offset: %lu: %s\n",
          lineno, offsetno, msg);
  exit(1);
}

int
json_array_to_stream() {
  wint_t ch;
  size_t lineno = 1, offsetno = 0;

  int array_depth = 0;
  bool inside_string = false;
  bool after_backslash = false;

  while ((ch = getwchar()) != WEOF) {
    offsetno += 1;

    switch (ch) {
    case L'[':
      if (inside_string) {
        putwchar(ch);
      }
      else {
        if (array_depth > 0) {
          putwchar(ch);
        }
        array_depth += 1;
      }
      after_backslash = false;
      break;
    case L']':
      if (inside_string) {
        putwchar(ch);
      }
      else {
        array_depth -= 1;
        if (array_depth > 0) {
          putwchar(ch);
        }
        if (array_depth < 0) {
          fatal("unmatched right square bracket", lineno, offsetno);
        }
      }
      after_backslash = false;
      break;
    case ',':
      if (inside_string) {
        putwchar(ch);
      }
      else {
        if (array_depth == 0) {
          fatal("unexpected comma", lineno, offsetno);
        }
        else if (array_depth == 1) {
          putwchar(L'\n');
        }
        else {
          putwchar(ch);
        }
      }
      after_backslash = false;
      break;
    case L'"':
      if (inside_string) {
        if (after_backslash) {
          inside_string = true;
          after_backslash = false;
        }
        else {
          inside_string = false;
        }
      }
      else {
        inside_string = true;
      }
      putwchar(ch);
      after_backslash = false;
      break;
    case L'\\':
      if (inside_string) {
        after_backslash = !after_backslash;
      }
      else {
        fatal("backslash outside of string", lineno, offsetno);
      }
      putwchar(ch);
      break;
    case L' ':
      if (inside_string) {
        putwchar(ch);
      }
      after_backslash = false;
      break;
    case L'\t':
      if (inside_string) {
        fatal("tab in string", lineno, offsetno);
      }
      after_backslash = false;
      break;
    case L'\n':;
      if (inside_string) {
        fatal("newline in string", lineno, offsetno);
      }
      lineno += 1;
      offsetno = 0;
      after_backslash = false;
      break;
    default:
      putwchar(ch);
      after_backslash = false;
      break;
    }
  }

  if (array_depth != 0) {
    fatal("more left bracket than right brackets", lineno - 1, offsetno);
  }

  putwchar(L'\n');

  return 0;
}

int
main(int argc, char **argv) {
  setlocale(LC_ALL, "");

  return json_array_to_stream();
}
