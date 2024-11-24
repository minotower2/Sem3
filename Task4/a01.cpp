#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"
#include "student.h"
#include "list_node.h"
#include "lists.h"

int main(int argc, char** argv) { 
  char *filename = 0;
  int r, res, task = 1;
  double t;
  list_node *head;
  FILE *fp;
  io_status read;

  if (!((argc == 3) &&
    (sscanf(argv[1], "%d", &r) == 1) && (r >= 0)))
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

  read = read_list(fp, &head);
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
  print_list(head, r);
  t = clock();
  res = solve1(head); 
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
  delete_list(head);
  fclose(fp);
  return 0;
}
