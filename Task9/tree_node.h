#ifndef TREENODE
#define TREENODE
#include "student.h"
class tree;
class tree_node : public student {
private:
  tree_node * down = nullptr;
  tree_node * level = nullptr;
public:
  tree_node () = default;
  tree_node (const tree_node& x) = delete;
  tree_node (tree_node&& x) : student ((student&&)x) {
    erase_links ();
    x.erase_links ();
  }
  ~tree_node () {
    erase_links ();
  }
  tree_node& operator= (const tree_node& x) = delete;
  tree_node& operator= (tree_node&& x) {
    if (this == &x)
      return *this;
    (student&&) *this = (student&&) x;
    erase_links ();
    x.erase_links ();
    return *this;
  }
  friend class tree;
private:
  void erase_links () { down = nullptr; level = nullptr; }
};
#endif
