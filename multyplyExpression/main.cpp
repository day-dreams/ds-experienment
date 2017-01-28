#include "expression.h"
#include <iostream>
#include <string>
using namespace std;
int main() {
  double x;
  while (true) {
    cout << "input x: ";
    cin >> x;
    cin.get();
    string str;
    char argc[100];
    cout << "input expression a: ";
    cin.getline(argc, 1000);
    expression a(str.append(argc));
    cout << "input expression b: ";
    cin.getline(argc, 1000);
    str.clear();
    expression b(str.append(argc));
    cout << "a+b:";
    (a + b).show(x);
    cout << "a*b:";
    (a * b).show(x);
    cout << "--------------------------------" << endl;
  }
}
