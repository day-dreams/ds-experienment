#include "binaryTree.h"
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  string x(argv[1]);
  string y(argv[2]);
  vector<char> before;
  vector<char> mid;
  do {
    before.push_back(x.front());
    x.erase(x.begin());
  } while (!x.empty());
  do {
    mid.push_back(y.front());
    y.erase(y.begin());
  } while (!y.empty());

  // vector<char> before{'a', 'b'};
  // vector<char> mid{'b', 'a'};
  //  vector<int> before{1, 2, 3, 4, 5, 6, 7};
  //  vector<int> mid{4, 2, 5, 1, 6, 3, 7};
  node *tem = new node();
  // cout << "----main--\n";
  auto root = buildTree(before, mid, tem);
  // cout << "----main--\n";

  show_after(root);
  cout << endl;
}
