#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "returns.h"
#include "array.h"
#include "solve.h"
#include "student.h"


int main(int argc, char** argv) { 
  char *filenamea = 0, *filenameb = 0;
  int na, nb, pa, pb, sa, sb, task = 2, read_feedback, diff = 0;
  student *a, *b, *c; 
  double t;

  if (!((argc >= 7) && (argc <= 9) && 
    (sscanf(argv[1], "%d", &na) == 1) && (na > 0) &&
    (sscanf(argv[2], "%d", &pa) == 1) && (pa >= 0) &&
    (sscanf(argv[3], "%d", &sa) == 1) && (sa >= 0) && (sa < 5)
    ))
  {
    printf("Usage %s\n", argv[0]);
    return USAGE_ERROR;
  }
  if (sa == 0) {
    filenamea = argv[4];
    if (!(
      (sscanf(argv[5], "%d", &nb) == 1) && (nb > 0) &&
      (sscanf(argv[6], "%d", &pb) == 1) && (pb >= 0) &&
      (sscanf(argv[7], "%d", &sb) == 1) && (sb >= 0) && (sb < 5)
    ))
    {
      printf("Usage %s\n", argv[0]);
      return USAGE_ERROR;
    }
    if (sb == 0) filenameb = argv[8];
  } 
  else {
    if (!( 
      (sscanf(argv[4], "%d", &nb) == 1) && (nb > 0) &&
      (sscanf(argv[5], "%d", &pb) == 1) && (pb >= 0) &&
      (sscanf(argv[6], "%d", &sb) == 1) && (sb >= 0) && (sb < 5)
    ))
    {
      printf("Usage %s\n", argv[0]);
      return USAGE_ERROR;
    }
    if (sb == 0) filenameb = argv[7];
  }


  a = new student[na]; 
  if (!a) {
    printf("Not enough memory!\n");
    return MEMORY_ERROR;
  }

  read_feedback = read_array(a, na, filenamea, sa);
  if (read_feedback != SUCCESS) {
    switch(read_feedback){
      case CANNOT_OPEN_FILE:
        printf("Cannot open %s\n", filenamea);
        break;
      case ERROR_READ:
        printf("Cannot read %s\n", filenamea);
        break;
      case MEMORY_ERROR:
        printf("Not enough memory!\n");
        break; 
      default:
        printf("Unknown error %d in %s\n", read_feedback, filenamea);
        break;
    }
    return 3;
  }

  b = new student[nb];
  if (!b) {
    printf("Not enough memory!\n");
    return MEMORY_ERROR;
  }

  read_feedback = read_array(b, nb, filenameb, sb);
  if (read_feedback != SUCCESS) {
    switch(read_feedback){
      case CANNOT_OPEN_FILE:
        printf("Cannot open %s\n", filenameb);
        break;
      case ERROR_READ:
        printf("Cannot read %s\n", filenameb);
        break;
      case MEMORY_ERROR:
        printf("Not enough memory!\n");
        break; 
      default:
        printf("Unknown error %d in %s\n", read_feedback, filenameb);
        break;
    }
    return 3;
  }

  c = new student[na+nb];
  if (!c) {
    printf("Not enough memory!\n");
    return MEMORY_ERROR;
  }


  printf("Array a: \n");
  print_array(a, na, pa);
  printf("Array b: \n");
  print_array(b, nb, pb);
  t = clock();
  merge_arrays(a, b, c, na, nb); 
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf("Array c: \n");
  print_array(c, na+nb, pa+pb);
  diff = calc_diff(c, na+nb);
  printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
  delete[] a;
  delete[] b;
  delete[] c;
  return 0;
}
