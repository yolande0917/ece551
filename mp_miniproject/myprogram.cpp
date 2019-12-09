#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

extern char ** environ;

/*******
A class that inherited from map<string, string> to store variables and values
 *******/
class VarMap : public std::map<std::string, std::string> {};

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
class StringVec : public std::vector<std::string> {};

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

/*******
Given a sourse string which starts with $ and may contain one variable, 
check with map if the string contains a stored variable right after $ sign.
Replace $ sign and variable name with the matching value,
and return the string after replacement.
 ******/
std::string searchVar(std::string source, VarMap & map) {
  size_t len = source.length();  // first char in source is $
  size_t trim = 0;
  while (len - trim > 1) {
    std::string name = source.substr(1, len - trim - 1);
    VarMap::iterator it;
    it = map.find(name);
    if (it != map.end()) {
      // found the key
      std::string value = it->second;
      if (trim > 0) {
        return (value + source.substr(len - trim, trim));
      }
      else {
        return value;
      }
    }
    trim++;
  }
  // var not found
  return source;
}

/*********
Given a string of argument, replace any stored variable name with its value
 *******/
std::string replaceVar(std::string str, VarMap & map) {
  std::string copy(str);
  char * input = &copy[0];
  char * start = input;
  char * dollar;
  // keep searching the string if contains $ sign
  while ((dollar = strchr(start, '$')) != NULL) {
    // find ending
    char * end = dollar + 1;
    while (isalpha(*end) || isdigit(*end) || *end == '_') {
      end++;
    }
    // no valid var name after $
    if (end - dollar == 1) {
      return copy;
    }
    // search variable
    size_t len = end - dollar;
    std::string varname = copy.substr(dollar - input, len);
    std::string aftervar = copy.substr(end - input);
    std::string newstr = searchVar(varname, map);
    // doesn't find var in the search string
    if (newstr.compare(varname) == 0) {
      start = end;
      continue;
    }
    size_t newlen = newstr.length();
    size_t beforelen = dollar - input;
    if (beforelen > 0) {
      std::string beforevar = copy.substr(0, beforelen);
      copy = beforevar + newstr + aftervar;
    }
    else {
      copy = newstr + aftervar;
    }
    // reassign input and start
    input = &copy[0];
    start = input + newlen + beforelen;
  }
  return copy;
}

/******
Given the user input string, split the arguments 
and store into StringVec
 *****/
void splitArguments(StringVec & vec, std::string inputStr, VarMap & map) {
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
        // replace var
        std::string newstr = replaceVar(std::string(dest), map);
        delete[] dest;
        vec.push_back(newstr);
      }
      else {
        vec.push_back(std::string(dest));
        delete[] dest;
      }
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
      // replace var
      std::string newstr = replaceVar(std::string(dest), map);
      delete[] dest;
      vec.push_back(newstr);
    }
    else {
      vec.push_back(std::string(dest));
      delete[] dest;
    }
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

/******
Check if the input is build in command
 ******/
bool isBuildInCommand(std::string command) {
  std::string str(command);
  if (str.compare("cd") == 0 || str.compare("set") == 0 || str.compare("export") == 0 ||
      str.compare("rev") == 0 || str.compare("env") == 0) {
    return true;
  }
  return false;
}

/******
For build in commands, splits the input string into argument strings
and store to the given string vector
 ******/
void splitCommandArg(StringVec & vec, std::string inputStr) {
  std::string inputcopy(inputStr);
  char * input = &inputcopy[0];
  char * start = input;
  char * firstspace = strchr(start, ' ');
  while ((firstspace = strchr(start, ' ')) != NULL) {
    size_t len = firstspace - start;
    char * dest = new char[len + 1];
    strncpy(dest, start, len);
    dest[len] = '\0';
    vec.push_back(dest);
    delete[] dest;
    while (*firstspace == ' ') {
      firstspace++;
    }
    if (*firstspace == '\0') {
      return;
    }
    start = firstspace;
  }
  size_t len = strlen(start);
  char * dest = new char[len + 1];
  strcpy(dest, start);
  vec.push_back(dest);
  delete[] dest;
}

/********
Given a string vector that contain all arguments for cd command,
change the current directory
Returns 0 if succeeds, -1 if fails
 *******/
int runcd(StringVec & vec) {
  std::string str(vec[1]);
  char * dir = &str[0];
  int result = chdir(dir);
  if (result == -1) {
    std::cout << "cd: " << dir << ": No such file or directory\n";
    return -1;
  }
  return 0;
}

/*****
Given the map stores all variables and values, and the key value pair to set,
insert the pair to map and replace the pair if already exists in map 
Returns 0 if succeeds, -1 if fails
 *****/
int runset(VarMap & map, std::string key, std::string value) {
  // check if key is valid
  char * c = &key[0];
  while (*c != '\0') {
    if (!(isalpha(*c) || isdigit(*c) || *c == '_')) {
      std::cout << "set: Invalid variable name\n";
      return -1;
    }
    c++;
  }
  // if already contains the key, erase it
  VarMap::iterator it;
  it = map.find(key);
  if (it != map.end()) {
    map.erase(it);
  }
  // insert the key value pair
  map.insert(std::pair<std::string, std::string>(key, value));
  // set ECE551PATH in env
  if (key.compare("ECE551PATH") == 0) {
    // TODO: check if is valid path
    std::string mypath = "ECE551PATH=" + value;
    setenv("ECE551PATH", &value[0], 1);
    //  putenv(&mypath[0]);
  }

  return 0;
}

/******
Reverse the given string
 *****/
