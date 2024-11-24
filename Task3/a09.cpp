#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "returns.h"
#include "array.h"
#include "solve.h"
#include "student.h"

int main(int argc, char** argv) { 
  char *filename = 0, *x = 0;
  int xn, s, n, p, res, task = 9, read_feedback;
  student *a; 
  student dop;
  double t;
  io_status read;

  if (!((argc >=6) && (argc <= 7) &&
    (sscanf(argv[2], "%d", &xn) == 1) &&
    (sscanf(argv[3], "%d", &n) == 1) && (n > 0) &&
    (sscanf(argv[4], "%d", &p) == 1) && (p >= 0) &&
    (sscanf(argv[5], "%d", &s) == 1) && (s >= 0) && (s < 5)))
  {
    printf("Usage %s\n", argv[0]);
    return USAGE_ERROR;
  }
  a = new student[n]; 
  if (!a) {
    printf("Not enough memory!\n");
    return MEMORY_ERROR;
  }
  x = argv[1];
  
  read = dop.full_init(x, xn);
  if (read != io_status::success) {
    switch (read) {
      case io_status::eof:
        printf("Reached the end of file\n");
        break;
      case io_status::memory:
        printf("Not enough memory\n");
        break;
      case io_status::format:
        printf("Wrong format\n");
        break;
      case io_status::success:
        break;
    }
    return 1;
  }

  if (s == 0) {
    filename = argv[6];
  }

  read_feedback = read_array(a, n, filename, s);
  if (read_feedback != SUCCESS) {
    switch(read_feedback){
      case CANNOT_OPEN_FILE:
        printf("Cannot open %s\n", filename);
        break;
      case ERROR_READ:
        printf("Cannot read %s\n", filename);
        break;
      case MEMORY_ERROR:
        printf("Not enough memory!\n");
        break; 
      default:
        printf("Unknown error %d in %s\n", read_feedback, filename);
        break;
    }
    return 3;
  }

  printf("Array: \n");
  print_array(a, n, p);
  t = clock();
  res = solve9(a, n, dop); 
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf("Resulting array: \n");
  print_array(a, res, p);
  printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
  delete [] a;
  return 0;
}
