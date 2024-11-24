#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "returns.h"
#include "data.h"

int read_array(data *a, int n, const char* filename, int s) {
  FILE* input_arr;
  int i;
  if (filename) {
    input_arr = fopen(filename, "r");
    if (!input_arr){
      delete[] a;
      return CANNOT_OPEN_FILE;
    }
    for (i = 0; i < n; i++) {
      if (a[i].read(input_arr) != 0) {
        delete[] a;
        return ERROR_READ;
      }
    }
    fclose(input_arr);
  }
  else {
    for (i = 0; i < n; i++) {
      a[i].init(f(s, n, i));
    }
  }
  return SUCCESS;
}

void print_array(data *a, int n, int p) {
  int i, num = (p > n ? n : p);
  for (i = 0; i < num; i++) {
    a[i].print();
  }
}

int calc_diff(data *a, int n) {
  int i, res = 0;
  for (i = 1; i < n; i++) {
    if (a[i] < a[i-1]) res++;
  }
  return res;
}

int f(int s, int n, int i) {
  switch(s) {
    case(1): return i;
    case(2): return n-i;
    case(3): return i/2;
    case(4): return n - i/2;
    default: return -1000000000;
  }
}
