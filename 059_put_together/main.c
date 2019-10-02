#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  // open file
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Failed to open file.\n");
    exit(EXIT_FAILURE);
  }
  // read from file
  char * line = NULL;
  size_t sz = 0;
  char * key;
  char * value;
  // initialize counts_t *
  counts_t * counts = createCounts();
  while (getline(&line, &sz, f) >= 0) {
    key = line;
    stripNewline(key);
    value = lookupValue(kvPairs, key);
    addCount(counts, value);
  }
  free(line);

  // close file
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close file.\n");
    exit(EXIT_FAILURE);
  }

  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 3) {
    fprintf(stderr, "Need at least two file names as args.\n");
    exit(EXIT_FAILURE);
  }

  kvarray_t * kv = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 0; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "Failed to open a new file.\n");
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Failed to close the file.\n");
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}
