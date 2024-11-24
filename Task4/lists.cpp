#include "list_node.h"
#include "student.h"
#include "lists.h"
#include <stdio.h>

void delete_list(list_node *head) {
  list_node *curr, *next;
  for (curr = head; curr; curr = next) {
    next = curr->get_next();
    delete curr;
  }
}

void print_list (const list_node *head, int r) {
  const list_node *curr;
  int count = 0;
  if (r < 1) return;
  for (curr = head; curr; curr = curr->get_next()) {
    curr->print();
    count++;
    if (count == r) {
      break;
    }
  }
}

io_status read_list (FILE* fp, list_node **head) {
  list_node buf;
  io_status res;
  list_node *curr, *tail;
  res = buf.read(fp);
  if (res != io_status::success) {
    if (feof(fp)) {*head = nullptr; return io_status::success;}
    else {return res;}
  }
  *head = new list_node;
  if (*head == nullptr) return io_status::memory;
  **head = (list_node&&) buf;
  curr = *head;
  tail = curr;
  while(buf.read(fp) == io_status::success) {
    tail = new list_node;
    if (tail == nullptr) {
      delete_list(*head);
      return io_status::memory;
    }
    *tail = (list_node&&) buf;
    curr -> set_next(tail);
    curr = tail;
  }
  if (!feof(fp)) {
    delete_list(*head);
    return io_status::read;
  }
  return io_status::success;
}
