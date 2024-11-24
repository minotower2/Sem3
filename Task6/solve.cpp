#include "list.h"

void list::bubble() {
  list_node *curr, *nxt, *nxtnxt, *nxtnxtnxt, *newhead = nullptr, *currhead;
  if (!head) return;
  if (!head->next) return;
  while(head->next) {
    nxt = head->next;
    if (*head < *nxt) {
      head->next = nxt->next;
      nxt->next = head;
      head = nxt;
    }
    for (curr = head; (curr->next)->next; curr = curr->next) {
      nxt = curr->next;
      nxtnxt = nxt->next;
      nxtnxtnxt = nxtnxt->next;
      if (*nxt < *nxtnxt) {
        curr->next = nxtnxt;
        nxtnxt->next = nxt;
        nxt->next = nxtnxtnxt;
      }
    }
    if (!newhead) {
      newhead = curr->next;
      currhead = newhead;
    }
    else {
      currhead->next = curr->next;
      currhead = currhead->next;
    }
    curr->next = nullptr;
  }
  currhead->next = head;
  head = newhead;
}

list_node* list::prev_min() {
  list_node *curr = nullptr, *min = head;
  for (curr = head; curr->next; curr = curr->next) {
    if (*(curr->next) < *min->next) {
      min = curr;
    }
  }
  if (*head < *(min->next)) return nullptr;
  return min;
}

void list::minimum() {
  list_node *newhead = nullptr, *currhead, *prevmin, *min; if (!head) return;
  if (!head->next) return;
  while(head->next) {
    prevmin = prev_min();
    if (!prevmin) {
      min = head;
      if (!newhead) {
        newhead = min;
        currhead = newhead;
      }
      else {
        currhead->next = min;
        currhead = currhead->next;
      }
      prevmin = head->next;
      head = prevmin;
    }
    else {
      min = prevmin->next;
      if (!newhead) {
        newhead = min;
        currhead = newhead;
      }
      else {
        currhead->next = min;
        currhead = currhead->next;
      }
      prevmin->next = min->next;
    }
  }
  currhead->next = head;
  head = newhead;
}

void list::insertion() {
  list_node *newhead = head, *dum = nullptr, *cur = nullptr;
  int flag = -1;
  if (!head) return;
  if (!head->next) return;
  dum = head->next;
  head = dum;
  newhead->next = nullptr;
  while(head) {
    dum = head;
    head = head->next;
    dum->next = nullptr;
    if (*dum < *newhead) {
      dum->next = newhead;
      newhead = dum;
    }
    else {
      if (!newhead->next) {
        newhead->next = dum;
      }
      else {
        flag = 0;
        for (cur = newhead; cur->next; cur = cur->next) {
          if (*dum < *cur->next) {
            flag = 1;
            dum->next = cur->next;
            cur->next = dum;
            break;
          }
        }
        if (flag == 0) {
          cur->next = dum;
        }
      }
    }
  }
  head = newhead;
}

/*
void list::quick() {
  list_node *l = nullptr, *u = nullptr, *m, *t, *lcurr, *ucurr, *mcurr, *dum, *newhead, *newcurr;
  int count_u, count_l;
  if (!head) return;
  if (!head->next) return;
  for (m = head; t; m = m->next, t = (t->next)->next) {}
  dum = m->next;
  m->next = dum->next;
  m = dum;
  m->next = nullptr;
  for (t = head; t; t = t->next) {
    count_u = 0; count_l = 0;
    if (*t < *m) {
      count_l++;
      if (!l) {
        l = t; 
        lcurr = l;
      }
      else {
        lcurr->next = t;
        lcurr = lcurr->next;
      }
    }
    else if (*t > *m) {
      count_u++;
      if (!u) {
        u = t; 
        ucurr = l;
      }
      else {
        ucurr->next = t;
        ucurr = ucurr->next;
      }
    }
    else {
      if (!m->next) {
        m->next = t;
        mcurr = m->next;
      }
      else {
        mcurr->next = t;
        mcurr = mcurr->next;
      }
    }
  }
  if(count_l < count_u) {
    head = l;
    quick();
    lcurr->next = m;
  }
}

*/
