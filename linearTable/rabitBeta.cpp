#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
int main(int argc, char **argv) {
  int num = atoi(argv[1]);
  int times = atoi(argv[2]);
  vector<int> holes(num + 1, 0);
  int pos = -1, step = 1;
  for (int i = 0; i != times; ++i) {
    pos += step;
    pos = pos % num + 1;
    ++step;
    holes[pos] = 1;
  }
  for (int i = 1; i < num + 1; ++i) {
    cout << "[" << i << "]	" << holes[i] << endl;
  }
}
