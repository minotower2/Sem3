#ifndef TREE 
#define TREE
#include "tree_node.h"

class tree {
private:
  tree_node * root = nullptr;
public:
  tree () = default;
  tree (const tree& x) = delete;
  tree (tree&& x) {
    root = x.root; x.root = nullptr;
  }
  ~tree () {
    delete_subtree (root);
    root = nullptr;
  }
  tree& operator= (const tree& x) = delete;
  tree& operator= (tree&& x) {
    if (this == &x) return *this;
    delete_subtree (root);
    root = x.root; x.root = nullptr;
    return *this;
  }
  void print (int r) const {
    print_subtree (root, 0, r);
  }
  io_status read (FILE * fp = stdin, unsigned int max_read = -1) {
    tree_node x; unsigned int count = 0;
    while(x.read(fp) == io_status::success && count < max_read) {
      tree_node *curr = new tree_node ();
      *curr = (tree_node&&) x;
      if (curr == nullptr) {
        delete_subtree(root);
        return io_status::memory;
      }
      if (root == nullptr) root = curr;
      else add_node_subtree(root, curr);
      if (count == max_read) return io_status::success;
    }
    if (!feof(fp)) return io_status::eof;
    return io_status::success;
  }
private:
  static void delete_subtree (tree_node * curr) {
    if (curr == nullptr) return;
    tree_node * p, * next;
    for (p = curr->down; p; p = next) {
      next = p->level;
      delete_subtree (p);
    }
    delete curr;
  }
  static void print_subtree (tree_node * curr, int level, int r) {
    if (curr == nullptr || level > r) return;
    int spaces = level * 2;
    for (int i = 0; i < spaces; i++) printf (" ");
    curr->print ();
    for (tree_node * p = curr->down; p; p = p->level) print_subtree (p, level + 1, r);
  }
  static void add_node_subtree (tree_node* curr, tree_node* x) {
    if (curr->down == nullptr) { // No any child node
      curr->down = x;
      return;
    }
    if (*x < *curr) {
      if (*curr->down < *curr) // head of the list of child nodes < *curr
        add_node_subtree (curr->down, x);
      else {
        x->level = curr->down;
        curr->down = x;
      }
    }
    else if (*x == *curr) {
      if (curr->down->level != nullptr) {
        x->level = curr->down->level;
        curr->down->level = x;
      }
      else if (*curr->down < *curr) {
        curr->down->level = x;
      }
      else {
        x->level = curr->down;
        curr->down = x;
      }
    }
    else { // *x > *curr 
      tree_node * p;
      for (p = curr->down; p->level; p = p->level);
      if (*p > *curr) // tail of the list of child nodes > *curr
        add_node_subtree (p, x);
      else
        p->level = x; // append at end of the list
    }
  }
public:
  int solve1(int k);
  int solve2(int k);
  int solve3(int k);
  int solve4(int k);
  int solve5(int k);
  int solve6(int k);
private:
  //task 1
  int check_node1(tree_node *curr, int k);
  int sum_over_subtree1(tree_node *curr, int k);
  //task 2
  int count_subtree(tree_node *curr);
  void magic2(tree_node *curr, int *count, int k);
};
#endif
