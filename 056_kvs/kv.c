#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stripNewline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

char * findFirstEqual(char * str) {
  // find the location of first '='
  char * eqPtr = strchr(str, '=');
  if (eqPtr == NULL) {
    fprintf(stderr, "No equal sign in the line.\n");
    exit(EXIT_FAILURE);
  }
  return eqPtr;
}

void readKey(char * str, kvpair_t * kv) {
  // find the location of first '='
  char * eqPtr = findFirstEqual(str);

  size_t keySize = eqPtr - str + 1;  // 1 more space for '\0'
  kv->key = malloc(keySize * sizeof(*kv->key));

  // assign value to key
  for (size_t i = 0; i < keySize - 1; i++) {
    kv->key[i] = str[i];
  }
  kv->key[keySize - 1] = '\0';
}

void readValue(char * str, kvpair_t * kv) {
  // find the location of first '='
  char * eqPtr = findFirstEqual(str);
  // find the location of the end of str
  char * endPtr = strchr(str, '\0');

  size_t valueSize = endPtr - eqPtr;
  kv->value = malloc(valueSize * sizeof(*kv->value));
  // assign value to value
  for (size_t i = 0; i < valueSize; i++) {
    kv->value[i] = eqPtr[i + 1];
  }
}

kvpair_t * readFromLine(char * str) {
  if (*str == '\0' || *str == '=') {
    fprintf(stderr, "Invalid string format.\n");
    exit(EXIT_FAILURE);
  }

  kvpair_t * kv = malloc(sizeof(*kv));
  readKey(str, kv);
  readValue(str, kv);

  return kv;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME

  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Invalid file name.\n");
    exit(EXIT_FAILURE);
  }

  kvarray_t * kvarray = malloc(sizeof(*kvarray));

  kvarray->array = malloc(sizeof(*kvarray->array));

  char * buffer = NULL;
  size_t sz = 0;
  size_t count = 0;
  while (getline(&buffer, &sz, f) >= 0) {
    kvarray->array = realloc(kvarray->array, (count + 1) * sizeof(*kvarray->array));
    stripNewline(buffer);
    kvarray->array[count] = readFromLine(buffer);
    count++;
  }
  kvarray->length = count;
  free(buffer);

  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the file.\n");
    exit(EXIT_FAILURE);
  }
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  kvpair_t ** array = pairs->array;
  size_t length = pairs->length;
  kvpair_t * kv;
  for (size_t i = 0; i < length; i++) {
    kv = array[i];
    free(kv->key);
    free(kv->value);
    free(kv);
  }
  free(array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  kvpair_t ** array = pairs->array;
  size_t length = pairs->length;
  kvpair_t * kv;
  for (size_t i = 0; i < length; i++) {
    kv = array[i];
    printf("key = '%s' value = '%s'\n", kv->key, kv->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  kvpair_t ** array = pairs->array;
  size_t length = pairs->length;
  kvpair_t * kv;
  for (size_t i = 0; i < length; i++) {
    kv = array[i];
    if (strcmp(kv->key, key) == 0) {
      return kv->value;
    }
  }
  return NULL;
}
