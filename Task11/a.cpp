#include "student.h"
#include "btree.h"
#include <time.h>

int main(int argc, char* argv[]) {
  char *filename = 0;
  int r, k, m, task, res;
  double t;
  FILE *fp;
  io_status read;

  if (!((argc == 5) &&
    (sscanf(argv[1], "%d", &m) == 1) &&
    (sscanf(argv[2], "%d", &r) == 1) &&
    (sscanf(argv[3], "%d", &k) == 1)))
  {
    printf("Usage %s\n", argv[0]);
    return -1;
  }
  filename = argv[4];

  fp = fopen(filename, "r");
  if (!fp) {
    printf("Can't open file %s\n", filename);
    return -2;
  }

  b_tree<student> *birch = new b_tree<student>(m);
  read = birch->read(fp);
  switch(read) {
    case io_status::success:
      break;
    case io_status::eof:
      printf("Reached end of file\n");
      delete birch;
      return -3;
    case io_status::format:
      printf("Wrong format of data\n");
      delete birch;
      return -4;
    case io_status::memory:
      printf("Not enough memory\n");
      delete birch;
      return -5;
    case io_status::read:
      printf("Failed to read list\n");
      delete birch;
      return -6;
    case io_status::create:
      printf("aaaaaaaaaaaaaaaa\n");
      delete birch;
      return -7;
  }
  birch->print(r);
  (void) t;
  (void) task;
  (void) res;
  delete birch;
  fclose(fp);
  return 0;
}
