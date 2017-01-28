#include "selfDefineColection.h"
#include <iostream>
#include <random>
#include <typeinfo>

using namespace std;

uniform_int_distribution<int> dis(1, 9);
random_device source;

int main(int argc, char **argv) {
  // cout << "value_type: " << typeid(value_type).name() << endl;
  colection col;
  for (int i = 0; i != 20; ++i)
    // col.add(str_to_value(argv[i]));
    col.add(dis(source) * 10 + dis(source) * 1);
  cout << "\nbefore operations:\n\t\t";
  col.show();
  cout << "\nafter selection-sort:\n\t\t";
  col.sort_selection();
  col.show();
  cout << "\nafter heap-sort:\n\t\t";
  col.sort_heap();
  col.show_heap();
  cout << "\nafter redix-sort:\n\t\t";
  col.sort_redix();
  col.show();
  cout << "\ninput a value to search:";
  value_type value;
  while (cin >> value) {
    col.search_inorder(value);
    col.search_binary(value);
    col.search_hash(value);
    cout << "\tafter hash:\t";
    col.show();
    cout << "\ninput a value to search:";
  }
  return 0;
}
