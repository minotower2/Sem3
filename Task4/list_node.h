#ifndef LISTNODE
#define LISTNODE
#include "student.h"

class list_node: public student
{
private:
  list_node *next = nullptr;
public:
  list_node() = default;
  list_node(const list_node& x) = delete;
  list_node(list_node&& x){
    next = x.next; x.next = nullptr;
  }
  ~list_node() {
    next = nullptr;
  }
  list_node& operator=(const list_node& x) = delete;
  list_node& operator=(list_node&& x) {
    *(student*)this = (student&&) x;
    next = x.next; x.next = nullptr;
    return *this;
  }
  list_node *get_next() const {return next;}
  void set_next(list_node *x) {next = x;}
};
#endif
