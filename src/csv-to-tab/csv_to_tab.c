#include <errno.h>
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
  unquoted_field_after_cr,
  before_newline
};

enum invalid_char {
  invalid_char_fail,
  invalid_char_escape,
  invalid_char_replace,
  invalid_char_strip
};

void
fatal(char *msg, size_t lineno, size_t offsetno, size_t src_lineno) {
  fprintf(stderr, "ERROR: line: %zu: offset: %zu: source: %zu: %s\n",
          lineno, offsetno, src_lineno, msg);
  exit(1);
}

void
handle_invalid_char(wint_t replacement,
                    char *msg,
                    enum invalid_char invalid_char_treatment,
                    size_t lineno,
                    size_t offsetno,
                    size_t src_lineno) {
  if (invalid_char_treatment == invalid_char_fail)
    fatal(msg, lineno, offsetno, src_lineno);
  else if (invalid_char_treatment == invalid_char_escape) {
    putwchar(L'\\');
    putwchar(replacement);
  }
  else if (invalid_char_treatment == invalid_char_replace)
    putwchar(L' ');
  else if (invalid_char_treatment == invalid_char_strip)
    return;
  else
    fatal("unexpected invalid character treatment", lineno, offsetno, src_lineno);
}

int
csv_to_tab(FILE *input_stream, enum invalid_char invalid_char_treatment) {
  wint_t ch;
  enum parse_state state = outside_field;
  size_t lineno = 1, offsetno = 0;

  while ((ch = fgetwc(input_stream)) != WEOF) {
    offsetno += 1;

    switch (ch) {
    case L'\t':
      switch (state) {
      case outside_field:
        state = unquoted_field;
        handle_invalid_char(L't', "tab in data", invalid_char_treatment, lineno, offsetno,
                            __LINE__);
        break;
      case quoted_field:
      case unquoted_field:
        handle_invalid_char(L't', "tab in data", invalid_char_treatment, lineno, offsetno,
                            __LINE__);
        break;
      case unquoted_field_after_cr:
        state = unquoted_field;
        handle_invalid_char(L'r', "carriage return in data", invalid_char_treatment, lineno,
                            offsetno, __LINE__);
        handle_invalid_char(L't', "tab in data", invalid_char_treatment, lineno, offsetno,
                            __LINE__);
        break;
      case quoted_field_after_dquote:
      case before_newline:
        fatal("unexpected tab", lineno, offsetno, __LINE__);
        break;
      default:
        fatal("unexpected state", lineno, offsetno, __LINE__);
      }
      break;

    case L'\\':
      switch (state) {
        case unquoted_field_after_cr:
          state = unquoted_field;
          handle_invalid_char(L'r', "carriage return in data", invalid_char_treatment, lineno,
                              offsetno, __LINE__);
          if (invalid_char_treatment == invalid_char_escape)
            putwchar(L'\\');
          putwchar(L'\\');
          break;
      case outside_field:
        state = unquoted_field;
        if (invalid_char_treatment == invalid_char_escape)
          putwchar(L'\\');
        putwchar(L'\\');
        break;
      case quoted_field:
      case unquoted_field:
        if (invalid_char_treatment == invalid_char_escape)
          putwchar(L'\\');
        putwchar(L'\\');
        break;
      case quoted_field_after_dquote:
      case before_newline:
        fatal("unexpected backslash", lineno, offsetno, __LINE__);
        break;
      default:
        fatal("unexpected state", lineno, offsetno, __LINE__);
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
      case unquoted_field_after_cr:
      case unquoted_field:
      case before_newline:
        fatal("unexpected double quote", lineno, offsetno, __LINE__);
        break;
      default:
        fatal("unexpected state", lineno, offsetno, __LINE__);
      }
      break;

    case L',':
      switch (state) {
      case outside_field:
        putwchar(L'\t');
        break;
      case quoted_field:
        putwchar(ch);
        break;
      case quoted_field_after_dquote:
        putwchar(L'\t');
        state = outside_field;
        break;
      case unquoted_field_after_cr:
        handle_invalid_char(L'r', "carriage return in data", invalid_char_treatment, lineno,
                            offsetno, __LINE__);
        putwchar(L'\t');
        state = outside_field;
        break;
      case unquoted_field:
        putwchar(L'\t');
        state = outside_field;
        break;
      case before_newline:
        fatal("unexpected comma", lineno, offsetno, __LINE__);
      default:
        fatal("unexpected state", lineno, offsetno, __LINE__);
      }
      break;

    case L'\n':
      lineno += 1;
      offsetno = 0;
      switch (state) {
      case quoted_field:
        handle_invalid_char(L'n', "newline in data", invalid_char_treatment, lineno, offsetno,
                            __LINE__);
        break;
      case outside_field:
      case quoted_field_after_dquote:
      case unquoted_field:
      case before_newline:
      case unquoted_field_after_cr:
        putwchar(L'\n');
        state = outside_field;
        break;
      default:
        fatal("unexpected state", lineno, offsetno, __LINE__);
      }
      break;

    case L'\r':
      switch (state) {
      case quoted_field:
        /* TODO: flag for escaping or replacing */
        break;
      case quoted_field_after_dquote:
      case outside_field:
        state = before_newline;
        break;
      case unquoted_field_after_cr:
        handle_invalid_char(L'r', "carriage return in data", invalid_char_treatment, lineno,
                            offsetno, __LINE__);
        state = unquoted_field_after_cr;
        break;
      case unquoted_field:
        state = unquoted_field_after_cr;
        break;
      default:
        fatal("unexpected carriage return", lineno, offsetno, __LINE__);
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
        fatal("unescaped double quote", lineno, offsetno, __LINE__);
        break;
      case unquoted_field_after_cr:
        state = unquoted_field;
        handle_invalid_char(L'r', "carriage return in data", invalid_char_treatment, lineno,
                            offsetno, __LINE__);
        putwchar(ch);
        break;
      case unquoted_field:
        putwchar(ch);
        break;
      case before_newline:
      default:
        fatal("unexpected state", lineno, offsetno, __LINE__);
      }
    }
  }

  if (state == quoted_field)
    fatal("unterminated double quote", lineno, offsetno, __LINE__);

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
    {"replace", no_argument, NULL, 'r'},
    {"strip", no_argument, NULL, 'x'},
    {0, 0, 0, 0}
  };

  int opti;
  enum invalid_char invalid_char_treatment = invalid_char_fail;

  setlocale(LC_ALL, "");

  while (1) {
    int ch = getopt_long(argc, argv, "dert:x", long_opts, &opti);
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
    fprintf(stderr, "USAGE: csv-to-tab [--escape|--strip|--replace] [PATH]\n");
    exit(1);
  }

  return csv_to_tab(f, invalid_char_treatment);
}
