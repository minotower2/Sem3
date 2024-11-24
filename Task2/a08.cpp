#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "returns.h"
#include "array.h"
#include "solve.h"
#include "student.h"


int main(int argc, char** argv) { 
  char *filename = 0;
  int s, n, p, diff, task = 8, read_feedback;
  student *a, *b; 
  double t;

  if (!((argc >= 4) && (argc <= 5) &&
    (sscanf(argv[1], "%d", &n) == 1) && (n > 0) &&
    (sscanf(argv[2], "%d", &p) == 1) && (p >= 0) &&
    (sscanf(argv[3], "%d", &s) == 1) && (s >= 0) && (s < 5)))
  {
    printf("Usage %s\n", argv[0]);
    return USAGE_ERROR;
  }

  a = new student[n]; 
  if (!a) {
    printf("Not enough memory!\n");
    return MEMORY_ERROR;
  }

  b = new student[n];
  if (!b) {
    printf("Not enough memory!\n");
    return MEMORY_ERROR;
  }


  if (s == 0) {
    filename = argv[4];
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
  neumann_sort(a, b, n); 
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf("Resulting array: \n");
  print_array(a, n, p);
  diff = calc_diff(a, n);
  printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
  delete[] a;
  delete[] b;
  return 0;
}
