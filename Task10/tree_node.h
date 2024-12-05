#ifndef TREENODE
#define TREENODE
#include "student.h"
template <class T> class tree;

template <class T>
class tree_node : public T {
private:
  tree_node * left = nullptr;
  tree_node * right = nullptr;
public:
  tree_node () = default;
  tree_node (const tree_node& x) = delete;
  tree_node (tree_node&& x) : T ((T&&)x) {
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
    (T&&) *this = (T&&) x;
    erase_links ();
    x.erase_links ();
    return *this;
  }
  friend class tree <T>;
private:
  void erase_links () { left = nullptr; right = nullptr; }
};
#endif
