#ifndef BTREE
#define BTREE
#include "btree_node.h"
template <class T>
class b_tree {
private:
  int m; // B-tree base
  b_tree_node<T> * root = nullptr;
public:
  b_tree (int i = 0) {m = i;}
  ~b_tree() {
    delete_subtree (root);
    erase_links ();
  }
  io_status read (FILE * fp = stdin) {
    T x;
    io_status r;
    while(x.read(fp) == io_status::success) {
      r = add_value(x);
      if (r != io_status::success) return r;
    }
    if (!feof(fp)) return io_status::eof;
    return io_status::success;
  }
  void print (int r, FILE * fp = stdout) const {
    print_subtree (root, 0, r, fp);
  }
private:
  void erase_links () {
    m = 0;
    root = nullptr;
  }
  static void delete_subtree (b_tree_node<T> * curr) {
    if (curr == nullptr) return;
    for (int i = 0; i <= curr->size; i++) delete_subtree (curr->children[i]);
    delete curr;
  }
  static void print_subtree (b_tree_node<T> * curr, int level, int r, FILE * fp = stdout) {
    if (curr == nullptr || level > r) return;
    curr->print (level, fp);
    for (int i = 0; i <= curr->size; i++) {
      if (curr->children[i] && level + 1 <= r) {
        for (int j = 0; j < level; j++) fprintf (fp, "  ");
        fprintf (fp, "children[%2d]\n", i);
        print_subtree (curr->children[i], level + 1, r, fp);
      }
    }
  }
  io_status add_value (T& x) {
    if (root == nullptr) {
      root = new b_tree_node<T>();
      if (root == nullptr) return io_status::memory;
      if (root->init(m) != io_status::success) {
        delete root;
        return io_status::memory;
      }
      root->values[0] = static_cast<T&&>(x);
      root->size = 1;
      return io_status::success;
    }
    b_tree_node<T> *curr = root, *down = nullptr;
    io_status r = add_value_subtree (curr, down, x, m);
    if (r == io_status::memory) return io_status::memory;
    if (r == io_status::success) return io_status::success;
    // иначе r == io_status::create и был создан новый узел
    // который возвращается в ’down’
    // Создаем новый корень с одним значением ’x’
    // и двумя потомками ’curr’ and ’down’
    b_tree_node<T>* p = new b_tree_node<T>();
    if (p == nullptr) return io_status::memory;
    if (p->init (m) != io_status::success) {
      delete p;
      return io_status::memory;
    }
    p->values[0] = static_cast<T&&>(x);
    p->children[0] = curr;
    p->children[1] = down;
    p->size = 1;
    root = p;
    return io_status::success;
  }
  // Insert value ’x’ with children ’down’ at subtree ’curr’
  static io_status add_value_subtree (b_tree_node<T>*& curr, b_tree_node<T>*& down, T& x, int m) {
    int index = curr->bin_search (x);
    b_tree_node<T>* p = curr->children[index];
    if (p != nullptr) { // Есть потомок
      io_status r = add_value_subtree (p, down, x, m);
      if (r == io_status::memory) return io_status::memory;
      if (r == io_status::success) return io_status::success;
      // иначе r == io_status::create
      // и был создан новый узел,
      // который возвращается в ’down’
    }
    else down = nullptr;
    if (curr->size < 2 * m) { // Есть свободное место в текущем узле
      curr->add_value (x, down, index);
      return io_status::success;
    }
    else { // Создаем новый узел
      b_tree_node<T>* p = new b_tree_node<T>();
      if (p == nullptr) return io_status::memory;
      if (p->init (m) != io_status::success) {
        delete p;
        return io_status::memory;
      }
      if (index == m) { // ’x’ ровно посередине.
        // Перемещаем вторую половину в новый узел
        for (int i = 1; i <= m; i++) {
          p->values[i - 1] = static_cast<T&&>(curr->values[i + m - 1]);
          p->children[i] = curr->children[i + m];
          curr->children[i + m] = nullptr;
        }
        p->children[0] = down; // меньше всех
      }
      if (index < m) { // ’x’ в первой половине.
        // Перемещаем вторую половину в новый узел
        for (int i = 0; i < m; i++) {
          p->values[i] = static_cast<T&&>(curr->values[i + m]);
          p->children[i] = curr->children[i + m];
          curr->children[i + m] = nullptr;
        }
        p->children[m] = curr->children[2 * m];
        curr->children[2 * m] = nullptr;
        // сдвигаем элементы вправо
        // и вставляем ’x’ в позицию ’index’
        for (int i = m; i > index; i--) {
          curr->values[i] = static_cast<T&&> (curr->values[i - 1]);
          curr->children[i + 1] = curr->children[i];
        }
        curr->children[index + 1] = down;
        curr->values[index] = static_cast<T&&>(x);
        x = static_cast<T&&> (curr->values[m]);
        // новый ’x’ - максимальный
      }
      if (index > m) { // ’x’ во второй половине.
        // Перемещаем вторую половину до ’index’
        // в новый узел
        p->children[0] = curr->children[m + 1];
        curr->children[m + 1] = nullptr;
        for (int i = 1 ; i < index - m; i++) {
          p->values[i - 1] = static_cast<T&&> (curr->values[i + m]);
          p->children[i] = curr->children[i + m + 1];
          curr->children[i + m + 1] = nullptr;
        }
        // Вставляем ’x’ в нужную позицию
        p->values[index - m - 1] = static_cast<T&&> (x);
        p->children[index - m] = down;
        // Перемещаем остаток второй половины в новый узел
        for (int i = index - m + 1; i <= m; i++) {
          p->values[i - 1] = static_cast<T&&> (curr->values[i + m - 1]);
          p->children[i] = curr->children[i + m];
          curr->children[i + m] = nullptr;
        }
        x = static_cast<T&&> (curr->values[m]);
        // новый ’x’ - максимальный
      }
      down = p;
      p->size = m;
      curr->size = m;
      return io_status::create;
      // создан новый узел, он возвращается в ’down’
    }
    return io_status::success;
  }
public:
  //===============================
  //           Task 1
  //===============================
  int solve1(int k) {
    int count = 0;
    solve1_recc(root, &count, k);
    return count;
  }
  void solve1_recc(b_tree_node<T> *curr, int *count, int k) {
    if (curr == nullptr) return;
    int size = curr->size;
    int j= 0;
    for (b_tree_node<T> *p = (curr->children)[j]; p; p = (curr->children)[++j]);
    if (j == k) (*count) += size;
    for (int i = 0; i <= size; i++) {
      if ((curr->children)[i]) solve1_recc((curr->children)[i], count, k);
    }
  }
  //===============================
  //           Task 2
  //===============================
  int solve2(int k) {
    int count = 0;
    solve2_recc(root, k, &count);
    return count;
  }
  int count_subtree(b_tree_node<T> *curr, int *num) {
    if (curr == nullptr) return 0;
    (*num)++;
    int size = curr->size;
    int count = size;
    for (int i = 0; i <= size; i++) {
      count += count_subtree((curr->children)[i], num);
    }
    return count;
  }
  void solve2_recc(b_tree_node<T> *curr, int k, int *count) {
    if (curr == nullptr) return;
    int num = 0, c;
    c = count_subtree(curr, &num);
    if (num <= k) {(*count) += c; return;}
    for (int i = 0; i <= curr->size; i++) {
      solve2_recc(curr->children[i], k, count);
    }
  }
  //===============================
  //           Task 3
  //===============================
  int solve3(int k) {
    int count = 0;
    solve3_recc(root, k, &count);
    return count;
  }
  int count_level_subtree(b_tree_node<T> *curr, int *num, int level) {
    if (curr == nullptr) return 0;
    if (*num < level) *num = level;
    int size = curr->size;
    int count = size;
    for (int i = 0; i <= size; i++) {
      count += count_level_subtree((curr->children)[i], num, level+1);
    }
    return count;
  }
  void solve3_recc(b_tree_node<T> *curr, int k, int *count) {
    if (curr == nullptr) return;
    int num = 0, c;
    c = count_level_subtree(curr, &num, 1);
    if (num <= k) {(*count) += c; return;}
    for (int i = 0; i <= curr->size; i++) {
      solve3_recc(curr->children[i], k, count);
    }
  }
  //===============================
  //           Task 4
  //===============================
  int solve4(int k) {
    int count = 0;
    solve4_recc(root, k, &count);
    return count;
  }
  int get_height(b_tree_node<T>*curr) {
    if (curr == nullptr) return 0;
    int count = 1, height, max_height = 0;
    for (int i = 0; i <= curr->size; i++) {
      height = get_height(curr->children[i]);
      if (height > max_height) max_height = height;
    }
    return count + max_height;
  }
  void count_nodes_kth_level(b_tree_node<T> *curr, int goal, int level, int *count) {
    if (curr == nullptr || level > goal) return;
    if (goal == level) (*count)++;
    for (int i = 0; i <= curr->size; i++) {
      count_nodes_kth_level(curr->children[i], goal, level+1, count);
    }
  }
  int check_subtree(b_tree_node<T> *curr, int k) {
    int height = get_height(curr);
    int count;
    for (int i = 0; i < height; i++) {
      count = 0;
      count_nodes_kth_level(curr, i, 0, &count);
      if (count > k) {
        return -1;
      }
    }
    return 1;
  }
  void solve4_recc(b_tree_node<T> *curr, int k, int *count) {
    if (curr == nullptr) return;
    int num = 0, c;
    num = check_subtree(curr, k);
    if (num == 1) {
      c = count_subtree_less(curr);
      (*count) += c;
      return;
    }
    for (int i = 0; i <= curr->size; i++) {
      solve4_recc(curr->children[i], k, count);
    }
  }
  int count_subtree_less(b_tree_node<T> *curr) {
    if (curr == nullptr) return 0;
    int size = curr->size;
    int count = size;
    for (int i = 0; i <= size; i++) {
      count += count_subtree_less((curr->children)[i]);
    }
    return count;
  }
  //===============================
  //           Task 5
  //===============================
  int solve5(int k) {
    int count = 0;
    count_kth_level(root, k, 0, &count);
    return count;
  }
  void count_kth_level(b_tree_node<T> *curr, int goal, int level, int *count) {
    if (curr == nullptr || level > goal) return;
    if (goal == level) (*count) += curr->size;
    for (int i = 0; i <= curr->size; i++) {
      count_kth_level(curr->children[i], goal, level+1, count);
    }
  }
};
#endif
