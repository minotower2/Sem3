#include "tree.h"

//====================
//      Task = 1
//====================

int tree::solve1(int k) {
  int sum = 0;
  sum_over_subtree1(root, k, &sum);
  return sum;
}

int tree::check_node1(tree_node *curr, int k) {
  int i;
  k--;
  tree_node *p = curr;
  if (!curr) return 0;
  for (p = curr->down, i = 0; p && i < k; p = p->level, i++);
  if (i == k && p && !p->level) {return 1;}
  else return 0;
}

void tree::sum_over_subtree1(tree_node *curr, int k, int *sum) {
  if (!curr) return;
  if (check_node1(curr, k) == 1) *sum += 1;
  if (curr->down) sum_over_subtree1(curr->down, k, sum);
  if (curr->level) sum_over_subtree1(curr->level, k, sum);
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
  int flag = 1;
  int num = count_subtree(curr);
  if (num <= k) {
    *count += num;
    flag = 0;
  }
  if (flag == 1) {
    if (curr->down) magic2(curr->down, count, k);
    if (curr->level) magic2(curr->level, count, k);
  }
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
  int flag = 1;
  int num = count_levels(curr, 1);
  if (num <= k) {
    *count += count_subtree(curr);
    flag = 0;
  }
  if (flag == 1) {
    if (curr->down) magic3(curr->down, count, k);
    if (curr->level) magic3(curr->level, count, k);
  }
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

//====================
//      Task = 4
//====================

int tree::solve4(int k) {
  int count = 0;
  magic4(root, &count, k);
  return count;
}

void tree::magic4(tree_node *curr, int *count, int k) {
  if (!curr) return;
  int res = 1;
  count_on_levels(curr, k, &res);
  if (res == 1) {
    *count += count_subtree(curr);
  }
  if (res != 1) {
    if (curr->down) magic4(curr->down, count, k);
    if (curr->level) magic4(curr->level, count, k);
  }
}

void tree::count_on_levels(tree_node *curr, int k, int *res) {
  if (!curr) return;
  tree_node *p;
  int c = 0;
  for (p = curr->down; p; p = p->level) {c++; count_on_levels(p, k, res);}
  if (c > k) *res = -1;
}

//====================
//      Task = 5
//====================

int tree::solve5(int k) {
  int count = 0;
  nodes_on_level(root, 0, k, &count);
  return count;
}

void tree::nodes_on_level(tree_node *curr, int level, int goal, int *count) {
  if (level == goal) (*count)++;
  if (!curr || level > goal) return;
  if (curr->down) nodes_on_level(curr->down, level+1, goal, count);
  if (curr->level) nodes_on_level(curr->level, level, goal, count);
}

//====================
//      Task = 6
//====================

int tree::solve6(int k) {
  int count = 0;
  magic6(root, &count, k);
  return count;
}

void tree::magic6(tree_node *curr, int *count, int k) {
  if (!curr) return;
  int num = count_levels(curr, 1);
  if (num >= k) {
    for (int j = k; j <= num; j++) {
      int c = 0;
      ends_on_level(curr, 1, j, &c);
      *count += c*j;
    }
  }
  if (curr->down) magic6(curr->down, count, k);
  if (curr->level) magic6(curr->level, count, k);
}


void tree::ends_on_level(tree_node *curr, int level, int goal, int *count) {
  if (level == goal && !curr->down) (*count)++;
  if (!curr || level > goal) return;
  if (curr->down) ends_on_level(curr->down, level+1, goal, count);
  if (curr->level) ends_on_level(curr->level, level, goal, count);
}
