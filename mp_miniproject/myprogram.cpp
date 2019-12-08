#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

/*****
A class that has a field of char ** to store arguments.
Another size_t field stores the number of char * 
Note that when the argv field is not NULL, the last element of it is NULL
 *****/
class ArgvContainer {
 public:
  char ** argv;
  size_t n;

  // constructor
  ArgvContainer() : argv(NULL), n(0) {}
  ArgvContainer(char **& argv_, size_t n_) : argv(argv_), n(n_) {}
  // destructor
  ~ArgvContainer() {
    if (n > 0) {
      for (size_t i = 0; i < n; i++) {
        delete[] argv[i];
      }
      delete[] argv;
    }
  }
  // attach
  void attach(char **& argv_, size_t n_) {
    if (n > 0) {
      for (size_t i = 0; i < n; i++) {
        delete[] argv[i];
      }
      delete[] argv;
    }
    n = n_;
    argv = argv_;
  }
  // get
  char **& get() { return argv; }
  // size
  size_t size() { return n; }
  // copy constructor
  ArgvContainer(ArgvContainer & rhs) : argv(NULL), n(rhs.size()) {
    char ** data = rhs.get();
    size_t num = rhs.size();
    argv = new char *[num];
    for (size_t i = 0; i < num; i++) {
      size_t len = strlen(data[i]);
      if (i == 0) {
        len = len + 80;
      }
      char * temp = new char[len + 1];
      strcpy(temp, data[i]);
      argv[i] = temp;
    }
  }
  // assignment constructor
};

/********
A class that inherited from std::vector<std::string> for simplicity
 ******/
class StringVec : public std::vector<std::string> {
  /*****
public:
  virtual ~StringVec() {
    StringVec::iterator it = begin();
    while (it != end()) {
      (*it).clear();
    }
  }
*******/
};

/*****
Given ECE551PATH (pPath), split it into vector of string
that each present one search path 
*******/
void splitPath(StringVec & vect, char * pPath) {
  char * startptr = pPath;
  char * endptr;
  size_t len;
  while ((endptr = strchr(startptr, ':')) != NULL) {
    len = endptr - startptr;
    char * dest = new char[len + 1];  // plus 1 for null terminator
    strncpy(dest, startptr, len);
    dest[len] = '\0';
    vect.push_back(std::string(dest));
    delete[] dest;
    // update startptr
    startptr = endptr + 1;
  }
  len = strlen(startptr);
  char * dest = new char[len + 1];
  strcpy(dest, startptr);
  vect.push_back(std::string(dest));
  delete[] dest;
  // std::cout << str << std::endl;
}

/********
Check if the command contains path
 *******/
bool containPath(const char * str) {
  while (*str != '\0') {
    if (*str == '/') {
      return true;
    }
    str++;
  }
  return false;
}

/*******
Execute the child process with specific path and arguments
 *******/
