#include <stdio.h>
#include <stdlib.h>
#define CELLS_LENGTH 5000
#define TRUE 1
#define FALSE 0

signed char array[CELLS_LENGTH] = {0}, *ptr = array;

void run_code(char *symbols, unsigned int *position);
void loop(char *symbols, unsigned int *position);
void *allocate(int len);
void *reallocate(void *v, int len);

int main(int argc, char const *argv[]) {
  int len = 1;
  char *symbols = NULL, *result;

  symbols = allocate(len);

  if (!symbols) {
    printf("Error: Cannot allocate memory");
    free(symbols);
    return 1;
  }

  if (argc == 1) {
    printf("Error: no file was passed as argument\n");
    free(symbols);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  unsigned int i = len - 1;
  while (!feof(file)) {
    if (i == len) {
      result = reallocate(symbols, len);

      if (!result) {
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
    loop(symbols, position);
  }
}

void loop(char *symbols, unsigned int *position) {
  unsigned int initial_position = *position, end_position, loops_count = 0, i;

  while (TRUE) {
    ++*position;

    if (symbols[*position] == '[') {
      loops_count++;
    } else if (symbols[*position] == ']') {
      if (loops_count > 0) {
        loops_count--;
      } else {
        break;
      }
    }
  }

  end_position = *position;

  if (!*ptr) {
    *position = end_position;
    return;
  }

  i = initial_position + 1;

  while (i != end_position || *ptr) {
    if (i == end_position) {
      i = initial_position + 1;
    } else {
      run_code(symbols, &i);
      i++;
    }
  }

  *position = i;
}

void *allocate(int len) {
  char *v = malloc(len);
  return v;
}

void *reallocate(void *v, int len) {
  void *result = realloc(v, len + 1);

  if (!result) {
    printf("Error: Cannot reallocate memory");
    free(result);
    return NULL;
  }

  return result;
}
