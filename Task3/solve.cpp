#include "solve.h"
#include "student.h"
#include <stdio.h>

int solve1(student *a , int n) {
  int i, flag = 0, dif = 0;
  student bad;
  if (n < 2) return n;
  for (i = 1; i < n; i++) {
    if ((flag == 0) && (a[i] < a[i-1-dif])){
      flag = 1;
      dif++;
      bad = (student&&) a[i];
    }
    else if ((flag == 1) && (a[i] < bad)){
      dif++;
      bad = (student&&) a[i];
    }
    else {
      a[i-dif] = (student&&) a[i];
      flag = 0;
    }
  }
  return n-dif;
}

// flag = 0 - default; flag = 1 - bad; flag = 2 - baddie; flag = 3 - bad and baddie
int solve2(student *a , int n) {
  int i, flag = 0, dif = 0;
  student bad, baddie;
  if (n < 3) return n;
  for (i = 2; i < n; i++) {
    switch(flag) {
      case 0:
        if ((a[i] > a[i-1-dif]) && (a[i] > a[i-2-dif])) {
          flag = 1;
          dif++;
          bad = (student&&) a[i];
        }
        else {
          a[i-dif] = (student&&) a[i];
        }
        break;
      case 1:
        if ((a[i] > bad) && (a[i] > a[i-2-dif])) {
          flag = 3;
          dif++;
          baddie = (student&&) bad;
          bad = (student&&) a[i];
        }
        else {
          flag = 2;
          baddie = (student&&) bad;
          a[i-dif] = (student&&) a[i];
        }
        break;
      case 2:
        if ((a[i] > baddie) && (a[i] > a[i-1-dif])) {
          flag = 1;
          dif++;
          bad = (student&&) a[i];
        }
        else {
          flag = 0;
          a[i-dif] = (student&&) a[i];
        }
        break;
      case 3:
        if ((a[i] > bad) && (a[i] > baddie)) {
          dif++;
          baddie = (student&&) bad;
          bad = (student&&) a[i];
        }
        else {
          flag = 2;
          baddie = (student&&) bad;
          a[i-dif] = (student&&) a[i];
        }
        break;
    }
  }
  return n-dif;
}

int solve3(student *a , int n) {
  int i, flag = 0, dif = 0;
  student bad;
  if (n < 2) return n;
  for (i = 1; i < n-1; i++) {
    if ((a[i] < a[i+1]) && (flag == 0) && (a[i] < a[i-1-dif])){
      flag = 1;
      dif++;
      bad = (student&&) a[i];
    }
    else if ((a[i] < a[i+1]) && (flag == 1) && (a[i] < bad)){
      dif++;
      bad = (student&&) a[i];
    }
    else {
      a[i-dif] = (student&&) a[i];
      flag = 0;
    }
  }
  a[i-dif] = (student&&) a[i];
  return n-dif;
}

int solve4(student *a , int n) {
  int i, flag = 0, dif = 0;
  student bad, baddie;
  if (n < 3) return n;
  for (i = 2; i < n-2; i++) {
    switch(flag) {
      case 0:
        if ((a[i] > a[i+1]) && (a[i] > a[i+2]) && (a[i] > a[i-1-dif]) && (a[i] > a[i-2-dif])) {
          flag = 1;
          dif++;
          bad = (student&&) a[i];
        }
        else {
          a[i-dif] = (student&&) a[i];
        }
        break;
      case 1:
        if ((a[i] > a[i+1]) && (a[i] > a[i+2]) && (a[i] > bad) && (a[i] > a[i-2-dif])) {
          flag = 3;
          dif++;
          baddie = (student&&) bad;
          bad = (student&&) a[i];
        }
        else {
          flag = 2;
          baddie = (student&&) bad;
          a[i-dif] = (student&&) a[i];
        }
        break;
      case 2:
        if ((a[i] > a[i+1]) && (a[i] > a[i+2]) && (a[i] > baddie) && (a[i] > a[i-1-dif])) {
          flag = 1;
          dif++;
          bad = (student&&) a[i];
        }
        else {
          flag = 0;
          a[i-dif] = (student&&) a[i];
        }
        break;
      case 3:
        if ((a[i] > a[i+1]) && (a[i] > a[i+2]) && (a[i] > bad) && (a[i] > baddie)) {
          dif++;
          baddie = (student&&) bad;
          bad = (student&&) a[i];
        }
        else {
          flag = 2;
          baddie = (student&&) bad;
          a[i-dif] = (student&&) a[i];
        }
        break;
    }
  }
  a[i-dif] = (student&&) a[i];
  a[i-dif+1] = (student&&) a[i+1];
  return n-dif;
}

