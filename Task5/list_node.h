#ifndef LISTNODE
#define LISTNODE
#include "student.h"
class list2;
class list2_node: public student
{
  friend class list2;
private:
  list2_node *next = nullptr;
  list2_node *prev = nullptr;
public:
  list2_node() = default;
  list2_node(const list2_node& x) = delete;
  list2_node(list2_node&& x){
    next = x.next; x.next = nullptr;
    prev = x.prev; x.prev = nullptr;
  }
  ~list2_node() {
    next = nullptr;
    prev = nullptr;
  }
  list2_node& operator=(const list2_node& x) = delete;
  list2_node& operator=(list2_node&& x) {
    *(student*)this = (student&&) x;
    next = x.next; x.next = nullptr;
    prev = x.prev; x.prev = nullptr;
    return *this;
  }
  list2_node *get_next() const {return next;}
  list2_node *get_prev() const {return prev;}
  void set_next(list2_node *x) {next = x;}
  void set_prev(list2_node *x) {prev = x;}
};
#endif
