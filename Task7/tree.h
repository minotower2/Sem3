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
    delete_subtree (curr->left);
    delete_subtree (curr->right);
    delete curr;
  }
  static void print_subtree (tree_node * curr, int level, int r, FILE *fp = stdout) {
    if (curr == nullptr || level > r) return;
    int spaces = level * 2;
    for (int i = 0; i < spaces; i++) printf (" ");
    curr->print (fp);
    print_subtree (curr->left, level + 1, r, fp);
    print_subtree (curr->right, level + 1, r, fp);
  }
  static void add_node_subtree (tree_node * curr, tree_node *x) {
    if (*x < *curr) {
      if (curr->left == nullptr) curr->left = x;
      else add_node_subtree(curr->left, x);
    }
    else {
      if (curr->right == nullptr) curr->right = x;
      else add_node_subtree(curr->right, x);
    }
  }
public:
  int solve1(tree_node *curr);
  int solve2(tree_node *curr);
  int solve3(tree_node *curr);
  int solve3_recc(tree_node *curr, int, int);
  int solve4(tree_node *curr);
  void update_max(tree_node *curr, int *max);
  int calc_diff(tree_node *curr);
  int solve5(tree_node *curr);
public:
  tree_node * get_root() {return root;}
};
#endif
