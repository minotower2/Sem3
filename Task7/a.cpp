#include <stdio.h>
#include <time.h>
#include "student.h"
#include "tree_node.h"
#include "tree.h"

int main(int argc, char** argv) { 
  char *filename = 0;
  int r, res, task;
  double t;
  FILE *fp;
  io_status read;
  tree birch;

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
  read = birch.read(fp);
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
  printf("Tree: \n");
  birch.print(r);  

  task = 1;
  t = clock();
  res = birch.solve1(birch.get_root());
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);

  task = 2;
  t = clock();
  res = birch.solve2(birch.get_root());
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);

  task = 3;
  t = clock();
  res = birch.solve3(birch.get_root());
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);

  task = 4;
  t = clock();
  res = birch.solve4(birch.get_root());
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);

  task = 5;
  t = clock();
  res = birch.solve5(birch.get_root());
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);

  fclose(fp);
  return 0;
}
