#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>
using namespace std;
bool compare(pair<double, double> a, pair<double, double> b) {
  return std::get<1>(a) > std::get<1>(b);
}

class expression {
public:
  vector<pair<double, double>> pairs;
  expression(string argc);
  expression() {}
  expression operator+(expression &other);
  expression operator*(expression &other);
  void show(double x);
};

void expression::show(double x) {
  double result = 0;
  for_each(pairs.begin(), pairs.end(), [&](pair<double, double> ele) {
    cout << std::get<0>(ele) << "x^" << std::get<1>(ele) << " ";
    result += get<0>(ele) * pow(x, std::get<1>(ele));
  });
  cout << " = " << result << endl;
}
expression::expression(string argc) {
  size_t begin = 0;
  while (true) {
    size_t a = argc.find(" ", begin) + 1;
    size_t b = argc.find(" ", a);
    auto x = atof(argc.c_str() + begin);
    auto y = atof(argc.c_str() + a);
    pairs.push_back(make_pair(x, y));
    begin = b + 1;
    if (b == string::npos)
      break;
  }
  sort(pairs.begin(), pairs.end(), compare);
}

expression expression::operator+(expression &other) {
  expression tem;
  auto backup1 = this->pairs;
  auto backup2 = other.pairs;
  while (!this->pairs.empty() || !other.pairs.empty()) {
    // debug iformatino
    // cout << this->pairs.size() << "--" << other.pairs.size() << endl;

    if (this->pairs.empty()) {
      tem.pairs.push_back(other.pairs.back());
      other.pairs.pop_back();
    } else if (other.pairs.empty()) {
      tem.pairs.push_back(this->pairs.back());
      this->pairs.pop_back();
    } else {
      auto a = this->pairs.back();
      auto b = other.pairs.back();
      if (std::get<1>(a) == std::get<1>(b)) {
        tem.pairs.push_back(
            make_pair((std::get<0>(a)) + (std::get<0>(b)), std::get<1>(b)));
        this->pairs.pop_back();
        other.pairs.pop_back();
      } else if (std::get<1>(a) > std::get<1>(b)) {
        tem.pairs.push_back(a);
        this->pairs.pop_back();
      } else {
        tem.pairs.push_back(b);
        other.pairs.pop_back();
      }
    }
  }
  sort(tem.pairs.begin(), tem.pairs.end(), compare);
  this->pairs = backup1;
  other.pairs = backup2;
  return tem;
}

expression expression::operator*(expression &other) {
  expression tem;
  auto backup1 = this->pairs;
  auto backup2 = other.pairs;
  // cout << this->pairs.size() << "  " << other.pairs.size();
  for (auto i = this->pairs.begin(); i != this->pairs.end(); ++i) {
    for (auto j = other.pairs.begin(); j != other.pairs.end(); ++j) {
      auto a = std::get<0>(*i) * std::get<0>(*j);
      auto b = std::get<1>(*i) + std::get<1>(*j);
      tem.pairs.push_back(make_pair(a, b));
    }
  }
  sort(tem.pairs.begin(), tem.pairs.end(), compare);
  this->pairs = backup1;
  other.pairs = backup2;
  return tem;
}
