#ifndef TREE
#define TREE
#include "tree_node.h"

template <class T>
class tree {
private:
  tree_node<T> * root = nullptr;
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
    if (this == &x)
      return *this;
    delete_subtree (root);
    root = x.root; x.root = nullptr;
    return *this;
  }
  void print (unsigned int r = 10, FILE *fp = stdout) const {
    print_subtree (root, 0, r, fp);
  }
  io_status read (FILE * fp = stdin, unsigned int max_read = -1) {
    tree_node<T> x; unsigned int count = 0;
    while(x.read(fp) == io_status::success && count < max_read) {
      tree_node<T> *curr = new tree_node<T> ();
      *curr = (tree_node<T>&&) x;
      if (curr == nullptr) {
        delete_subtree(root);
        return io_status::memory;
      }
      if (root == nullptr) root = curr;
      else add_node_subtree(root, curr);
      count++;
      if (count == max_read) return io_status::success;
    }
    if (!feof(fp)) return io_status::eof;
    return io_status::success;
  }
private:
  static void delete_subtree (tree_node<T> * curr) {
    if (curr == nullptr) return;
    delete_subtree (curr->left);
    delete_subtree (curr->right);
    delete curr;
  }
  static void print_subtree (tree_node<T> * curr, int level, int r, FILE *fp = stdout) {
    if (curr == nullptr || level > r) return;
    int spaces = level * 2;
    curr->print (fp, spaces);
    print_subtree (curr->left, level + 1, r, fp);
    print_subtree (curr->right, level + 1, r, fp);
  }
  static void add_node_subtree (tree_node<T> * curr, tree_node<T> *x) {
    if (*x < *curr) {
      if (curr->left == nullptr) curr->left = x;
      else add_node_subtree(curr->left, x);
    }
    else {
      if (curr->right == nullptr) curr->right = x;
      else add_node_subtree(curr->right, x);
    }
  }
  void swap_tree_nodes(tree_node<T> * first, tree_node<T> * second) {
    student temp;
    if (!first || !second) return;
    if (first == second) return;
    temp = (student&&) *first;
    (student&&) *first = (student&&) *second;
    (student&&) *second = (student&&) temp;
  }
public:
  tree_node<T> * get_root() {return root;}
public:
  int solve1(tree_node<T> *curr);
  int solve2(tree_node<T> *curr);
  int solve3(tree_node<T> *curr);
  int solve3_recc(tree_node<T> *curr, int, int);
  int solve4(tree_node<T> *curr);
  void update_max(tree_node<T> *curr, int *max);
  int calc_diff(tree_node<T> *curr);
  int solve5(tree_node<T> *curr);
};
#endif
