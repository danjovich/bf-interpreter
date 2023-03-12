#include <stdio.h>
#include <stdlib.h>
#define CELLS_LENGTH 5000
#define TRUE 1
#define FALSE 0

signed char array[CELLS_LENGTH] = {0}, *ptr = array;

void run_code(char *symbols, unsigned int *position);

int main(int argc, char const *argv[]) {
  int len = 1;
  char *symbols = NULL, *result;

  symbols = malloc(len);

  if (!symbols) {
    printf("Error: Cannot allocate memory");
    free(symbols);
    return 1;
  }

  if (argc == 1) {
    printf("Error: No file was passed as argument\n");
    free(symbols);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  unsigned int i = len - 1;
  while (!feof(file)) {
    if (i == len) {
      result = realloc(symbols, len + 1);

      if (!result) {
        printf("Error: Cannot reallocate memory");
        free(symbols);
        return 1;
      }

      symbols = result;
      len++;
    }
    fscanf(file, "%c", &symbols[i]);
    i++;
  }

  for (unsigned int j = 0; j < i; j++) {
    run_code(symbols, &j);
  }

  free(symbols);
  fclose(file);

  return 0;
}

void run_code(char *symbols, unsigned int *position) {
  char symbol = symbols[*position];

  if (symbol == '>') {
    ptr++;
  } else if (symbol == '<') {
    ptr--;
  } else if (symbol == '+') {
    ++*ptr;
  } else if (symbol == '-') {
    --*ptr;
  } else if (symbol == '.') {
    putchar(*ptr);
  } else if (symbol == ',') {
    *ptr = getchar();
  } else if (symbol == '[') {
    unsigned int i, goto_end = !*ptr, loops = 0;

    do {
      for (i = *position + 1; symbols[i] != ']' || loops != 0; i++) {
        if (!goto_end) {
          run_code(symbols, &i);
        } else if (symbols[i] == '[') {
          loops++;
        } else if (symbols[i] == ']') {
          loops--;
        }
      }
    } while (*ptr);

    *position = i;
  }
}
