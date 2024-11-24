#include "tree.h"

void tree::solve1(tree_node *curr) {
  tree_node *l, *r, *c;
  if (!curr) return;
  if (!curr->right && !curr->left) return;

  if (curr->right && !curr->left) {
    r = find_max_subtree(curr->right);
    if (*r > *curr) swap_tree_nodes(curr, r);
  }
  else if (curr->left && !curr->right) {
    l = find_max_subtree(curr->left);
    if (*l > *curr) swap_tree_nodes(curr, l);
  }
  else if (curr->right && curr->left){
    r = find_max_subtree(curr->right);
    l = find_max_subtree(curr->left);
    if (*r > *l) c = r;
    else c = l;
    if (*c > *curr) swap_tree_nodes(curr, c);
  }

  if (curr->right) solve1(curr->right);
  if (curr->left) solve1(curr->left);
}

tree_node * tree::find_max_subtree(tree_node *curr) {
  tree_node *lmax = nullptr, *rmax = nullptr, *cmax;
  if (!curr) return curr;
  if (!curr->right && !curr->left) return curr;
  if (curr->right && curr->left == nullptr && (curr->right)->left == nullptr && (curr->right)->right == nullptr) {
    if (*curr > *(curr->right)) return curr;
    else return curr->right;
  }
  else if (curr->right == nullptr && curr->left && (curr->left)->left == nullptr && (curr->left)->right == nullptr) {
    if (*curr > *(curr->left)) return curr;
    else return curr->left;
  }
  else if (curr->right && curr->left && (curr->right)->left == nullptr && (curr->right)->right == nullptr && (curr->left)->left == nullptr && (curr->left)->right == nullptr) {
    if (*(curr->right) > *(curr->left)) cmax = curr->right;
    else cmax = curr->left;
    if (*curr > *cmax) return curr;
    else return cmax;
  }
  else if (curr->right && !curr->left) {
    rmax = find_max_subtree(curr->right);
    if (*rmax > *curr) return rmax;
    else return curr;
  }
  else if (curr->left && !curr->right) {
    lmax = find_max_subtree(curr->left);
    if (*lmax > *curr) return lmax;
    else return curr;
  }
  else {
    lmax = find_max_subtree(curr->left);
    rmax = find_max_subtree(curr->right);
    if (*rmax > *lmax) cmax = rmax;
    else cmax = lmax;
    if (*curr > *cmax) return curr;
    else return cmax;
  }
}

void tree::solve3(tree_node *curr, tree_node *prev) {
  tree_node *b, *c, *t = nullptr, *a;
  int flag = 0;
  if (!curr) return;
  if (curr == root) {
    a = root;
    if (curr->right && !curr->left && ((curr->right)->left || (curr->right)->right)) {
      b = curr->right;
      c = b;
      while ((c->left)) {
        t = c;
        c = c->left;
      }
      if (t && !(c->right)) {
        flag = 1;
        t->left = nullptr;
        a->erase_links();
        root = c;
        root->right = b;
        root->left = a;
      }
    }
  }
  else {
    a = curr;
    if (curr->right && !curr->left && ((curr->right)->left || (curr->right)->right)) {
      b = curr->right;
      c = b;
      while ((c->left)) {
        t = c;
        c = c->left;
      }
      if (t && !(c->right)) {
        flag = 1;
        t->left = nullptr;
        if (curr == prev->right) prev->right = c;
        else prev->left = c;
        a->erase_links();
        curr = b;
        c->right = b;
        c->left = a;
      }
    }
  }
  if (flag == 0) {
    if (curr->right) solve3(curr->right, curr);
    if (curr->left) solve3(curr->left, curr);
  }
  else {
    solve3(b, c);
  }
}

