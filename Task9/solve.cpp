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

//====================
//      Task = 2
//====================


int tree::solve2(int k) {
  int count = 0;
  magic2(root, &count, k);
  return count;
}

int tree::count_subtree(tree_node *curr) {
  if (!curr) return 0;
  if (!curr->down) return 1;
  int d_count = 0, l_count = 0;
  if (curr->down) {
    tree_node *p = curr->down;
    d_count = count_subtree(p);
    for (p = p->level; p && p->level; p = p->level) l_count++;
    l_count += count_subtree(p);
  }
  return d_count + l_count + 1;
}

void tree::magic2(tree_node *curr, int *count, int k) {
  if (!curr) return;
  int num = count_subtree(curr);
  if (num <= k) {
    *count += num;
  }
  if (curr->down) magic2(curr->down, count, k);
  if (curr->level) magic2(curr->level, count, k);
}

//====================
//      Task = 3
//====================

int tree::solve3(int k) {
  int count = 0;
  magic3(root, &count, k);
  return count;
}

void tree::magic3(tree_node *curr, int *count, int k) {
  if (!curr) return;
  int num = count_levels(curr, 1);
  if (num <= k) {
    *count += count_subtree(curr);
  }
  if (curr->down) magic3(curr->down, count, k);
  if (curr->level) magic3(curr->level, count, k);
}

int tree::count_levels(tree_node *curr, int level) {
  int l = 0, d = 0;
  if (!curr->down && !curr->level) return level;
  else {
    if (curr->level) l = count_levels(curr->level, level);
    if (curr->down) d = count_levels(curr->down, level+1);
    return l > d ? l : d;
  }
}
