#include "tree.h"

//====================
//      Task = 1
//====================

int tree::solve1(int k) {
  k--;
  return sum_over_subtree1(root, k);
}

int tree::check_node1(tree_node *curr, int k) {
  int i;
  tree_node *p = curr;
  if (!curr) return 0;
  for (p = curr->down, i = 0; p && i < k; p = p->level, i++);
  if (i == k && p && !p->level) {return 1;}
  else return 0;
}

int tree::sum_over_subtree1(tree_node *curr, int k) {
  tree_node *tail;
  if (!curr) return 0;
  int s_level = 0, s_down = 0, s;
  s = check_node1(curr, k);
  if (curr->down) s_down = sum_over_subtree1(curr->down, k);
  for (tail = curr->level; tail && tail->level; tail = tail->level);
  if (tail) s_level = sum_over_subtree1(tail, k);
  return s_level + s_down + s;
}
