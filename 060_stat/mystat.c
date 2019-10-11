#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/***********
Given a stat struct, find its file type information
 */
char * findFileType(struct stat st) {
  char * str;
  switch (st.st_mode & S_IFMT) {
    case S_IFBLK:
      str = "block special file";
      break;
    case S_IFCHR:
      str = "character special file";
      break;
    case S_IFDIR:
      str = "directory";
      break;
    case S_IFIFO:
      str = "fifo";
      break;
    case S_IFLNK:
      str = "symbolic link";
      break;
    case S_IFREG:
      str = "regular file";
      break;
    case S_IFSOCK:
      str = "socket";
      break;
    default:
      str = "unknown";
      break;
  }
  return str;
}

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

int main(int argc, char * argv[]) {
  // check if have correct args number
  if (argc != 2) {
    fprintf(stderr, "Usage case: ./mystat pathname\n");
    exit(EXIT_FAILURE);
  }
  // create a stat to store file information
  struct stat st;
  if (lstat(argv[1], &st) == -1) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }
  // step 1
  printf("  File: ‘%s’\n", argv[1]);
  char * filetype = findFileType(st);
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         st.st_size,
         st.st_blocks,
         st.st_blksize,
         filetype);
  printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
         st.st_dev,
         st.st_dev,
         st.st_ino,
         st.st_nlink);

  return EXIT_SUCCESS;
}
