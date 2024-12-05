#ifndef LIST2
#define LIST2
#include "list_node.h"
#include "student.h"

class list2 
{
private:
  list2_node *head = nullptr;
  list2_node *tail = nullptr;
  static int max_print;
  static int max_read;
public:
  list2() = default;
  list2(const list2& x) = delete;
  list2(const list2&& x) = delete;
  ~list2() {
    delete_list();
  }
  list2& operator= (const list2& x) = delete;
  list2& operator= (list2&& x) {
    if (this == &x)
      return *this;
    head = nullptr;
    tail = nullptr;
    head = x.head; x.head = nullptr;
    tail = x.tail; x.tail = nullptr;
    return *this;

  }

  void print(FILE *fp = stdout, int spaces = 0) const{
    const list2_node *curr;
    int count;
    for (curr = head, count = 0; count < max_print && curr; curr=curr->get_next(), count++) {
      curr->print(fp, spaces);
    }
  }

  io_status read (FILE* fp = stdin) {
    list2_node buf;
    io_status res;
    list2_node *curr;
    res = buf.read(fp);
    if (res != io_status::success) {
      return res;
    }
    head = new list2_node;
    if (head == nullptr) return io_status::memory;
    *head = (list2_node&&) buf;
    curr = head;
    tail = curr;
    int i = 2;
    if (max_read >= 2) {
      while(buf.read(fp) == io_status::success) {
        tail = new list2_node;
        if (tail == nullptr) {
          delete_list();
          return io_status::memory;
        }
        *tail = (list2_node&&) buf;
        curr -> set_next(tail);
        curr = tail;
        if (i >= max_read) break;
        i++;
      }
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
  int get_length() const {
    int res = 0;
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
      if (curr) delete curr;
    }
  }
public:
  static void set_max_print (int m) {list2::max_print = m;}
  static void set_max_read (int r) {list2::max_read = r;}
  int operator< (const list2& b) const {
    if (head == nullptr) {
      if (b.head == nullptr) return 0;
      else return 1;
    }
    else {
      return (*head < *(b.head));
    }
  }
};
#endif
