#include "student.h"
#include "solve.h"
#include "returns.h"
#include "array.h"
#include <algorithm>

int binary_search(student *a, int n, student& x) {
  int left = 0, right = n, mid;
  while (left < right) {
    mid = (left + right) / 2;
    if (a[mid] < x) {
      left = mid + 1;
    }
    else {
      right = mid;
    }
  }
  return right;
}

void merge_arrays(student *a, student *b, student *c, int n, int m) {
  int i = 0, j = 0, k = 0;
  while ((i < n) && (j < m)) {
    if (a[i] < b[j]) {
      c[k] = (student&&) a[i];
      k++;
      i++;
    }
    else {
      c[k] = (student&&) b[j];
      k++;
      j++;
    }
  }
  if (k < n + m) {
    if (i < n) {
      while (k < n + m) {
        c[k] = (student&&)a[i];
        i++;
        k++;
      }
    }
    else {
      while (k < n + m) {
        c[k] = (student&&)b[j];
        j++;
        k++;
      }
    }
  }
}

int split_func(student *a, int n, int m) {
  int i = 0;
  int j = n - 1;
  for(; i < n; ++i) {
    if (!(a[i] < a[m])) break;
  }
  for(; j>= 0; --j) {
    if (!(a[j] > a[m])) break;
  }
  while(i <= j) {
    std::swap(a[j], a[i]);
    if (i == m) m = j;
    else if (j == m) m = i;
    i++;
    j--;
    for(; i < n; ++i) {
      if (!(a[i] < a[m])) break;
    }
    for (; j >= 0; --j) {
      if (!(a[j] > a[m])) break;
    }
  }
  return i; 
}

void bubble_sort(student *a, int n) {
  int i, j;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n - i - 1; ++j) {
      if (a[j] > a[j + 1]) {
        std::swap(a[j], a[j+1]);
      }
    }
  }
}

void selection_sort(student *a, int len) {
  int i, j;
  int mn = 0;
  for (i = 0; i < len; ++i) {
    mn = i;
    for (j = i; j < len; ++j) {
      if (a[j] < a[mn]) mn = j;
    }
    std::swap(a[i], a[mn]);
  }
}

void insertion_sort(student *a, int n) {
  int i, j;
  student cur;
  for (i = 0; i < n; ++i) {
    cur = (student&&)a[i];
    j = i - 1;
    while (j >= 0 && (a[j] > cur)) {
      a[j + 1] = (student&&)a[j];
      j--;
    }
    a[j + 1] = (student&&)cur;
  }
}

void binary_insertion_sort(student *a, int n) {
  student t;
  int i, k, left, right, mid;
    for (i = 1; i < n; i++)  { 
      left = 0;
      right = i;
      while (left < right) {
        mid = (left + right) / 2;
        if (a[mid] < a[i])
          left = mid + 1;
        else
	  right = mid;
      }
      t = (student&&)a[i];
      for (k = i; k > left; k--)  {
        a[k] = (student&&)a[k - 1];
      }
      a[left] = (student&&)t;
  }
}

void neumann_sort(student *a, student *b, int n) {
  int i, j, k, l, t;
  int last;
  for (i = 1; i < n; i *= 2) {
    k = n / (2 * i) * 2 * i;
    for (j = 0; j < k; j += 2 * i) {
      merge_arrays(a + j, a + i + j, b, i, i);
      for (l = 0; l < 2 * i; l++) {
        a[j + l] = (student&&)b[l];
      }
    }
    last = n - k;
    if (last <= i)
      continue;  
    merge_arrays(a + k, a + i + k, b, i, last - i);
    for (t = 0; t < last; ++t) {
      a[t + k] = (student&&)b[t];
    }
  }
}

void quicksort(student *a, int n) {
  int pos;
  student t;
  while (n > 1) {
    pos = split_func(a, n, n / 2);
    if (pos == 0) {
      std::swap(a[0], a[n/2]);
      n--;
      a++;
    }
    else if (pos == n) {
      std::swap(a[n-1], a[n/2]);
      n--;
    }
    else {
      if (pos < n/2) {
        quicksort(a, pos);
        a += pos;
        n -= pos;
      }
      else {
        quicksort(a + pos, n - pos);
        n = pos;
      }
    }
  }
}


void heapsort(student *a, int n) {
  int i, j, k, des_index;
  student des;
  student cur;
  for (i = 1; i < n; ++i) {
    des = (student&&)a[i];
    for (des_index = i; des_index > 0; des_index = (des_index - 1) / 2) {
      if (des > a[(des_index - 1) / 2]) {
        a[des_index] = (student&&)(a[(des_index - 1) / 2]);
      }
      else {
        a[des_index] = (student&&)(des);
        break;
      }
    }
    if (des_index == 0)
      a[0] = (student&&)(des);
  }

  for (j = n - 1; j > 0; j--) {
    k = 0;
    cur = (student&&)(a[j]);
    a[j] = (student&&)(a[0]);
    while (2 * k + 2 < j) {
      if (a[2 * k + 1] < a[2 * k + 2]) {
        if (!(cur < a[2 * k + 2])) {
          a[k] = (student&&)(cur);
          break;
        }
        a[k] = (student&&)(a[2 * k + 2]);
        k = 2 * k + 2;
      }
      else {
        if (!(cur < a[2 * k + 1])) {
          a[k] = (student&&)(cur);
          break;
        }
        a[k] = (student&&)(a[2 * k + 1]);
        k = 2 * k + 1; 
      }
    }
    if (2 * k + 2 >= j) {
      if (2 * k + 1 < j) {
        if (cur > a[2 * k + 1])
          a[k] = (student&&)(cur);
        else {
          a[k] = (student&&)(a[2 * k  + 1]);
          a[2 * k + 1] = (student&&)(cur);
        }
      }
      else 
        a[k] = (student&&)(cur);
    }
  }
}
