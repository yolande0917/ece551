#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkNameInd(counts_t * c, const char * name) {
  // check if the name is NULL
  if (name == NULL) {
    c->unknownCount++;
    return -2;  // return -2 if name is NULL
  }
  size_t length = c->length;
  if (length == 0) {
    return -1;  // return -1 if c->items is empty
  }

  one_count_t ** array = c->items;
  one_count_t * one_count;
  for (size_t i = 0; i < length; i++) {
    one_count = array[i];
    if (strcmp(one_count->value, name) == 0) {  // return ind if find the name
      one_count->count++;
      return i;
    }
  }
  return -1;  // return -1 if doesn't find the name
}

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * myCount = malloc(sizeof(*myCount));
  myCount->unknownCount = 0;
  myCount->items = NULL;
  myCount->length = 0;

  return myCount;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  // call checkNameind
  int ind = checkNameInd(c, name);
  if (ind == -2 || ind >= 0) {  // unknown name or find the name in items
    return;
  }

  // name not found in items
  c->length++;  // increase length
  size_t length = c->length;
  c->items = realloc(c->items, length * sizeof(*c->items));
  one_count_t * one_count = malloc(sizeof(*one_count));
  size_t len = strlen(name) + 1;  // string length of name
  char * str = malloc(len * sizeof(*str));
  str = strcpy(str, name);  // copy name to str
  one_count->value = str;
  one_count->count = 1;
  c->items[length - 1] = one_count;

  return;
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (outFile == NULL) {
    fprintf(stderr, "Invalid file pointer.\n");
    exit(EXIT_FAILURE);
  }

  // print to file if length>0
  size_t length = c->length;
  if (length > 0) {
    one_count_t ** items = c->items;
    one_count_t * one_count;
    for (size_t i = 0; i < length; i++) {
      one_count = items[i];
      fprintf(outFile, "%s: %zu\n", one_count->value, one_count->count);
    }
  }
  // check unknown
  if (c->unknownCount > 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->unknownCount);
  }
  return;
}

void freeCounts(counts_t * c) {
  //WRITE ME
  one_count_t ** items = c->items;
  one_count_t * one_count;
  char * value;
  for (size_t i = 0; i < c->length; i++) {
    one_count = items[i];
    value = one_count->value;
    free(value);
    free(one_count);
  }
  free(items);
  free(c);
}
