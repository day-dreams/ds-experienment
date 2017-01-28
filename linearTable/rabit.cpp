// for 1.2 problem abou t rabit

#include <iostream>
using namespace std;

const unsigned int NUM = 10;

int main() {
  int holes[1 + NUM] = {};
  int step = 1, pos = -1;
  for (int i = 0; i != 1000; ++i) {
    pos += step;
    pos = pos % NUM + 1;
    holes[pos] = 1;
    ++step;
  }
  for (int i = 1; i != NUM + 1; ++i) {
    cout << "[" << i << "]	" << holes[i] << endl;
  }
}
