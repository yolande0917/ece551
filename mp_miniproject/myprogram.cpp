#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// TODO
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
  while (1) {
    // repeat displaying the prompt and reading user input
    std::string prompt = "ffosh$ ";
    std::string userinput;
    std::cout << prompt;
    std::getline(std::cin, userinput);
    // exit program if user enter exit or EOF
    if (std::cin.eof() || userinput.compare("exit") == 0) {
      break;
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
      execve(childargv[0], childargv, childenviron);
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
