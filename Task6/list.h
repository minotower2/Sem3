#ifndef LIST
#define LIST
#include "list_node.h"
#include "student.h"

class list 
{
private:
  list_node *head = nullptr;
public:
  list() = default;
  list(const list& x) = delete;
  list(const list&& x) = delete;
  ~list() {
    delete_list();
  }
  list& operator= (const list& x) = delete;
  list& operator== (const list& x) = delete;
  void print_list(int r = 10) {
    const list_node *curr;
    int count;
    for (curr = head, count = 0; count < r && curr; curr=curr->get_next(), count++) {
      curr->print();
    }
  }

  io_status read_list (FILE* fp = stdin) {
    list_node buf;
    io_status res;
    list_node *curr, *tail;
    res = buf.read(fp);
    if (res != io_status::success) {
      if (feof(fp)) {head = nullptr; return io_status::success;}
      else {return res;}
    }
    head = new list_node;
    if (head == nullptr) return io_status::memory;
    *head = (list_node&&) buf;
    curr = head;
    tail = curr;
    while(buf.read(fp) == io_status::success) {
      tail = new list_node;
      if (tail == nullptr) {
        delete_list();
        return io_status::memory;
      }
      *tail = (list_node&&) buf;
      curr -> set_next(tail);
      curr = tail;
    }
    if (!feof(fp)) {
      delete_list();
      return io_status::read;
    }
    return io_status::success;
  }
  int diff() {
    int res = 0;
    list_node *curr;
    for (curr = head; curr->next; curr = curr->next) {
      if (*curr > *curr->next) res++;
    }
    return res;
  }
private:
  void delete_list() {
    list_node *curr, *next;
    for (curr = head; curr; curr = next) {
      next = curr->get_next();
      delete curr;
    }
  }
public:
  void bubble();
  void minimum();
  list_node* prev_min();
  void insertion();
  void neuman();
  void quick();
};
#endif
