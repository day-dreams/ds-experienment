#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
using namespace std;

map<string, int> ops{{"+", 1}, {"-", 1}, {"*", 2},
                     {"/", 2}, {"(", 3}, {")", 3}};

int getPriority(string ch) {
  auto ite = ops.find(ch);
  if (ite == ops.end())
    return -1;
  else
    return ite->second;
}

string getValue(string &text) {
  int pos = 0;
  for (; pos < text.size(); ++pos) {
    if (getPriority(text.substr(pos, 1)) != -1)
      break;
  }
  //    cout << "pos:" << pos << endl;
  // cout << "pos:" << pos << endl;
  string value = text.substr(0, pos);
  text = text.substr(pos);
  // debug information
  // cout << "get a value: " << value << endl;
  return value;
}

string getOperator(string &text) {

  string op = text.substr(0, 1);
  text = text.substr(1);
  // debug information
  // cout << "get an operator: " << op << endl;
  return op;
}

string doMathmatics(string &_a, string &_b, string op) {
  char x = op[0];
  double result, a = atof(_a.c_str()), b = atof(_b.c_str());
  switch (x) {
  case '+':
    result = a + b;
    break;
  case '-':
    result = a - b;
    break;
  case '*':
    result = a * b;
    break;
  case '/':
    result = a / b;
    break;
  }
  return to_string(result);
}
double calculate(queue<string> rpn) {
  stack<string> output;
  while (!rpn.empty()) {
    string x = rpn.front();
    rpn.pop();
    if (getPriority(x) == -1)
      output.push(x);
    else {
      auto b = output.top();
      output.pop();
      auto a = output.top();
      output.pop();
      output.push(doMathmatics(a, b, x));
    }
  }
  return atof(output.top().c_str());
}

double parser(string text) {
  stack<string> operators;
  queue<string> reverse_polish_novation;
  while (!text.empty()) {
    if (getPriority(text.substr(0, 1)) == -1) {
      // value
      reverse_polish_novation.push(getValue(text));
    } else {
      // an operator
      auto x = getOperator(text);
      if (x == ")") {
        while (operators.top() != "(") {
          reverse_polish_novation.push(operators.top());
          operators.pop();
        }
        operators.pop();
      } else if (operators.empty()) {
        operators.push(x);
      } else {
        // compare the decencing level
        if (getPriority(x) <= getPriority(operators.top())) {
          if (operators.top() == "(")
            operators.push(x);
          else {
            reverse_polish_novation.push(operators.top());
            operators.pop();
            operators.push(x);
          }
        } else {
          operators.push(x);
        }
      }
    }
  }
  while (!operators.empty()) {
    reverse_polish_novation.push(operators.top());
    operators.pop();
  }

  {
    // show the reverse polish novation
    cout << "RPN: ";
    auto novation = reverse_polish_novation;
    while (!novation.empty()) {
      cout << novation.front() << " ";
      novation.pop();
    }
    cout << endl;
  }

  return calculate(reverse_polish_novation);
  // // print the reverse polish novation
  // {
  //   auto tem = output;
  //   while (!tem.empty()) {
  //     cout << tem.front() << ' ';
  //     tem.pop();
  //   }
  //   cout << endl;
  // }
  // stack<string> result;
  // while (!output.empty()) {
  //   if (getPriority(output.front()) == -1) {
  //     result.push(output.front());
  //     output.pop();
  //   } else {
  //     string b = result.top();
  //     result.pop();
  //     string a = result.top();
  //     result.pop();
  //     result.push(doMathmatics(a, b, output.front()));
  //     output.pop();
  //   }
  // }
  //  return atof(result.top().c_str());
}
