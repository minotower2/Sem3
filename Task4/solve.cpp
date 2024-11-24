#include "solve.h"
#include "list_node.h"

int solve1(list_node *head) {
  list_node *curr, *max = head;
  int count = 0;
  for (curr = head; curr; curr = curr->get_next()) {
    if (*curr > *max) {
      count = 1;
      max = curr;
    }
    else if (*curr == *max){
      count++;
    }
  }
  return count;
}

int solve2(list_node *head) {
  list_node *curr = head ? head->get_next() : nullptr, *prev = head;
  int count = 0;
  for (; curr; curr = curr->get_next()) {
    if (*curr > *prev) {
      count++;
    }
    prev = curr;
  }
  return count;
}

int solve3(list_node *head) {
  list_node *curr = head ? head->get_next() : nullptr, *prev = head;
  int count = 0;
  for (; curr; curr = curr->get_next()) {
    if (curr->get_next()) {
      if (*curr > *prev && *curr > *(curr->get_next())) {
        count++;
      }
    }
    prev = curr;
  }
  return count;
}


int solve4(list_node *head) {
  list_node *curr = head ? head->get_next() : nullptr, *prev = head;
  if (!curr) return 4;
  int type = -1, res = -2;
  if(*curr > *prev) {
    type = 1;
  }
  else if(*curr < *prev) {
    type = 2;
  }
  else if(*curr == *prev) {
    type = 3;
  }

  for (; curr; curr = curr->get_next()) {
    if(*curr > *prev) {
      res = 1;
    }
    else if(*curr < *prev) {
      res = 2;
    }
    else if(*curr == *prev) {
      res = 3;
    }
    if (res != type) {
      return 0;
    }
    prev = curr;
  }
  return type;
}

int solve5(list_node *head) {
  list_node *curr = head ? head->get_next() : nullptr, *prev = head;
  int count = 0, flag = 0, max = 0;
  for (; curr; curr = curr->get_next()) {
      if (flag == 0 && *curr > *prev) {
        flag = 1;
        count = 2;
      }
      else if (flag == 1 && *curr > *prev) {
        count++;
      }
      else if (flag == 1) {
        flag = 0;
        if (count > max) max = count;
      }
    prev = curr;
  }
  return max;
}

int solve6(list_node *head) {
  list_node *curr = head ? head->get_next() : nullptr, *prev = head;
  int count = 0, flag = 0;
  for (; curr; curr = curr->get_next()) {
    if (flag == 0 && *curr == *prev) {
      flag = 1;
      count++;
    }
    else if (flag == 1 && !(*curr == *prev)) {
      flag = 0;
    }
    prev = curr;
  }
  return count;
}

// flag -1 = default flag 1 = constant flag 0 = between constants
int solve7(list_node *head) {
  list_node *curr = head ? head->get_next() : nullptr, *prev = head;
  int count = 0, flag = -1, max = 0;
  for (; curr; curr = curr->get_next()) {
    if (flag == -1 && *curr == *prev) {
      flag = 1;
    }
    else if (flag == 1 && !(*curr == *prev)) {
      flag = 0;
    }
    else if (flag == 0 && !(*curr == *prev)) {
      count++;
    }
    else if (flag == 0 && *curr == *prev) {
      flag = 1;
      if (count > max) max = count;
      count = 0;
    }
    prev = curr;
  }
  return max;
}


//flag 0 = default flag 1 = increasing flag 2 = decreasing
int solve8(list_node *head) {
  list_node *curr = head ? head->get_next() : nullptr, *prev = head;
  int count = 0, max = 0, flag = 0;
  for (; curr; curr = curr->get_next()) {
    if (flag == 0 && (*curr > *prev || *curr == *prev)) {
      flag = 1;
      count = 2;
    }
    else if (flag == 1 && (*curr > *prev || *curr == *prev)) {
      count++;
    }
    else if (flag == 0 && (*curr < *prev || *curr == *prev)) {
      flag = 2;
      count = 1;
    }
    else if (flag == 2 && (*curr < *prev || *curr == *prev)) {
      count++;
    }
    else {
      flag = 0;
      if (count > max) max = count;
    }
    prev = curr;
  }
  if (count > max) max = count;
  return max;
}


