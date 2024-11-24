#include "tree.h"

int tree::get_count_leaf(tree_node * curr) const {
  if (!curr) return 0;
  if (!curr->left && !curr->right) return 1;
  else if (!curr->left) return get_count_leaf(curr->right);
  else if (!curr->right) return get_count_leaf(curr->left);
  else return get_count_leaf(curr->right) + get_count_leaf(curr->left);
}

int tree::get_height(tree_node * curr) const {
  int count = 1, left, right;
  if (!curr) return 0;
  if (curr->left && !curr->right) {
    count += get_height(curr->left);
  }
  else if (curr->right && !curr->left) {
    count += get_height(curr->right);
  }
  else if (curr->left && curr->right) {
    left = get_height(curr->left);
    right = get_height(curr->right);
    count += left < right ? right : left;
  }
  return count;
}
int tree::get_width(tree_node *curr) const {
  int max = 0, n, level;
  for(level = 0; (n = solve3_recc(curr, level, 0)); level++) {
    if(max < n) max = n;
  }
  return max;
}

int tree::solve3_recc(tree_node * curr, int level, int curr_level) const {
  if(curr == nullptr) return 0;
  if(level == curr_level) return 1;
  return solve3_recc(curr -> right, level, curr_level + 1) + solve3_recc(curr -> left, level, curr_level + 1);
}

int tree::get_balance(tree_node *curr) const {
  int max = 0;
  if (curr) update_max(curr, &max);
  return max;
}

void tree::update_max(tree_node *curr, int *max) const {
  int diff;
    diff = calc_diff(curr);
    if (diff > *max) *max = diff;
    if (curr->left) update_max(curr->left, max);
    if (curr->right) update_max(curr->right, max);
}

int tree::calc_diff(tree_node *curr) const {
  int left, right, diff;
  if (!curr->left && !curr->right) return 0;
  else if (curr->left && !curr->right) {
    diff = get_height(curr->left);
  }
  else if (!curr->left && curr->right) {
    diff = get_height(curr->right);
  }
  else {
    left = get_height(curr->left);
    right = get_height(curr->right);
    diff = right > left ? right - left : left - right;
  }
  return diff;
}

int tree::get_count_1(tree_node * curr) const {
  int count = 0;
  if (!curr) return 0;
  if (curr->right && !curr->left) {
    count++;
    count += get_count_1(curr->right);
  }
  else if (curr->left && !curr->right) {
    count++;
    count += get_count_1(curr->left);
  }
  else if (curr->left && curr->right) {
    count += get_count_1(curr->left) + get_count_1(curr->right);
  }
  return count;
}

int tree::get_count_total(tree_node *curr) const {
  if (!curr) return 0;
  if (!curr->left && !curr->right) return 1;
  else if (!curr->left) return 1 + get_count_total(curr->right);
  else if (!curr->right) return 1 + get_count_total(curr->left);
  else return 1 + get_count_total(curr->right) + get_count_total(curr->left);
}

int tree::get_count_2(tree_node *curr) const {
  int count = 0;
  if (!curr) return 0;
  if (curr->right && !curr->left) {
    count += get_count_2(curr->right);
  }
  else if (curr->left && !curr->right) {
    count += get_count_2(curr->left);
  }
  else if (curr->left && curr->right) {
    count++;
    count += get_count_2(curr->left) + get_count_2(curr->right);
  }
  return count;
}