std::string reverse(std::string input) {
  std::string output;
  size_t len = input.length();
  int i = len - 1;
  while (i >= 0) {
    output.append(1, input[i]);
    i--;
  }
  return output;
}

/*******
Run the rev command.
Returns 0 if succeeds, -1 if fails
 ******/
int runrev(VarMap & map, std::string key) {
  // check if key is valid
  char * c = &key[0];
  while (*c != '\0') {
    if (!(isalpha(*c) || isdigit(*c) || *c == '_')) {
      std::cout << "rev: Invalid variable name\n";
      return -1;
    }
    c++;
  }
  // Find the iterator that points to the pair
  VarMap::iterator it;
  it = map.find(key);
  // If not found, print error
  if (it == map.end()) {
    std::cout << "rev: Variable name not found\n";
    return -1;
  }
  std::string oldvalue = it->second;
  map.erase(it);
  std::string value = reverse(oldvalue);
  map.insert(std::pair<std::string, std::string>(key, value));
  return 0;
}

/******
TODO
 ******/
int runenv() {
  char ** env;
  for (env = environ; *env != 0; env++) {
    std::cout << *env << "\n";
  }
  return 0;
}

/*******
TODO
******/
int runexport(VarMap & map, std::string key) {
  // check if key is valid
  char * c = &key[0];
  while (*c != '\0') {
    if (!(isalpha(*c) || isdigit(*c) || *c == '_')) {
      std::cout << "export: Invalid variable name\n";
      return -1;
    }
    c++;
  }
  // Find the iterator that points to the pair
  VarMap::iterator it;
  it = map.find(key);
  // If not found, print error
  if (it == map.end()) {
    std::cout << "export: Variable name not found\n";
    return -1;
  }
  // export the variable and value to environment
  std::string value = it->second;
  std::string myvar = key + "=" + value;

  setenv(&key[0], &value[0], 1);

  return 0;
}

/********
Handle all build in commands
If successfully runs the command, return 0. If fails, return -1
 *******/
int commandHandler(StringVec & vec, std::string inputStr, VarMap & map) {
  std::string str(vec[0]);
  // cd
  if (str.compare("cd") == 0) {
    if (vec.size() != 2) {
      std::cout << "cd: Invalid argument\n";
      return -1;
    }
    return runcd(vec);
  }
  // set
  else if (str.compare("set") == 0) {
    if (vec.size() < 3) {
      std::cout << "set: Invalid arguments\n";
      return -1;
    }
    // find the value
    std::string inputcopy(inputStr);
    size_t start = 3;  // start with index of first space
    while (inputcopy[start] == ' ') {
      start++;
    }
    while (inputcopy[start] != ' ') {
      start++;
    }
    while (inputcopy[start] == ' ') {
      start++;
    }
    std::string value = inputcopy.substr(start);
    return runset(map, vec[1], value);
  }
  // export
  else if (str.compare("export") == 0) {
    if (vec.size() != 2) {
      std::cout << "export: Invalid argument\n";
      return -1;
    }
    return runexport(map, vec[1]);
  }
  // rev
  else if (str.compare("rev") == 0) {
    if (vec.size() != 2) {
      std::cout << "rev: Invalid argument\n";
      return -1;
    }
    return runrev(map, vec[1]);
  }
  // env
  else if (str.compare("env") == 0) {
    if (vec.size() != 1) {
      std::cout << "env: Invalid argument\n";
      return -1;
    }
    return runenv();
  }
  return -1;
}

/******
The program starts a simple command shell
 ******/
int main(void) {
  VarMap map;
  char * pPath;
  pPath = getenv("PATH");
  if (pPath == NULL) {
    std::cout << "Error: PATH not found in environment variables.\n";
    return EXIT_FAILURE;
  }
  map.insert(std::pair<std::string, std::string>("ECE551path", pPath));
  // put ECE551PATH into env
  std::string mypath = "ECE551PATH=" + std::string(pPath);
  putenv(&mypath[0]);

  while (1) {
    // update path in the begining of each loop
    pPath = getenv("ECE551PATH");
    if (pPath == NULL) {
      std::cout << "Error: ECE551PATH not found in environment variables.\n";
      break;
    }
    // repeat displaying the prompt and reading user input
    // show current directory and prompt
    char * currentdir = get_current_dir_name();
    if (currentdir == NULL) {
      perror("get_current_dir_name");
      break;
    }
    std::string prompt = "ffosh:";
    std::string userinput;
    std::cout << prompt << currentdir << " $";
    free(currentdir);
    std::getline(std::cin, userinput);
    // exit if encounters eof
    if (std::cin.eof()) {
      break;
    }
    // trim spaces at the begining
    size_t start = 0;
    while (userinput.at(start) == ' ') {
      start++;
    }
    if (userinput.at(start) == '\0') {
      std::cout << "Invalid input\n";
      break;
    }
    userinput = userinput.substr(start);
    // exit program if user enter exit or EOF
    // TODO: spaces after exit
    if (userinput.compare("exit") == 0) {
      break;
    }

    // build in commands: cd set export rev env
    StringVec commandargs;
    splitCommandArg(commandargs, userinput);
    if (isBuildInCommand(commandargs[0])) {
      // TODO: handle build in commands
      if (commandHandler(commandargs, userinput, map) == -1) {
        std::cout << "Command failed\n";
      }
      continue;
    }
    // for external programs, check unclosed quotation mark
    else if (hasUnclosedQuote(userinput)) {
      std::cout << "Invalid command: contains unclosed quotation mark\n";
      continue;
    }
    // split arguments from user input
    // search the map and replace var
    StringVec arguments;
    splitArguments(arguments, userinput, map);
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
