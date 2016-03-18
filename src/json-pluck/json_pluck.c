#include <locale.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>

void
fatal(char *msg, size_t lineno, size_t offsetno) {
  fprintf(stderr, "ERROR: line: %lu: offset: %lu: %s\n",
          lineno, offsetno, msg);
  exit(1);
}

typedef bool json_type;

json_type JSON_TYPE_ARRAY = false;
json_type JSON_TYPE_OBJECT = true;

typedef struct {
  size_t size;
  size_t capacity;
  json_type *data;
} json_type_stack;

void
init_stack(json_type_stack *stack) {
  stack->size = 0;
  stack->capacity = 0;
  stack->data = NULL;
}

void
push_stack(json_type_stack *stack, json_type val) {
  // fprintf(stderr, "DEBUG: pushing %d\n", val);
  stack->size += 1;
  if (stack->size > stack->capacity) {
    stack->capacity = 2 * (stack->capacity) + 1;
    stack->data = (json_type *)realloc(stack->data, stack->capacity);
  }
  stack->data[stack->size - 1] = val;
}

json_type
peek_stack(json_type_stack *stack) {
  if (stack->size == 0) {
    fprintf(stderr, "ERROR: stack underflow");
    exit(1);
  }
  return stack->data[stack->size - 1];
}

json_type
pop_stack(json_type_stack *stack) {
  json_type retval = peek_stack(stack);
  // fprintf(stderr, "DEBUG: popping %d\n", retval);
  stack->size -= 1;
  return retval;
}

int
json_pluck() {
  wint_t ch;
  size_t lineno = 1, offsetno = 0;

  int array_depth = 0;
  bool inside_string = false;
  bool after_backslash = false;
  json_type_stack stack;
  init_stack(&stack);

  while ((ch = getwchar()) != WEOF) {
    offsetno += 1;

    switch (ch) {
    case L'[':
      if (inside_string) {
        putwchar(ch);
      }
      else {
        push_stack(&stack, JSON_TYPE_ARRAY);
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
        pop_stack(&stack);
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
    case L'{':
      if (!inside_string) {
        push_stack(&stack, JSON_TYPE_OBJECT);
      }
      putwchar(ch);
      after_backslash = false;
      break;
    case L'}':
      if (!inside_string) {
        pop_stack(&stack);
      }
      putwchar(ch);
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
          if (peek_stack(&stack) == JSON_TYPE_ARRAY) {
            putwchar(L'\n');
          }
          else {
            putwchar(ch);
          }
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
    fatal("more left brackets than right brackets", lineno - 1, offsetno);
  }

  putwchar(L'\n');

  return 0;
}

int
main(int argc, char **argv) {
  setlocale(LC_ALL, "");

  return json_pluck();
}
