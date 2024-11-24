#ifndef LIST2
#define LIST2
#include "list_node.h"
#include "student.h"

class list2 
{
private:
  list2_node *head = nullptr;
  list2_node *tail = nullptr;
public:
  list2() = default;
  list2(const list2& x) = delete;
  list2(const list2&& x) = delete;
  ~list2() {
    delete_list();
  }
  list2& operator= (const list2& x) = delete;
  list2& operator== (const list2& x) = delete;
  void print_list(int r = 10) {
    const list2_node *curr;
    int count;
    for (curr = head, count = 0; count < r && curr; curr=curr->get_next(), count++) {
      curr->print();
    }
  }

  io_status read_list (FILE* fp = stdin) {
    list2_node buf;
    io_status res;
    list2_node *curr;
    res = buf.read(fp);
    if (res != io_status::success) {
      if (feof(fp)) {head = nullptr; return io_status::success;}
      else {return res;}
    }
    head = new list2_node;
    if (head == nullptr) return io_status::memory;
    *head = (list2_node&&) buf;
    curr = head;
    tail = curr;
    while(buf.read(fp) == io_status::success) {
      tail = new list2_node;
      if (tail == nullptr) {
        delete_list();
        return io_status::memory;
      }
      *tail = (list2_node&&) buf;
      curr -> set_next(tail);
      curr = tail;
    }
    if (!feof(fp)) {
      delete_list();
      return io_status::read;
    }
    if (head) { 
      tail = head;
      for (curr = head->get_next(); curr; curr = curr->get_next()) {
        curr->set_prev(tail);
        tail = curr;
      }
    } 
    return io_status::success;
  }
  unsigned int get_length() {
    unsigned int res = 0;
    list2_node *curr;
    for (curr = head; curr; curr=curr->get_next()) {
      res++;
    }
    return res;
  }
private:
  void delete_list() {
    list2_node *curr, *next;
    for (curr = head; curr; curr = next) {
      next = curr->get_next();
      delete curr;
    }
  }
  void delete_node(list2_node *curr) {
    list2_node *pr, *nx;
    if (curr) {
      pr = curr->prev;
      nx = curr->next;
      if (pr && nx) {
        pr->next = nx;
        nx->prev = pr;
        delete curr;
        return;
      }
    }
  }
  void delete_head() {
    list2_node *nx;
    if (head) {
      nx = head->next;
      if (nx) {
        nx->prev = nullptr;
        delete head;
        head = nx;
      }
    }
  }
  void delete_tail() {
    list2_node *pr;
    if (tail) {
      pr = tail->prev;
      if (pr) {
        pr->next = nullptr;
        delete tail;
        tail = pr;
      }
    }
  }
public:
  void solve1(int k);
  void solve2(int k);
  void solve3(int k);
  void solve4(int k);
  void solve5(int k);
  void solve6(int k);
  void solve7(int k);
  void solve8(int k);
};
#endif
