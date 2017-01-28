#include "expressionParser.h"
#include <iostream>
using namespace std;
int main() {
  string text;
  while (true) {
    cout << "input an expression: ";
    cin >> text;
    cout << "result: " << parser(text) << endl;
    cin.get();
    cin.get();
  }
  return 0;
}
