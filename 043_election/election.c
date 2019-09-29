#include "election.h"
//include any other headers you need here...
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/*************
Takes in the votes of the candidate and the population of the state
and calculate the percentage of votes he gets from the state
 */
double calculatePercentage(uint64_t votes, uint64_t population) {
  return (double)votes / population * 100;
}

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
    // check if the string ends before the first ':'
    if (*line == '\0') {
      exitError("String lacks information.");
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

/****************
Takes in an array of state_t and votecounts of the candidate 
of each state and the size, calculate the total electoral votes
 */
unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  //STEP 2: write me
  // check if any of the input pointers is NULL
  if (stateData == NULL || voteCounts == NULL) {
    exitError("Invalid input pointers.");
  }
  unsigned int totalElectoralVotes = 0;
  double percentage;
  // iterate through every elements in arrays
  for (size_t i = 0; i < nStates; i++) {
    // calculate the votes/population of each state
    percentage = calculatePercentage(voteCounts[i], stateData[i].population);
    if (percentage > 50) {
      // add the electoralVotes to total counts if the votes percentage exceeds 50%
      totalElectoralVotes += stateData[i].electoralVotes;
    }
  }
  return totalElectoralVotes;
}

/********
Takes in an array of state_t and votecounts of the candidate 
of each state and the size, print out if needs to recount for each state
 */
void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  // check if any of the input pointers is NULL
  if (stateData == NULL || voteCounts == NULL) {
    exitError("Invalid input pointers.");
  }
  double percentage;
  // iterate through every elements in arrays
  for (size_t i = 0; i < nStates; i++) {
    // calculate the votes/population of each state
    percentage = calculatePercentage(voteCounts[i], stateData[i].population);
    // if the vote percentage is within +/-0.5% away from 50%, print out
    if (percentage >= 49.5 && percentage <= 50.5) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             percentage);
    }
  }
}

/**********
Takes in an array of state_t and votecounts of the candidate 
of each state and the size, prints out in which state candidate A won
the largest percentage of vote.
 */
void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  // check if any of the input pointers is NULL
  if (stateData == NULL || voteCounts == NULL) {
    exitError("Invalid input pointers.");
  }
  double percentage;
  double max = 0;
  size_t ind = 0;
  // iterate through every elements in arrays
  for (size_t i = 0; i < nStates; i++) {
    // calculate the votes/population of each state
    percentage = calculatePercentage(voteCounts[i], stateData[i].population);
    // find the max percentage of votes
    if (percentage > max) {
      max = percentage;
      ind = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[ind].name, max);
}
