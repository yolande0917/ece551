#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

class StringVec : public std::vector<char *> {
  virtual ~StringVec() {
    StringVec::iterator it = begin();
    while (it != end()) {
      delete[] * it;
    }
  }
};

// TODO: comments
void splitPath(std::vector<char *> & vect, char * pPath) {
  char * startptr = pPath;
  char * endptr;
  size_t len;
  while ((endptr = strchr(startptr, ':')) != NULL) {
    len = endptr - startptr;
    char * dest = new char[len + 1];  // plus 1 for null terminator
    strncpy(dest, startptr, len);
    dest[len] = '\0';
    vect.push_back(dest);
    // debug
    std::cout << dest << std::endl;
    // delete[] dest;
    // update startptr
    startptr = endptr + 1;
  }
  len = strlen(startptr);
  char * dest = new char[len + 1];
  strcpy(dest, startptr);
  dest[len] = '\0';
  vect.push_back(dest);
  // debug
  std::cout << dest << std::endl;
}

// TODO: comments
bool containPath(const char * str) {
  while (*str != '\0') {
    if (*str == '/') {
      return true;
    }
    str++;
  }
  return false;
}

// TODO: comments
void executeProgram(char ** childargv, char ** childenviron, char * pPath) {
  if (containPath(childargv[0])) {
    // execute when the first argument contains path
    // if command not found, print message and exit progress
    if (execve(childargv[0], childargv, childenviron) == -1) {
      std::cout << childargv[0] << ": command not found" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  else {
    // if argument doesn't contain path, check through ECE551PATH
    std::vector<char *> paths;
    splitPath(paths, pPath);
    std::vector<char *>::iterator it = paths.begin();
    while (it != paths.end()) {
      // concatenate path and program
      size_t pathlen = strlen(*it);
      // debug
      std::cout << pathlen << std::endl;
      size_t comlen = strlen(childargv[0]);
      // keep a copy of old childargv[0]
      char * oldargv = new char[comlen + 1];
      strcpy(oldargv, childargv[0]);
      char * dest = new char[pathlen + comlen + 2];
      strcpy(dest, *it);
      strcat(dest, "/");
      strcat(dest, childargv[0]);
      strcpy(childargv[0], dest);
      // debug
      std::cout << childargv[0] << std::endl;
      delete[] dest;
      // execute
      if (execve(childargv[0], childargv, childenviron) == -1) {
        // if command not found
        // if still has other path, check the next one
        if (it != (paths.end() - 1)) {
          std::cout << childargv[0] << ": command not found" << std::endl;
          delete[] * it;
          ++it;
          strcpy(childargv[0], oldargv);
          delete[] oldargv;
        }
        // if is the last path, print message and exit
        else {
          delete[] oldargv;
          delete[] * it;
          ++it;
          delete[] * it;
          std::cout << childargv[0] << ": command not found" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      else {
        return;
      }
    }
  }
}

// TODO: use reference
std::vector<std::string> * splitArguments(std::string str) {
  return new std::vector<std::string>;
}

/*****
This function takes the child process's exit status as parameter,
and prints out appropriate message showing whether it exits on success,
on failure, or send a signal.
 ****/
void handleStatus(int status) {
  if (WIFEXITED(status)) {
    if (WEXITSTATUS(status) == 0) {
      std::cout << "Program was successful" << std::endl;
    }
    else {
      std::cout << "Program failed with code " << WEXITSTATUS(status) << std::endl;
    }
  }
  if (WIFSIGNALED(status)) {
    std::cout << "Terminated by signal " << WTERMSIG(status) << std::endl;
  }
}

int main(int argc, char * argv[]) {
  char * pPath;
  pPath = getenv("PATH");
  if (pPath != NULL) {
    std::cout << "ECE551PATH is: " << pPath << std::endl;
  }
  while (1) {
    // repeat displaying the prompt and reading user input
    std::string prompt = "ffosh$ ";
    std::string userinput;
    std::cout << prompt;
    std::getline(std::cin, userinput);
    // exit program if user enter exit or EOF
    if (std::cin.eof() || userinput.compare("exit") == 0) {
      exit(EXIT_SUCCESS);
    }

    // TODO split the input string
    // std::vector<std::string> progargv;
    // progargv = splitArguments(userinput);
    // for part 1
    char * childenviron[] = {NULL};
    char * childargv[2];  // for part 1
    childargv[0] = &userinput[0];
    childargv[1] = NULL;

    // fork a child process
    pid_t childpid, waitpid;
    int childstatus;
    childpid = fork();
    if (childpid < 0) {
      // fork error
      perror("fork");
      exit(EXIT_FAILURE);
    }
    else if (childpid == 0) {
      // child: execute the specified program
      executeProgram(childargv, childenviron, pPath);
    }
    else {
      // parent: wait for the child
      waitpid = wait(&childstatus);
      if (waitpid == -1) {
        perror("wait");
        exit(EXIT_FAILURE);
      }
      // print message based on child process status
      handleStatus(childstatus);
    }
  }

  return EXIT_SUCCESS;
}
