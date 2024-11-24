#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "student.h"
#include "list_node.h"
#include "list2.h"

int main(int argc, char** argv) { 
  char *filename = 0;
  int r, task = 7, k;
  unsigned int len1, len2;
  double t;
  FILE *fp;
  io_status read;
  list2 lst;

  if (!((argc == 4) &&
    (sscanf(argv[1], "%d", &r) == 1) && (r >= 0) &&
    (sscanf(argv[3], "%d", &k) == 1)))
  {
    printf("Usage %s\n", argv[0]);
    return -1;
  }
  filename = argv[2];

  fp = fopen(filename, "r");
  if (!fp) {
    printf("Can't open file %s\n", filename);
    return -2;
  }
  read = lst.read_list(fp);
  switch(read) {
    case io_status::success:
      break;
    case io_status::eof:
      printf("Reached end of file\n");
      return -3;
    case io_status::format:
      printf("Wrong format of data\n");
      return -4;
    case io_status::memory:
      printf("Not enough memory\n");
      return -5;
    case io_status::read:
      printf("Failed to read list\n");
      return -6;
  }
  printf("List: \n");
  lst.print_list(r);  
  len1 = lst.get_length();
  t = clock();
  lst.solve7(k); 
  t = (clock() - t) / CLOCKS_PER_SEC;
  len2 = lst.get_length();
  printf("New list: \n");
  lst.print_list(r);
  printf ("%s : Task = %d Len Old = %u Len New = %u Elapsed = %.2f\n", argv[0], task, len1, len2, t);
  fclose(fp);
  return 0;
}