void tree::solve4(tree_node *curr, tree_node *prev) {
  tree_node *b, *c, *t = nullptr, *a;
  int flag = 0;
  if (!curr) return;
  if (curr == root) {
    a = root;
    if (curr->left && !curr->right && ((curr->left)->right || (curr->left)->left)) {
      b = curr->left;
      c = b;
      while ((c->right)) {
        t = c;
        c = c->right;
      }
      if (t && !(c->left)) {
        flag = 1;
        t->right = nullptr;
        a->erase_links();
        root = c;
        root->left = b;
        root->right = a;
      }
    }
  }
  else {
    a = curr;
    if (curr->left && !curr->right && ((curr->left)->left || (curr->left)->right)) {
      b = curr->left;
      c = b;
      while ((c->right)) {
        t = c;
        c = c->right;
      }
      if (t && !(c->left)) {
        flag = 1;
        t->right = nullptr;
        if (curr == prev->right) prev->right = c;
        else prev->left = c;
        a->erase_links();
        curr = c;
        curr->left = b;
        curr->right = a;
      }
    }
  }
  if (flag == 0) {
    if (curr->right) solve4(curr->right, curr);
    if (curr->left) solve4(curr->left, curr);
  }
  else {
    solve4(b, c);
  }
}

void tree::solve5(const student& petya) {
  char *s = petya.get_name();
  int k = petya.get_value();
  if (root && check_subtree(root, s, k) == 1) {delete_subtree(root); root = nullptr;}
  else magic5(root, s, k);
}

void tree::magic5(tree_node *curr, char *s, int k) {
  if (!curr) return;
  if (curr->right && check_subtree(curr->right, s, k) == 1) {delete_subtree(curr->right); curr->right = nullptr;}
  if (curr->left && check_subtree(curr->left, s, k) == 1) {delete_subtree(curr->left); curr->left = nullptr;}
  if (curr->right) magic5(curr->right, s, k);
  if (curr->left) magic5(curr->left, s, k);
}

int tree::check_subtree(tree_node * curr, char * s, int k) {
  int res = 1;
  int level = get_height_mod(curr, s, &res);
  if (res == 1 && level >= k) return 1;
  else return -1;
}


void tree::solve6(const student& petya) {
  char *s = petya.get_name();
  int k = petya.get_value();
  if (root) {
    if ((root->right && check_subtree(root->right, s, k) == 1) || (root->left && check_subtree(root->left, s, k) == 1)) {
      delete_subtree(root);
      root = nullptr;
      return;
    }
    magic6(root, s, k);
  }
}


void tree::magic6(tree_node *curr, char *s, int k) {
  tree_node *r;
  if (!curr) return;
  if (curr->right) {
    r = curr->right;
    if ((r->right && check_subtree(r->right, s, k) == 1) || (r->left && check_subtree(r->left, s, k) == 1)) {
      delete_subtree(curr->right);
      curr->right = nullptr;
    }
  }
  if (curr->left) {
    r = curr->left;
    if ((r->right && check_subtree(r->right, s, k) == 1) || (r->left && check_subtree(r->left, s, k) == 1))  {
      delete_subtree(curr->left);
      curr->left = nullptr;
    }
  }
  if (curr->right) magic6(curr->right, s, k);
  if (curr->left) magic6(curr->left, s, k);
}

int tree::get_height_mod(tree_node *curr, char * s, int* res) {
  int count = 1, left, right;
  if (!curr) return 0;
  char *name = ((student*) curr)->get_name();
  if (strstr(name, s) == nullptr) *res = -1;
  if (curr->left && !curr->right) {
    count += get_height_mod(curr->left, s, res);
  }
  else if (curr->right && !curr->left) {
    count += get_height_mod(curr->right, s, res);
  }
  else if (curr->left && curr->right) {
    left = get_height_mod(curr->left, s, res);
    right = get_height_mod(curr->right, s, res);
    count += left < right ? right : left;
  }
  return count;
}

