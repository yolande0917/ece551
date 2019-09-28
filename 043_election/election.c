#include "election.h"
//include any other headers you need here...
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/***********
Takes a string parameter as the error message,
print out the message to stderr and exit.
*/
void exitError(const char * str) {
  fprintf(stderr, "%s\n", str);
  exit(EXIT_FAILURE);
}

/***********
Takes in a string and fill in a state_t
with the information inside the string.
 */
state_t parseLine(const char * line) {
  //STEP 1: write me
  // check if is a valid string
  if (line == NULL) {
    exitError("Invalid string.");
  }

  // check if the string has no content
  if (*line == '\0') {
    exitError("Empty string.");
  }

  // Initialize a state_t
  state_t state;

  size_t count = 0;
  // buffers for population and electoralVotes
  char population_char[8 * sizeof(uint64_t) + 1];
  char votes_char[8 * sizeof(unsigned int) + 1];

  // read char until reaches the first ':'
  while (*line != ':') {
    // check if the char is an alphabet or space
    if (!isalpha(*line) && (*line != ' ')) {
      exitError("Invalid state name.");
    }
    // check if the state name is too long
    if (count >= MAX_STATE_NAME_LENGTH - 2) {
      exitError("The state name is too long.");
    }
    // parse in the char to state.name
    state.name[count] = *line;
    count++;
    line++;
  }
  // check is the state name is empty
  if (count == 0) {
    exitError("No chars for state name.");
  }
  // check if the state name starts or ends with space
  if (state.name[0] == ' ' || state.name[count - 1] == ' ') {
    exitError("The state name start or ends with space.");
  }
  // null terminated the string
  state.name[count] = '\0';

  count = 0;
  line++;
  // read char until reaches the second ':'
  while (*line != ':') {
    // check if the char is a digit
    if (!isdigit(*line)) {
      exitError("Invalid population.");
    }
    // check if the number is too long
    if (count >= 8 * sizeof(uint64_t) - 1) {
      exitError("Population number is too long");
    }
    population_char[count] = *line;
    count++;
    line++;
  }
  // check if population is empty
  if (count == 0) {
    exitError("No chars for population.");
  }
  // null terminated the string
  population_char[count] = '\0';

  count = 0;
  line++;
  // read char until reaches '\0'
  while (*line != '\0') {
    // check if the char is a digit
    if (!isdigit(*line)) {
      exitError("Invalid electoral votes.");
    }
    // check if the number is too long
    if (count >= 8 * sizeof(unsigned int) - 1) {
      exitError("Electoral votes number is too long.");
    }
    votes_char[count] = *line;
    count++;
    line++;
  }
  // check if electoralVotes is empty
  if (count == 0) {
    exitError("No chars for electoral votes.");
  }

  // null terminated the string
  votes_char[count] = '\0';

  // convert population and electoralVotes to number
  state.population = (uint64_t)atol(population_char);
  state.electoralVotes = (unsigned int)atoi(votes_char);

  return state;
}

unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  //STEP 2: write me
  return 0;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
}
