#include "list2.h"
#include "student.h"
#include "tree.h"
#include <time.h>

int list2::max_read = 0;
int list2::max_print = 0;

int main(int argc, char* argv[]) {
  char *filename = 0;
  int r, k, task, res;
  double t;
  FILE *fp;
  io_status read;

  if (!((argc == 4) &&
    (sscanf(argv[1], "%d", &r) == 1) &&
    (sscanf(argv[3], "%d", &k) == 1)))
  {
    printf("Usage %s\n", argv[0]);
    return -1;
  }
  filename = argv[2];

  list2::set_max_print(r);
  list2::set_max_read(k);

  fp = fopen(filename, "r");
  if (!fp) {
    printf("Can't open file %s\n", filename);
    return -2;
  }

  tree<student> *birch = new tree<student>;
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
  }
  birch->print(r);

  task = 1;
  t = clock();
  res = birch->solve1(birch->get_root());
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  task = 2;
  t = clock();
  res = birch->solve2(birch->get_root());
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  task = 3;
  t = clock();
  res = birch->solve3(birch->get_root());
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  task = 4;
  t = clock();
  res = birch->solve4(birch->get_root());
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  task = 5;
  t = clock();
  res = birch->solve5(birch->get_root());
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  delete birch;
  fclose(fp);


  fp = fopen(filename, "r");
  if (!fp) {
    printf("Can't open file %s\n", filename);
    return -2;
  }
  tree<list2> *pine = new tree<list2>;
  read = pine->read(fp);
  switch(read) {
    case io_status::success:
      break;
    case io_status::eof:
      printf("Reached end of file\n");
      delete pine;
      return -3;
    case io_status::format:
      printf("Wrong format of data\n");
      delete pine;
      return -4;
    case io_status::memory:
      printf("Not enough memory\n");
      delete pine;
      return -5;
    case io_status::read:
      printf("Failed to read list\n");
      delete pine;
      return -6;
  }
  pine->print(r);

  task = 1;
  t = clock();
  res = pine->solve1(pine->get_root());
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  task = 2;
  t = clock();
  res = pine->solve2(pine->get_root());
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  task = 3;
  t = clock();
  res = pine->solve3(pine->get_root());
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  task = 4;
  t = clock();
  res = pine->solve4(pine->get_root());
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  task = 5;
  t = clock();
  res = pine->solve5(pine->get_root());
  t = (clock()-t)/CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], task, k, res, t);

  delete pine;
  fclose(fp);
  return 0;
}
