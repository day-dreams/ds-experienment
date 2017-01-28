#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef int value_type;
const int MIN = -1;

class colection {
private:
  vector<value_type> col, raw_col;
  vector<queue<value_type>> buckets; // for redix-sort

  void _sort_heap(int index);
  int _search_binary(int low, int high, value_type &value);

public:
  colection() : col(), raw_col(), buckets(10) {}
  void add(value_type value) {
    col.push_back(value);
    raw_col.push_back(value);
  }
  void search_inorder(value_type value);
  void search_binary(value_type value);
  void search_hash(value_type value);
  void sort_selection();
  void sort_heap();
  void sort_redix();
  void show();
  void show_heap();
};

void colection::show() {
  for (auto &x : col)
    cout << x << ' ';
  cout << endl;
}

void colection::sort_selection() {
  col = raw_col;
  for (int i = 0; i != col.size() - 1; ++i) {
    auto min = col[i];
    auto min_index = i;
    for (int j = i + 1; j != col.size(); ++j) {
      if (min > col[j]) {
        min = col[j];
        min_index = j;
      }
    }
    if (min_index != i) {
      col[min_index] = col[i];
      col[i] = min;
    }
  }
}

void colection::_sort_heap(int index) {
  int right_child;
  if (index == 0) {
    right_child = 2;
  } else {
    right_child = index * 2;
  }
  auto left_child = right_child - 1;
  if (left_child >= col.size()) {
    // with no child, a leaf ndoe
    return;
  } else if (right_child >= col.size()) {
    // with only left child
    if (col[index] > col[left_child]) {
      auto tem = col[index];
      col[index] = col[left_child];
      col[left_child] = tem;
      _sort_heap(left_child);
    }
  } else {
    // with left and right children
    auto branch_index = index;
    if (col[branch_index] > col[left_child])
      branch_index = left_child;
    if (col[branch_index] > col[right_child])
      branch_index = right_child;
    if (branch_index == index) {
      // min-heap,no operations is needed
    } else {
      auto tem = col[index];
      col[index] = col[branch_index];
      col[branch_index] = tem;
      _sort_heap(branch_index);
    }
  }
}

void colection::sort_heap() {
  col = raw_col;
  for (int i = col.size() - 1; i != -1; --i)
    _sort_heap(i);
}

void colection::show_heap() {
  auto time = col.size() - 1;
  for (int i = 0; i <= time; ++i) {
    cout << col[0] << ' ';
    col[0] = col.back();
    col.pop_back();
    _sort_heap(0);
  }
  cout << endl;
}

int get_bit(value_type &value, int bit_index) {
  int result = 0;
  int mod = 1;
  for (int i = 1; i < bit_index; ++i)
    mod *= 10;
  result = (value / mod) % 10;
  return result;
}

void colection::sort_redix() {
  // a different way to sort, unlike traditional compare-sort
  col = raw_col;
  for (int bit_index = 1; bit_index <= 2; ++bit_index) {
    for (auto &value : col)
      buckets[get_bit(value, bit_index)].push(value);
    int i = 0;
    for (auto &bucket : buckets) {
      while (!bucket.empty()) {
        col[i++] = bucket.front();
        bucket.pop();
      }
    }
    // cout << "\nbit_index:" << bit_index << "\t\t";
    // this->show();
  }
}

void colection::search_inorder(value_type value) {
  col = raw_col;
  int i = col.size() - 1;
  for (; i >= 0; --i)
    if (col[i] == value)
      break;
  cout << "inorder-search   position: " << i << endl;
}

int colection::_search_binary(int low, int high, value_type &value) {
  if (low == high) {
    if (col[low] == value)
      return low;
    else
      return -1;
  } else if (low == high - 1) {
    if (col[low] == value)
      return low;
    else if (col[high] == value)
      return high;
    else
      return -1;
  }
  auto mid = (low + high) / 2;
  auto result = _search_binary(low, mid, value);
  if (result != -1)
    return result;
  else
    return _search_binary(mid, high, value);
}

void colection::search_binary(value_type value) {
  col = raw_col;
  auto index = _search_binary(0, col.size() - 1, value);
  cout << "binary-search    position: " << index << endl;
}

void colection::search_hash(value_type value) {
  col = vector<int>(raw_col.size(), -1);
  // hash-function: value%size
  for (int i = 0; i < raw_col.size(); ++i) {
    auto pos = raw_col[i] % col.size();
    while (col[pos] != -1) {
      // hash conflict
      ++pos; // linear detect, (pos+m)%size
      pos %= raw_col.size();
    }
    col[pos] = raw_col[i];
  }
  auto pos = value % col.size();
  if (col[pos] == -1)
    cout << "hash-search      position: " << -1 << endl;
  else {
    while (col[pos] != value) {
      ++pos;
      pos %= raw_col.size();
      if (value % col.size() == pos) {
        cout << "hash-search      position: " << -1 << endl;
        return;
      }
    }
    cout << "hash-search      position: " << pos << endl;
  }
}

value_type str_to_value(char *str) { return atoi(str); }
