#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

enum parse_state {
  outside_of_field,
  quoted_field,
  quoted_field_after_dquote,
  unquoted_field
};

void
fatal(char *msg, size_t lineno, size_t offsetno) {
  fprintf(stderr, "ERROR: line: %lu: offset: %lu: %s\n",
          lineno, offsetno, msg);
  exit(1);
}

int
main(int argc, char **argv) {
  wint_t ch;
  enum parse_state state = outside_of_field;
  size_t lineno = 1, offsetno = 0, fieldno = 0;

  while ((ch = getwchar()) != WEOF) {
    offsetno += 1;
    switch (ch) {
    case L'\t':
      /* TODO: flag for replacing with space or escaping */
      break;
    case L'"':
      switch (state) {
      case outside_of_field:
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
        fatal("unexpected double quote", lineno, offsetno);
        break;
      default:
        fatal("unexpected state", lineno, offsetno);
      }
      break;
    case L',':
      switch (state) {
      case outside_of_field:
        putwchar(L'\t');
        fieldno += 1;
        break;
      case quoted_field:
        putwchar(ch);
        break;
      case quoted_field_after_dquote:
        putwchar(L'\t');
        state = outside_of_field;
        fieldno += 1;
        break;
      case unquoted_field:
        putwchar(L'\t');
        fieldno += 1;
        state = outside_of_field;
        break;
      default:
        fatal("unexpected state", lineno, offsetno);
      }
      break;
    case L'\n':
      switch (state) {
      case quoted_field:
        /* TODO: flag for escaping or replacing */
        break;
      case outside_of_field:
      case quoted_field_after_dquote:
      case unquoted_field:
        putwchar(L'\n');
        lineno += 1;
        offsetno = 0;
        fieldno = 0;
        state = outside_of_field;
        break;
      default:
        fatal("unexpected state", lineno, offsetno);
      }
      break;
    default:
      switch (state) {
      case outside_of_field:
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
