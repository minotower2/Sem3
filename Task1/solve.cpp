#include "data.h"
#include "solve.h"
#include "returns.h"
#include "array.h"

int binary_search(data *a, int n, data& x) {
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

void merge_arrays(data *a, data *b, data *c, int n, int m) {
  int i = 0, j = 0, k = 0;
  while ((i < n) && (j < m)) {
    if (a[i] < b[j]) {
      c[k] = a[i];
      k++;
      i++;
    }
    else {
      c[k] = b[j];
      k++;
      j++;
    }
  }
  if (k < n + m) {
    if (i < n) {
      while (k < n + m) {
        c[k] = a[i];
        i++;
        k++;
      }
    }
    else {
      while (k < n + m) {
        c[k] = b[j];
        j++;
        k++;
      }
    }
  }
}

int split_func(data *a, int n, int m) {
  int i = 0;
  int j = n - 1;
  data temp;
  while(i <= j) {
    if(a[i] < a[m])
      i++;
    else  {
      if (!(a[j] < a[m]))
        j--;
      else {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        i++;
        j--;
      }
    }
  }
  return i; 
}

void bubble_sort(data *a, int n) {
  int i, j;
  data t;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n - i - 1; ++j) {
      if (a[j] > a[j + 1]) {
        t = a[j];
        a[j] = a[j + 1];
        a[j + 1] = t;
      }
    }
  }
}

void selection_sort(data *a, int len) {
  int i, j;
  int mn = 0;
  data t;
  for (i = 0; i < len; ++i) {
    mn = i;
    for (j = i; j < len; ++j) {
      if (a[j] < a[mn]) mn = j;
    }
    t = a[i];
    a[i] = a[mn];
    a[mn] = t;
  }
}

void insertion_sort(data *a, int n) {
  int i, j;
  data cur;
  for (i = 0; i < n; ++i) {
    cur = a[i];
    j = i - 1;
    while (j >= 0 && (a[j] > cur)) {
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = cur;
  }
}

void binary_insertion_sort(data *a, int n) {
  data t;
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
      t = a[i];
      for (k = i; k > left; k--)  {
        a[k] = a[k - 1];
      }
      a[left] = t;
  }
}

void neumann_sort(data *a, data *b, int n) {
  int i, j, k;
  int last;
  for (i = 1; i < n; i *= 2) {
    k = n / (2 * i) * 2 * i;
    for (j = 0; j < k; j += 2 * i) {
      int l;
      merge_arrays(a + j, a + i + j, b, i, i);
      for (l = 0; l < 2 * i; l++) {
        a[j + l] = b[l];
      }
    }
    last = n - k;
    if (last <= i)
      continue;  
    merge_arrays(a + k, a + i + k, b, i, last - i);
    for (int t = 0; t < last; ++t) {
      a[t + k] = b[t];
    }
  }
}

void quicksort(data *a, int n) {
  int pos;
  data t;
  while (n > 1) {
    pos = split_func(a, n, n / 2);
    if (pos == 0) {
      t = a[0];
      a[0] = a[n / 2];
      a[n / 2] = t;
      n--;
      a += 1;
      continue;
    }
    if (pos < n - pos) {
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

void heapsort(data *a, int n) {
  int i, j, k, des_index;
  data des;
  data cur;
  for (i = 1; i < n; ++i) {
    des = a[i];
    for (des_index = i; des_index > 0; des_index = (des_index - 1) / 2) {
      if (des > a[(des_index - 1) / 2]) {
        a[des_index] = a[(des_index - 1) / 2];
      }
      else {
        a[des_index] = des;
        break;
      }
    }
    if (des_index == 0)
      a[0] = des;
  }

  for (j = n - 1; j > 0; j--) {
    k = 0;
    cur = a[j];
    a[j] = a[0];
    a[0] = cur;
    while (2 * k + 2 < j) {
      if (a[2 * k + 1] < a[2 * k + 2]) {
        if (!(cur < a[2 * k + 2])) {
          a[k] = cur;
          break;
        }
        a[k] = a[2 * k + 2];
        k = 2 * k + 2;
      }
      else {
        if (!(cur < a[2 * k + 1])) {
          a[k] = cur;
          break;
        }
        a[k] = a[2 * k + 1];
        k = 2 * k + 1; 
      }
    }
    if (2 * k + 2 >= j) {
      if (2 * k + 1 < j) {
        if (cur > a[2 * k + 1])
          a[k] = cur;
        else {
          a[k] = a[2 * k  + 1];
          a[2 * k + 1] = cur;
        }
      }
      else 
        a[k] = cur;
    }
  }
}

