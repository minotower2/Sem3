#include "list2.h"
#include "list_node.h"

void list2::solve1(int k) {
  if (!head) return;
  if (!head->next) return;
  int len = get_length();
  int m = k % len;
  int count;
  list2_node *newhead = head, *newtail;
  if (m == 0) return;
  m = len - m;
  for (count = 0; count < m; count++) {
    if (newhead->next) newhead = newhead->next;
    else newhead = head;
  }
  newtail = newhead->prev;
  newtail->next = nullptr;
  newhead->prev = nullptr;
  head->prev = tail;
  tail->next = head;
  head = newhead;
  tail = newtail;
}

void list2::solve2(int k) {
  if (!head) return;
  if (k<= 0) return;
  list2_node *curr, *pr, *nx;
  int i, flag;
  for (curr = tail; curr; curr = nx) { 
    nx = curr->prev;
    flag = 0;
    pr = curr;
    for (i = 0; i < k; i++) {
      if (pr->prev) {
        pr = pr->prev;
        if (*curr > *pr) {
          flag = 1;
          break;
        }
      }
    }
    if (flag == 1) {
      if (!curr->prev) delete_head();
      else if (!curr->next) delete_tail();
      else delete_node(curr);
    }
  }
}

void list2::solve3(int k) {
  if (!head) return;
  if (k<= 0) return;
  list2_node *curr, *pr, *nx;
  int i, flag;
  for (curr = head; curr; curr = nx) { 
    nx = curr->next;
    flag = 0;
    pr = curr;
    for (i = 0; i < k; i++) {
      if (pr->next) {
        pr = pr->next;
        if (*curr > *pr) {
          flag = 1;
          break;
        }
      }
    }
    if (flag == 1) {
      if (!curr->prev) delete_head();
      else if (!curr->next) delete_tail();
      else delete_node(curr);
    }
  }
}

void list2::solve4(int k) {
  (void) k;
//  Мама собирает сыну обед в школу:
//— Вот, положила тебе в ранец хлеб, колбасу и гвозди.
//— Мам, нафига??
//— Ну как же, берешь хлеб, кладешь на него колбасу и ешь.
//— А гвозди?
//— Так вот же они! 
}

void list2::solve5(int k) {
  if (!head) return;
  if (!head->next) return;
  if (k <= 0) return;
  list2_node *curr, *start = head, *nx, *temp, *tempnx;
  int i, flag = 0, count = 0;
  for (curr = head, nx = head->next; nx; curr = nx, nx = curr->next) {
    if (flag == 0 && *curr == *nx) {
      count = 1;
      start = curr;
      flag = 1;
    }
    else if (flag == 1 && *curr == *nx) {
      count++;
    }
    else if (flag == 1){
      flag = 0;
      if (count > k) {
        for (temp = start, i = 0; temp && i <= count; temp = tempnx, i++) {
          tempnx = temp->next;
          if (!temp->prev) delete_head();
          else if (!temp->next) delete_tail();
          else delete_node(temp);
        }
      }
    }
  }
  if (flag == 1 && count > k) {
    for (temp = start, i = 0; temp && i <= count; temp = tempnx, i++) {
      tempnx = temp->next;
      if (!temp->prev) delete_head();
      else if (!temp->next) delete_tail();
      else delete_node(temp);
    }
  }
}

void list2::solve6(int k) {
  if (!head) return;
  if (!head->next) return;
  if (k <= 0) return;
  list2_node *curr, *start = head, *nx, *temp, *tempnx;
  int i, flag = 0, count = 0;
  for (curr = head, nx = head->next; nx; curr = nx, nx = curr->next) {
    if (flag == 0 && (*curr == *nx || *curr > *nx)) {
      count = 1;
      start = curr;
      flag = 1;
    }
    else if (flag == 1 && (*curr == *nx || *curr > *nx)) {
      count++;
    }
    else if (flag == 1){
      flag = 0;
      if (count > k) {
        for (temp = start, i = 0; temp && i <= count; temp = tempnx, i++) {
          tempnx = temp->next;
          if (!temp->prev) delete_head();
          else if (!temp->next) delete_tail();
          else delete_node(temp);
        }
      }
    }
  }
  if (flag == 1 && count > k) {
    for (temp = start, i = 0; temp && i <= count; temp = tempnx, i++) {
      tempnx = temp->next;
      if (!temp->prev) delete_head();
      else if (!temp->next) delete_tail();
      else delete_node(temp);
    }
  }
}

void list2::solve7(int k) {
  if (!head) return;
  if (!head->next) return;
  list2_node *curr, *start= head, *nx = head->next, *temp, *tempnx;
  int i, flag = -1, count = 0, count2 = 0;
  for (curr = head, nx = head->next; nx; curr = nx, nx = curr->next) {
    nx = curr->next;
    if (flag == -1 && *curr == *nx) {
      count = 1;
      flag = 1;
    }
    else if (flag == 1 && *curr == *nx) {
      count++;
    }
    else if (flag == 1){
      count2 = 0;
      flag = 0;
      start = nx;
    }
    else if (flag == 0 && !(*curr == *nx)) {
      count2++;
    }
    else if (flag == 0 && *curr == *nx) {
      if (count > k) {
        for (temp = start, i = 0; temp && i < count2; temp = tempnx, i++) {
          tempnx = temp->next;
          if (!temp->prev) delete_head();
          else if (!temp->next) delete_tail();
          else delete_node(temp);
        }
      }
      count = 1;
      flag = 1;
    }
  }
  if (flag == 1 && count > k) {
    for (temp = start, i = 0; temp && i < count2; temp = tempnx, i++) {
      tempnx = temp->next;
      if (!temp->prev) delete_head();
      else if (!temp->next) delete_tail();
      else delete_node(temp);
    }
  }
}


void list2::solve8(int k) {
  if (!head) return;
  if (!head->next) return;
  list2_node *curr, *start, *nx = head->next, *temp, *tempnx;
  int i, flag = -1, count = 0, count2 = 0;
  for (curr = head, nx = head->next; nx; curr = nx, nx = curr->next) {
    nx = curr->next;
    if (flag == -1 && (*curr == *nx || *curr < *nx)) {
      count = 1;
      flag = 1;
    }
    else if (flag == 1 && (*curr == *nx || *curr < *nx)) {
      count++;
    }
    else if (flag == 1){
      count2 = 0;
      flag = 0;
      start = nx;
    }
    else if (flag == 0 && !(*curr == *nx || *curr < *nx)) {
      count2++;
    }
    else if (flag == 0 && (*curr == *nx || *curr < *nx)) {
      if (count2 > k) {
        for (temp = start, i = 0; temp && i < count2; temp = tempnx, i++) {
          tempnx = temp->next;
          if (!temp->prev) delete_head();
          else if (!temp->next) delete_tail();
          else delete_node(temp);
        }
      }
      count = 1;
      flag = 1;
    }
  }
  if (flag == 1 && count2 > k) {
    for (temp = start, i = 0; temp && i < count2; temp = tempnx, i++) {
      tempnx = temp->next;
      if (!temp->prev) delete_head();
      else if (!temp->next) delete_tail();
      else delete_node(temp);
    }
  }
}