int solve5(student *a , int n) {
  int i, flag = 0, dif = 0;
  student bad;
  if (n < 2) return n;
  for (i = 1; i < n; i++) {
    if ((flag == 0) && (a[i] < a[i-1-dif])){
      flag = 1;
      dif+=2;
      bad = (student&&) a[i];
    }
    else if ((flag == 1) && (a[i] < bad)){
      dif++;
      bad = (student&&) a[i];
    }
    else {
      a[i-dif] = (student&&) a[i];
      flag = 0;
    }
  }
  return n-dif;
}

int solve6(student *a , int n, student& x) {
  int i, dif = 0;
  for (i = 0; i < n; i++) {
    if (a[i] < x){
      dif++;
    }
    else {
      a[i-dif] = (student&&) a[i];
    }
  }
  return n - dif;
}

int solve7(student *a , int n, student& x) {
  int i, dif = 0, flag = 0;
  for (i = 0; i < n; i++) {
    if ((flag == 0) && (a[i] < x)){
      flag = 1;
      a[i-dif] = (student&&) a[i];
    }
    else if (a[i] < x) {
      dif++;
    }
    else {
      flag = 0;
      a[i-dif] = (student&&) a[i];
    }
  }
  return n - dif;
}

int solve8(student *a , int n, student& x) {
  int i, j = 0, flag = 0, res;
  for (i = 0; i < n; i++) {
    res = a[i] > x ? 1 : 0;
    if (res == 1 && flag == 0) {
      flag = 1;
      a[j] = (student&&)a[i];
      if (j < n-1) j++;
    }
    else if (res == 1) {
      a[j] = (student&&)a[i];
    }
    else if (flag == 0){
      a[j] = (student&&)a[i];
      if (j < n-1) j++;
    }
    else {
      flag = 0;
      a[j] = (student&&)a[i];
      if (j < n-1) j++;
    }
  }
  return j+1;
}

int solve9(student *a , int n, student& x) {
  int i = 0, flag = 0, dif = 0;
  student bad;
  if (n < 2) return n;
  if (a[1] < x){
      flag = 1;
      dif++;
      bad = (student&&) a[i];
  }
  else {
      a[i-dif] = (student&&) a[i];
      flag = 0;
  }
  for (i = 1; i < n-1; i++) {
    if ((flag == 0) && ((a[i+1] < x) || (a[i-1-dif] < x))){
      flag = 1;
      dif++;
      bad = (student&&) a[i];
    }
    else if ((flag == 1) && ((a[i+1] < x) || (bad < x))){
      dif++;
      bad = (student&&) a[i];
    }
    else {
      a[i-dif] = (student&&) a[i];
      flag = 0;
    }
  }
    if ((flag == 0) && ((a[i-1-dif] < x))){
      flag = 1;
      dif++;
      bad = (student&&) a[i];
    }
    else if ((flag == 1) && ((bad < x))){
      dif++;
      bad = (student&&) a[i];
    }
    else {
      a[i-dif] = (student&&) a[i];
      flag = 0;
    }
  return n-dif;
}


int solve10(student *a , int n, student& x) {
  int i, flag = 0, dif = 0;
  student bad;
  if (n < 2) return n;
  for (i = 1; i < n; i++) {
    if ((a[i] < x) && (flag == 0) && (a[i] > a[i-1-dif])){
      flag = 1;
      dif+=2;
      bad = (student&&) a[i];
    }
    else if ((a[i] < x) && (flag == 1) && (a[i] > bad)){
      dif++;
      bad = (student&&) a[i];
    }
    else {
      a[i-dif] = (student&&) a[i];
      flag = 0;
    }
  }
  return n-dif;
}