tree_node * tree::get_to_ith(tree_node *curr, int level, int goalh, int goalw, int* i) {
  tree_node *l = nullptr, *r = nullptr;
  if (!curr) return nullptr;
  if (level == goalh && goalw == *i) return curr;
  if (goalh == level) (*i)++;
  if (level < goalh) {
    if (curr->left) l = get_to_ith(curr->left, level+1, goalh, goalw, i);
    if (l) return l;
    if (curr->right) r = get_to_ith(curr->right, level+1, goalh, goalw, i);
    if (r) return r;
  }
  return nullptr;
}

void tree::nodes_on_level(tree_node * curr, int level, int goal, int *i) {
  if (!curr) return;
  if (level == goal) (*i)++;
  if (level > goal) return;
  if (curr->left) nodes_on_level(curr->left, level+1, goal, i);
  if (curr->right) nodes_on_level(curr->right, level+1, goal, i);
}

void tree::solve2(int h) {
  int i, width = 0, j, k, c;
  tree_node *min, *cur, *tek;
  for (i = 0; i < h; i++) {
    width = 0;
    nodes_on_level(root, 0, i, &width);
    if (width > 1) {
      for (c = 0; c < width; c++) {
        j = 0;
        min = get_to_ith(root, 0, i, c, &j);
        j = 0;
        tek = get_to_ith(root, 0, i, c, &j);
        for (k = c+1; k < width; k++) {
          j = 0;
          cur = get_to_ith(root, 0, i, k, &j);
          if (cur && min && cmp_val(cur, min) == 1) min = cur;
        }
        if (tek && min) {
          swap_tree_nodes(tek, min);
        }
      }
    }
  }
}

int tree::cmp_val(tree_node *first, tree_node *second) {
  int val1 = ((student *) first)->get_value();
  int val2 = ((student *) second)->get_value();
  if (val1 < val2) return 1;
  else return 0;
}

void tree::solve7(int h, const student & jerry) {
  char *s = jerry.get_name();
  int k = jerry.get_value();
  magic7(s, k, h);
}

void tree::magic7(char *s, int k, int h) {
  int i, width, res, l, t, flag = 0;
  for (i = 0; i < h; i++) {
    width = 0;
    nodes_on_level(root, 0, i, &width);
    if (width >= k) {
      flag = 0;
      for (l = 0; l < width-k+1; l++) {
        res = 1;
        t = 0;
        check_level(root, 0, i, &res, &t, l, l+k-1, s);
        if (res == 1) flag = 1;
      }
      if (flag == 1) {
        if (i == 0) {
          delete_subtree(root);
          root = nullptr;
          return;
        }
        else {
          delete_level(root, 0, i-1);
          return;
        }
      }
    }
  }
}

void tree::nodes_on_level_mod(tree_node * curr, int level, int goal, int *i, char *s, int *res) {
  if (!curr) return;
  if (level == goal) (*i)++;
  if (level > goal) return;
  char *name = ((student*) curr)->get_name();
  if (strstr(name, s) == nullptr) *res = -1;
  if (curr->left) nodes_on_level(curr->left, level+1, goal, i);
  if (curr->right) nodes_on_level(curr->right, level+1, goal, i);
}

void tree::check_level(tree_node *curr, int level, int goal, int *res, int *i, int start, int end, char *s) {
  if (!curr) return;
  if (level == goal) {
    if (start <= *i && *i <= end) {
      char *name = ((student*) curr)->get_name();
      if (strstr(name, s) == nullptr) *res = -1;
    }
    (*i)++;
  }
  if (level > goal) return;
  if (curr->left) check_level(curr->left, level+1, goal, res, i, start, end, s);
  if (curr->right) check_level(curr->right, level+1, goal, res, i, start, end, s);
}

void tree::delete_level(tree_node * curr, int level, int goal) {
  if (!curr) return;
  if (level == goal) {
    if (curr->right) {delete_subtree(curr->right); curr->right = nullptr;}
    if (curr->left) {delete_subtree(curr->left); curr->left = nullptr;}
  }
  if (level > goal) return;
  if (curr->left) delete_level(curr->left, level+1, goal);
  if (curr->right) delete_level(curr->right, level+1, goal);
}
