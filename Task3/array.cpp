#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "returns.h"
#include "student.h"

int read_array(student *a, int n, const char* filename, int s) {
  FILE* input_arr;
  int i;
  if (filename) {
    input_arr = fopen(filename, "r");
    if (!input_arr){
      delete[] a;
      return CANNOT_OPEN_FILE;
    }
    for (i = 0; i < n; i++) {
      if (a[i].read(input_arr) != io_status::success) {
        delete[] a;
        return ERROR_READ;
      }
    }
    fclose(input_arr);
  }
  else {
    for (i = 0; i < n; i++) {
      if (a[i].formul_init(f(s, n, i)) != io_status::success) {
        delete[] a;
        return ERROR_READ;
      }
    }
  }
  return SUCCESS;
}

void print_array(student *a, int n, int p) {
  int i, num = (p > n ? n : p);
  for (i = 0; i < num; i++) {
    a[i].print();
  }
}

int calc_diff(student *a, int n) {
  int i, res = 0;
  for (i = 1; i < n; i++) {
    if (a[i] < a[i-1]) res++;
  }
  return res;
}

int f(int s, int n, int i) {
  switch(s) {
    case(1): return i + 1;
    case(2): return n - i - 1;
    case(3): return (i+1)/2;
    case(4): return n - (i+1)/2;
    default: return -1000000000;
  }
}
