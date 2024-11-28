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
  void swap_tree_nodes(tree_node * first, tree_node * second) {
    student temp;
    if (!first || !second) return;
    if (first == second) return;
    temp = (student&&) *first;
    (student&&) *first = (student&&) *second;
    (student&&) *second = (student&&) temp;
  }
public:
  int get_count_leaf(tree_node *curr) const;
  int get_height(tree_node *curr) const;
  int get_width(tree_node *curr) const;
  int get_balance(tree_node *curr) const;
  int get_count_1(tree_node *curr) const;
  int get_count_total(tree_node *curr) const;
  int get_count_2(tree_node *curr) const;
private:
  int solve3_recc(tree_node *curr, int, int) const;
  void update_max(tree_node *curr, int *max) const;
  int calc_diff(tree_node *curr) const;
public:
  tree_node * get_root() {return root;}
public:
  void solve1(tree_node *curr);
  void solve2(int h);
  void solve3(tree_node *curr, tree_node *prev);
  void solve4(tree_node *curr, tree_node *prev);
  void solve5(const student& x);
  void solve6(const student& x);
  void solve7(int h, const student& x);
private:
  tree_node * find_max_subtree(tree_node *curr);
  void magic5(tree_node *curr, char * s, int k);
  void magic6(tree_node *curr, char * s, int k);
  int check_subtree(tree_node * curr, char * s, int k);
  int get_height_mod(tree_node *curr, char * s, int* res);
  tree_node * get_to_ith(tree_node *curr, int level, int goalh, int goalw, int* i);
  void nodes_on_level(tree_node* curr, int level, int goal, int *i);
  int cmp_val(tree_node *first, tree_node *second);
  void magic7(char * s, int k, int h);
  void nodes_on_level_mod(tree_node* curr, int level, int goal, int *i, char *s, int *res);
  void check_level(tree_node *curr, int level, int goal, int *res, int *i, int start, int end, char* s);
  void delete_level(tree_node* curr, int level, int goal);
  void find_min(tree_node *curr, int level, int goal, int *i, int left, int right, tree_node **min);
};
#endif
