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

/**************
Given a stat struct, find the first char of
its human readable description of the permissions
 */
char findFstCInPermission(struct stat st) {
  char c;
  switch (st.st_mode & S_IFMT) {
    case S_IFBLK:
      c = 'b';
      break;
    case S_IFCHR:
      c = 'c';
      break;
    case S_IFDIR:
      c = 'd';
      break;
    case S_IFIFO:
      c = 'p';
      break;
    case S_IFLNK:
      c = 'l';
      break;
    case S_IFREG:
      c = '-';
      break;
    case S_IFSOCK:
      c = 's';
      break;
    default:
      c = '?';
      break;
  }
  return c;
}

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

/**************
Given a stat struct and a pointer to a string of length 11,
write human readable description to the given string
 */
void findPermissionDescription(struct stat st, char ** ptr) {
  char * str = *ptr;
  // null terminated the string
  str[10] = '\0';
  // fill in str
  str[0] = findFstCInPermission(st);
  str[1] = st.st_mode & S_IRUSR ? 'r' : '-';
  str[2] = st.st_mode & S_IWUSR ? 'w' : '-';
  str[3] = st.st_mode & S_IXUSR ? 'x' : '-';
  str[4] = st.st_mode & S_IRGRP ? 'r' : '-';
  str[5] = st.st_mode & S_IWGRP ? 'w' : '-';
  str[6] = st.st_mode & S_IXGRP ? 'x' : '-';
  str[7] = st.st_mode & S_IROTH ? 'r' : '-';
  str[8] = st.st_mode & S_IWOTH ? 'w' : '-';
  str[9] = st.st_mode & S_IXOTH ? 'x' : '-';
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
  // step 2
  char permissiondesc[11];
  char * ptr = permissiondesc;
  findPermissionDescription(st, &ptr);
  printf("Access: (%04o/%s)\n", st.st_mode & ~S_IFMT, permissiondesc);

  return EXIT_SUCCESS;
}
