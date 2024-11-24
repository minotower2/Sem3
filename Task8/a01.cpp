#include <stdio.h>
#include <time.h>
#include "student.h"
#include "tree_node.h"
#include "tree.h"

int main(int argc, char** argv) { 
  char *filename = 0;
  int r, task = 1;
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

  printf ("Original tree:\n");
  birch.print (r);

  int T = birch.get_count_total (birch.get_root());
  int L = birch.get_count_leaf (birch.get_root());
  int C1 = birch.get_count_1 (birch.get_root());
  int C2 = birch.get_count_2 (birch.get_root());
  int H = birch.get_height (birch.get_root());
  int W = birch.get_width (birch.get_root());
  int B = birch.get_balance (birch.get_root());
  printf ("%s : Task = %d T = %d L = %d C1 = %d C2 = %d H = %d W = %d B = %d \n", argv[0], task, T, L, C1, C2, H, W, B);

  t = clock ();
  birch.solve1(birch.get_root());
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("Modified tree:\n");
  birch.print (r);

  T = birch.get_count_total (birch.get_root());
  L = birch.get_count_leaf (birch.get_root());
  C1 = birch.get_count_1 (birch.get_root());
  C2 = birch.get_count_2 (birch.get_root());
  H = birch.get_height (birch.get_root());
  W = birch.get_width (birch.get_root());
  B = birch.get_balance (birch.get_root());
  printf ("%s : Task = %d T = %d L = %d C1 = %d C2 = %d H = %d W = %d B = %d Elapsed = %.2f\n", argv[0], task, T, L, C1, C2, H, W, B, t);

  fclose(fp);
  return 0;
}
