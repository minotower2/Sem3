#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "returns.h"
#include "array.h"
#include "solve.h"
#include "data.h"

int data::p=0;

int main(int argc, char** argv) { 
  char *filename = 0, *x = 0;
  int s, n, p, res, diff, task = 1, read_feedback;
  data *a; 
  data dop;
  double t;
  FILE *fp;

  if (!((argc >=5) && (argc <= 6) &&
    (sscanf(argv[2], "%d", &n) == 1) && (n > 0) &&
    (sscanf(argv[3], "%d", &p) == 1) && (p >= 0) &&
    (sscanf(argv[4], "%d", &s) == 1) && (s >= 0) && (s < 5)))
  {
    printf("Usage %s\n", argv[0]);
    return USAGE_ERROR;
  }
  a = new data[n]; 
  if (!a) {
    printf("Not enough memory!\n");
    return MEMORY_ERROR;
  }
  a[0].set_p(p);
  x = argv[1];
  fp = fopen(x, "r");
  res = dop.read(fp);
  if(res) {
    printf("Couldn't read additional file %d\n", res);
    delete[] a;
    return 1;
  }
  fclose(fp);

  if (s == 0) {
    filename = argv[5];
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
  res = binary_search(a, n, dop); 
  t = (clock() - t) / CLOCKS_PER_SEC;
  diff = calc_diff(a, n);
  printf("Res = %d\n", res);
  printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
  delete[] a;
  return 0;
}
