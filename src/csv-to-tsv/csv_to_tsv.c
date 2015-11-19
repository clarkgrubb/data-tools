#include <getopt.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

enum parse_state {
  outside_field,
  quoted_field,
  quoted_field_after_dquote,
  unquoted_field,
  before_newline
};

enum invalid_char {
  invalid_char_fail,
  invalid_char_escape,
  invalid_char_replace,
  invalid_char_strip
};

void
fatal(char *msg, size_t lineno, size_t offsetno) {
  fprintf(stderr, "ERROR: line: %lu: offset: %lu: %s\n",
          lineno, offsetno, msg);
  exit(1);
}

int
csv_to_tsv(enum invalid_char invalid_char_treatment, long pad, char *header) {
  wint_t ch;
  enum parse_state state = outside_field;
  size_t lineno = 1, offsetno = 0, fieldno = 0;

  while ((ch = getwchar()) != WEOF) {
    offsetno += 1;

    switch (ch) {
    case L'\t':
      switch (state) {
      case outside_field:
        state = unquoted_field;
      case quoted_field:
      case unquoted_field:
        if (invalid_char_treatment == invalid_char_fail)
          fatal("tab in data", lineno, offsetno);
        else if (invalid_char_treatment == invalid_char_escape) {
          putwchar(L'\\');
          putwchar(L't');
        }
        else if (invalid_char_treatment == invalid_char_replace)
          putwchar(L' ');
        else if (invalid_char_treatment == invalid_char_strip)
          break;
        else
          fatal("unexpected invalid character treatment", lineno, offsetno);
        break;
      case quoted_field_after_dquote:
      case before_newline:
        fatal("unexpected tab", lineno, offsetno);
        break;
      default:
        fatal("unexpected state", lineno, offsetno);
      }
      break;

    case L'\\':
      switch (state) {
      case outside_field:
        state = unquoted_field;
      case quoted_field:
      case unquoted_field:
        if (invalid_char_treatment == invalid_char_escape)
          putwchar(L'\\');
        putwchar(L'\\');
      case quoted_field_after_dquote:
      case before_newline:
        fatal("unexpected backslash", lineno, offsetno);
        break;
      default:
        fatal("unexpected state", lineno, offsetno);
      }
      break;

    case L'"':
      switch (state) {
      case outside_field:
        state = quoted_field;
        break;
      case quoted_field:
        state = quoted_field_after_dquote;
        break;
      case quoted_field_after_dquote:
        putwchar(L'"');
        state = quoted_field;
        break;
      case unquoted_field:
      case before_newline:
        fatal("unexpected double quote", lineno, offsetno);
        break;
      default:
        fatal("unexpected state", lineno, offsetno);
      }
      break;

    case L',':
      switch (state) {
      case outside_field:
        putwchar(L'\t');
        fieldno += 1;
        break;
      case quoted_field:
        putwchar(ch);
        break;
      case quoted_field_after_dquote:
        putwchar(L'\t');
        state = outside_field;
        fieldno += 1;
        break;
      case unquoted_field:
        putwchar(L'\t');
        fieldno += 1;
        state = outside_field;
        break;
      case before_newline:
        fatal("unexpected comma", lineno, offsetno);
      default:
        fatal("unexpected state", lineno, offsetno);
      }
      break;

    case L'\n':
      switch (state) {
      case quoted_field:
        /* TODO: flag for escaping or replacing */
        break;
      case outside_field:
      case quoted_field_after_dquote:
      case unquoted_field:
      case before_newline:
        putwchar(L'\n');
        lineno += 1;
        offsetno = 0;
        fieldno = 0;
        state = outside_field;
        break;
      default:
        fatal("unexpected state", lineno, offsetno);
      }
      break;

    case L'\r':
      switch (state) {
      case quoted_field_after_dquote:
      case unquoted_field:
      case outside_field:
        state = before_newline;
        break;
      default:
        fatal("unexpected carriage return", lineno, offsetno);
      }
      break;

    default:
      switch (state) {
      case outside_field:
        putwchar(ch);
        state = unquoted_field;
        break;
      case quoted_field:
        putwchar(ch);
        break;
      case quoted_field_after_dquote:
        fatal("unescaped double quote", lineno, offsetno);
        break;
      case unquoted_field:
        putwchar(ch);
        break;
      case before_newline:
      default:
        fatal("unexpected state", lineno, offsetno);
      }
    }
  }

  if (state == quoted_field)
    fatal("unterminated double quote", lineno, offsetno);

  if (ferror(stdin)) {
    perror("error reading input stream");
    exit(1);
  }

  return 0;
}

int
main(int argc, char **argv) {
  static struct option long_opts[] = {
    {"escape", no_argument, NULL, 'e'},
    {"header", required_argument, NULL, 'h'},
    {"pad", required_argument, NULL, 'p'},
    {"replace", no_argument, NULL, 'r'},
    {"strip", no_argument, NULL, 'x'},
    {0, 0, 0, 0}
  };

  int ch;
  int opti;
  char *endptr;
  enum invalid_char invalid_char_treatment = invalid_char_fail;
  long pad = 0;
  char *header = NULL;

  setlocale(LC_ALL, "");

  while (1) {
    ch = getopt_long(argc, argv, "dert:x", long_opts, &opti);
    if (-1 == ch) {
      break;
    }

    switch (ch) {
    case 'e':
      invalid_char_treatment = invalid_char_escape;
      break;
    case 'x':
      invalid_char_treatment = invalid_char_strip;
      break;
    case 'r':
      invalid_char_treatment = invalid_char_replace;
      break;
    case 'h':
      header = strdup(optarg);
      break;
    case 'p':
      pad = strtol(optarg, &endptr, 10);
      if (*endptr != 0) {
        fprintf(stderr, "expected integer: %s\n", optarg);
        exit(1);
      }
      break;
    default:
      fprintf(stderr, "unexpected arg: %d\n", ch);
      exit(1);
    }
  }

  return csv_to_tsv(invalid_char_treatment, pad, header);
}
