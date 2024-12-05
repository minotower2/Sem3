#include "tree.h"
#include "list2.h"
template class tree<student>;
template class tree<list2>;

template <class T>
int tree<T>::solve1(tree_node<T> * curr) {
  if (!curr) return 0;
  if (!curr->left && !curr->right) return curr->get_length();
  else if (!curr->left) return solve1(curr->right);
  else if (!curr->right) return solve1(curr->left);
  else return solve1(curr->right) + solve1(curr->left);
}

template <class T>
int tree<T>::solve2(tree_node<T> * curr) {
  if (!curr) return 0;
  int count = curr->get_length(), left, right;
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
template <class T>
int tree<T>::solve3(tree_node<T> *curr) {
  int max = 0, n, level;
  for(level = 0; (n = solve3_recc(curr, level, 0)); level++) {
    if(max < n) max = n;
  }
  return max;
}

template <class T>
int tree<T>::solve3_recc(tree_node<T> * curr, int level, int curr_level) {
  if(curr == nullptr) return 0;
  if(level == curr_level) return curr->get_length();
  return solve3_recc(curr -> right, level, curr_level + 1) + solve3_recc(curr -> left, level, curr_level + 1);
}

template <class T>
int tree<T>::solve4(tree_node<T> *curr) {
  int max = 0;
  if (curr) update_max(curr, &max);
  return max;
}

template <class T>
void tree<T>::update_max(tree_node<T> *curr, int *max) {
  int diff;
    diff = calc_diff(curr);
    if (diff > *max) *max = diff;
    if (curr->left) update_max(curr->left, max);
    if (curr->right) update_max(curr->right, max);
}

template <class T>
int tree<T>::calc_diff(tree_node<T> *curr) {
  int left, right, diff;
  if (!curr->left && !curr->right) return 0;
  else if (curr->left && !curr->right) {
    diff = get_count_total(curr->left);
  }
  else if (!curr->left && curr->right) {
    diff = get_count_total(curr->right);
  }
  else {
    left = get_count_total(curr->left);
    right = get_count_total(curr->right);
    diff = right > left ? right - left : left - right;
  }
  return diff;
}

template <class T>
int tree<T>::get_count_total(tree_node<T> *curr) {
  if (!curr) return 0;
  int len = curr->get_length();
  if (!curr->left && !curr->right) return len;
  else if (!curr->left) return len + get_count_total(curr->right);
  else if (!curr->right) return len + get_count_total(curr->left);
  else return len + get_count_total(curr->right) + get_count_total(curr->left);
}
template <class T>
int tree<T>::solve5(tree_node<T> * curr) {
  int count = 0;
  if (!curr) return 0;
  int len = curr->get_length();
  if (curr->right && !curr->left) {
    count+=len;
    count += solve5(curr->right);
  }
  else if (curr->left && !curr->right) {
    count+=len;
    count += solve5(curr->left);
  }
  else if (curr->left && curr->right) {
    count += solve5(curr->left) + solve5(curr->right);
  }
  return count;
}
