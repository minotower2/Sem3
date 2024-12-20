#include "tree.h"

int tree::solve1(tree_node * curr) {
  if (!curr) return 0;
  if (!curr->left && !curr->right) return 1;
  else if (!curr->left) return solve1(curr->right);
  else if (!curr->right) return solve1(curr->left);
  else return solve1(curr->right) + solve1(curr->left);
}

int tree::solve2(tree_node * curr) {
  int count = 1, left, right;
  if (!curr) return 0;
  if (curr->left && !curr->right) {
    count += solve2(curr->left);
  }
  else if (curr->right && !curr->left) {
    count += solve2(curr->right);
  }
  else if (curr->left && curr->right) {
    left = solve2(curr->left);
    right = solve2(curr->right);
    count += left < right ? right : left;
  }
  return count;
}
int tree::solve3(tree_node *curr) {
  int max = 0, n, level;
  for(level = 0; (n = solve3_recc(curr, level, 0)); level++) {
    if(max < n) max = n;
  }
  return max;
}

int tree::solve3_recc(tree_node * curr, int level, int curr_level) {
  if(curr == nullptr) return 0;
  if(level == curr_level) return 1;
  return solve3_recc(curr -> right, level, curr_level + 1) + solve3_recc(curr -> left, level, curr_level + 1);
}

int tree::solve4(tree_node *curr) {
  int max = 0;
  if (curr) update_max(curr, &max);
  return max;
}

void tree::update_max(tree_node *curr, int *max) {
  int diff;
    diff = calc_diff(curr);
    if (diff > *max) *max = diff;
    if (curr->left) update_max(curr->left, max);
    if (curr->right) update_max(curr->right, max);
}

int tree::calc_diff(tree_node *curr) {
  int left, right, diff;
  if (!curr->left && !curr->right) return 0;
  else if (curr->left && !curr->right) {
    diff = solve2(curr->left);
  }
  else if (!curr->left && curr->right) {
    diff = solve2(curr->right);
  }
  else {
    left = solve2(curr->left);
    right = solve2(curr->right);
    diff = right > left ? right - left : left - right;
  }
  return diff;
}

int tree::solve5(tree_node * curr) {
  int count = 0;
  if (!curr) return 0;
  if (curr->right && !curr->left) {
    count++;
    count += solve5(curr->right);
  }
  else if (curr->left && !curr->right) {
    count++;
    count += solve5(curr->left);
  }
  else if (curr->left && curr->right) {
    count += solve5(curr->left) + solve5(curr->right);
  }
  return count;
}