void executeProgram(char **& childargv, char ** childenviron, char * pPath) {
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
    StringVec paths;
    splitPath(paths, pPath);
    std::vector<std::string>::iterator it = paths.begin();
    while (it != paths.end()) {
      // concatenate path and program
      char * path = &(*it)[0];
      size_t pathlen = strlen(path);
      size_t comlen = strlen(childargv[0]);
      // keep a copy of old childargv[0]
      char * oldargv = new char[comlen + 1];
      strcpy(oldargv, childargv[0]);
      char * dest = new char[pathlen + comlen + 2];
      strcpy(dest, path);
      strcat(dest, "/");
      strcat(dest, childargv[0]);
      strcpy(childargv[0], dest);
      delete[] dest;
      // execute
      if (execve(childargv[0], childargv, childenviron) == -1) {
        // if command not found
        // if still has other path, check the next one
        if (it != (paths.end() - 1)) {
          std::cout << childargv[0] << ": command not found" << std::endl;
          ++it;
          strcpy(childargv[0], oldargv);
          delete[] oldargv;
        }
        // if is the last path, print message and exit
        else {
          delete[] oldargv;
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

/********
Given a string starts with space, returns a char pointer
to the first character that is not space.
 *******/
char * findNextArg(char * spaceptr) {
  while ((*spaceptr) == ' ') {
    spaceptr++;
  }
  return spaceptr;
}

/*****
Given the char pointer right after a starting quotation mark,
find the matching close quotation mark.
******/
char * findCloseQuote(char * start) {
  char * ptr;
  int count = 0;
  while ((ptr = strchr(start, '"')) != NULL) {
    // if has backslash before "
    char * preptr = ptr - 1;
    while (*preptr == '\\') {
      // multiple backslash
      count++;
      preptr--;
    }
    if (count % 2 == 0) {
      return ptr;
    }
    count = 0;
    start = ptr + 1;
  }
  return ptr;
}

/*******
Delete the backslashes within one argument string
********/
void backSlashHandler(char *& str) {
  char * start = str;
  char * slashptr;
  while ((slashptr = strchr(start, '\\')) != NULL) {
    // slash at begining
    if (slashptr - str == 0) {
      size_t len = strlen(slashptr) - 1;
      char * temp = new char[len + 1];
      strcpy(temp, slashptr + 1);
      strcpy(str, temp);
      delete[] temp;
    }  // slash at end
    else if (strlen(slashptr) == 1) {
      size_t len = strlen(str) - 1;
      char * temp = new char[len + 1];
      strncpy(temp, str, len);
      temp[len] = '\0';
      strcpy(str, temp);
      delete[] temp;
      return;
    }  // slash at middle
    else {
      // first half
      size_t len1 = slashptr - str;
      char * first = new char[len1 + 1];
      strncpy(first, str, len1);
      first[len1] = '\0';
      // last half
      size_t len2 = strlen(slashptr) - 1;
      char * last = new char[len2 + 1];
      strcpy(last, slashptr + 1);
      // concatenate string
      strcpy(str, first);
      strcat(str, last);
      delete[] first;
      delete[] last;
    }
    start = slashptr + 1;  // +2-1
  }
}

/******
Given the user input string, split the arguments 
and store into StringVec
 *****/
void splitArguments(StringVec & vec, std::string inputStr) {
  char * input = &inputStr[0];
  char * start = input;
  char * firstspace = strchr(start, ' ');
  bool hasQuote = false;
  while (firstspace != NULL) {
    size_t len = firstspace - start;
    if (hasQuote) {
      hasQuote = false;
      len--;
    }
    // if only has single backslash, can't be an argument
    if (len > 1 || *start != '\\') {
      char * dest = new char[len + 1];
      strncpy(dest, start, len);
      dest[len] = '\0';
      //  handle backslashes
      if (len > 1) {
        backSlashHandler(dest);
      }
      vec.push_back(std::string(dest));
      delete[] dest;
    }
    start = findNextArg(firstspace);
    // space at the end
    if (*start == '\0') {
      return;
    }
    // handle quotes
    if (*start == '"') {
      start++;
      char * closequote = findCloseQuote(start);
      hasQuote = true;
      if (closequote == NULL) {
        std::cout << "Error: doesn't find matching close quote.\n";
        return;
      }
      firstspace = strchr(closequote, ' ');
    }
    else {
      firstspace = strchr(start, ' ');
    }
  }
  // last argument
  size_t len = strlen(start);
  if (hasQuote) {
    hasQuote = false;
    len--;
  }
  if (len > 1 || *start != '\\') {
    char * dest = new char[len + 1];
    strncpy(dest, start, len);
    dest[len] = '\0';
    // handle backslashes
    if (len > 1) {
      backSlashHandler(dest);
    }
    vec.push_back(std::string(dest));
    delete[] dest;
  }
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

/********
Check if the user input string contains unclosed quotation mark
 *******/
bool hasUnclosedQuote(std::string inputStr) {
  char * input = &inputStr[0];
  char * start = input;
  int count = 0;
  int contslash = 0;
  char * ptr;
  while ((ptr = strchr(start, '"')) != NULL) {
    char * preptr = ptr - 1;
    while (*preptr == '\\') {
      contslash++;
      preptr--;
    }
    if (contslash % 2 == 0) {
      count++;
    }
    contslash = 0;
    start = ptr + 1;
  }
  return (count % 2) != 0;
}

/*******
Move the arguments from StringVec to a container that has a field of char **
Note that the last element of char ** is NULL as requested by execve
 ******/
void moveArguments(ArgvContainer & container, StringVec & vec) {
  size_t n = vec.size();
  char ** data = new char *[n + 1];
  for (size_t i = 0; i < n; i++) {
    std::string str = vec[i];
    size_t len = str.length();
    // command need more space for path
    if (i == 0) {
      len = len + 80;
    }
    char * dest = new char[len + 1];
    strcpy(dest, &str[0]);
    data[i] = dest;
  }
  // last element is NULL
  data[n] = NULL;
  container.attach(data, n + 1);
}

// TODO: check: set export rev env
bool isBuildInCommand(std::string inputStr) {
  return false;
}

/******
The program starts a simple command shell
 ******/
int main(int argc, char * argv[]) {
  char * pPath;
  pPath = getenv("PATH");
  if (pPath != NULL) {
    std::cout << "ECE551PATH is: " << pPath << std::endl;
  }
  while (1) {
    // repeat displaying the prompt and reading user input

    // TODO: show current directory
    std::string prompt = "ffosh$ ";
    std::string userinput;
    std::cout << prompt;
    std::getline(std::cin, userinput);
    // exit program if user enter exit or EOF
    if (std::cin.eof() || userinput.compare("exit") == 0) {
      break;
    }

    // TODO: build in commands: cd set export rev env
    if (isBuildInCommand(userinput)) {
      // TODO: handle build in commands
      continue;
    }
    // for external programs, check unclosed quotation mark
    else if (hasUnclosedQuote(userinput)) {
      std::cout << "Invalid command: contains unclosed quotation mark\n";
      continue;
    }
    // split arguments from user input
    StringVec arguments;
    splitArguments(arguments, userinput);
    // debug
    for (size_t i = 0; i < arguments.size(); i++) {
      std::cout << arguments[i] << std::endl;
    }
    // create a class to contain arguments
    ArgvContainer container;
    moveArguments(container, arguments);
    char * childenviron[] = {NULL};
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
      executeProgram(container.get(), childenviron, pPath);
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
