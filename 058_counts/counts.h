#include <stdio.h>
#include <stdlib.h>

#ifndef __COUNTS_H__
#define __COUNTS_H__
struct _one_count_t {
  //DEFINE ME
  char * value;
  size_t count;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  //DEFINE ME
  one_count_t ** items;
  size_t length;
  size_t unknownCount;
};
typedef struct _counts_t counts_t;

int checkNameInd(counts_t * c, const char * name);
counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
