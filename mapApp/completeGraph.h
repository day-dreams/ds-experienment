#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

//#define DebugInfo cout << "running here: line_" << __LIsizeE__ << endl;
#define DebugInfo ;

uniform_int_distribution<int> dis(5, 50);
random_device rd;

class completeGraph {
private:
  int size, source;
  vector<vector<int>> weight;
  vector<int> dist;
  vector<int> pi;

  void initialize();
  void relax(int u, int v);
  int get_min_point(vector<bool> &S);

public:
  completeGraph(int size)
      : size(size), pi(size + 1), dist(size + 1),
        weight(size + 1, vector<int>(size + 1, 1000)) {
    weight[1][1] = 0;
    for (int i = 2; i < size + 1; ++i)
      weight[i][1] = weight[1][i] = dis(rd);

    for (int i = 2; i < size + 1; ++i)
      for (int j = 1; j < size + 1; ++j)
        if (i == j)
          weight[i][i] = 0;
        else if (dis(rd) < 40) {
          if (i < j)
            weight[i][j] = dis(rd);
          else if (i > j)
            weight[i][j] = weight[j][i];
        }
  }
  void show_weight();
  void show_dist();
  void show_pre();
  void BellmanFord(int s);
  void Dijkstra(int s);
  void Floyd_Warshall();
};

void completeGraph::show_weight() {
  cout << "---------------------------------------------------------" << endl;
  cout << "原始图" << endl;
  cout << setw(5) << ' ';
  for (int i = 1; i < size + 1; ++i)
    cout << setw(5) << i;
  cout << endl;
  for (int i = 1; i < size + 1; ++i) {
    cout << setw(6) << i;
    for (int j = 1; j < size + 1; ++j)
      if (weight[i][j] == 1000)
        cout << setw(5) << "max";
      else
        cout << setw(5) << weight[i][j];
    cout << endl;
  }
}

void completeGraph::show_dist() {
  cout << "---------------------------------------------------------" << endl;
  cout << "最短路径长度\n";
  for (int i = 1; i < size + 1; ++i)
    cout << setw(5) << i;
  cout << endl;
  for (int i = 1; i < size + 1; ++i)
    cout << setw(5) << dist[i];
  cout << endl;
}

void completeGraph::show_pre() {
  cout << "---------------------------------------------------------" << endl;
  cout << "前驱节点" << endl;
  for (int i = 1; i < size + 1; ++i)
    cout << setw(5) << pi[i];
  cout << endl;
}

// set initial distance
void completeGraph::initialize() {
  for (int i = 1; i < size + 1; ++i) {
    pi[i] = source;
    if (i != source)
      dist[i] = weight[source][i];
    else
      dist[i] = 0;
  }
}

void completeGraph::relax(int u, int v) {
  if (dist[u] + weight[u][v] < dist[v]) {
    dist[v] = dist[u] + weight[u][v];
    pi[v] = u;
  }
}

void completeGraph::BellmanFord(int s) {
  source = s;
  initialize();
  for (int i = 1; i != size; ++i)
    for (int j = 1; j != size + 1; ++j)
      for (int k = 1; k != size + 1; ++k)
        relax(j, k);
  /*
    省略判断负权环
  */
  show_dist();
  show_pre();
}

int completeGraph::get_min_point(vector<bool> &S) {
  int min = -1, min_dist = 0xffff;
  for (int i = 1; i < size + 1; ++i)
    if (dist[i] < min_dist && !S[i]) {
      min = i;
      min_dist = dist[i];
    }
  return min;
}
void completeGraph::Dijkstra(int s) {
  source = s;
  DebugInfo;
  vector<bool> is_in_S(size + 1, false);
  DebugInfo;
  initialize();
  DebugInfo;
  while (find(is_in_S.begin() + 1, is_in_S.end(), false) != is_in_S.end()) {
    DebugInfo;
    auto min = get_min_point(is_in_S);
    is_in_S[min] = true;
    for (int i = 1; i < size + 1; ++i)
      relax(min, i);
  }
  show_dist();
  show_pre();
}

void completeGraph::Floyd_Warshall() {
  vector<vector<int>> dist(weight);
  auto pi(dist);
  for (int i = 1; i < size + 1; ++i)
    for (int j = 1; j < size + 1; ++j)
      pi[i][j] = 0;

  for (int k = 1; k < size + 1; ++k) {
    for (int i = 1; i < size + 1; ++i)
      for (int j = 1; j < size + 1; ++j)
        if (dist[i][j] > dist[i][k] + dist[k][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
  }

  for (int i = 1; i < size + 1; ++i) {
    for (int j = 1; j < size + 1; ++j) {
      for (int k = 1; k < size + 1; ++k)
        if (j == k)
          continue;
        else if (dist[i][k] + dist[k][j] == dist[i][j])
          pi[i][j] = k;
    }
  }
  // // show distance
  // cout << "distance:";
  // cout.put('\n');
  // for (int i = 1; i < size + 1; ++i) {
  //   for (int j = 1; j < size + 1; ++j)
  //     cout << setw(5) << dist[i][j];
  //   cout << endl;
  // }
  // cout << "pi:";
  // // show the pi
  // cout.put('\n');
  // for (int i = 1; i < size + 1; ++i) {
  //   for (int j = 1; j < size + 1; ++j)
  //     cout << setw(5) << pi[i][j];
  //   cout << endl;
  // }

  string input;
  while (std::getline(cin, input)) {
    cout << "input: " << input << endl;
    if (count(input.begin(), input.end(), '-') == 1) {
      // input three
      auto index = input.find('-');
      auto min = stoi(input.substr(0, index));
      auto max = stoi(input.substr(index + 1));
      for (int i = 1; i != size + 1; ++i)
        for (int j = 1; j != size + 1; ++j)
          if (dist[i][j] <= max && dist[i][j] >= min)
            cout << "(" << i << ',' << j << ",distance=" << dist[i][j] << ")\n";
      cout << endl;

    } else if (count(input.begin(), input.end(), ' ') == 0) {
      // input one
      int u = stoi(input);
      for (int v = 1; v != size + 1; ++v) {
        int k = v;
        while (pi[u][k] != 0) {
          cout << k << "<--";
          k = pi[u][k];
        }
        cout << u << "      len=" << dist[u][v] << endl;
      }
    } else if (count(input.begin(), input.end(), ' ') == 1) {
      // input two
      auto index = input.find(' ');
      auto u = stoi(input.substr(0, index));
      auto v = stoi(input.substr(index + 1));
      int k = v;
      while (pi[u][k] != 0) {
        cout << k << "<--";
        k = pi[u][k];
      }
      cout << u << "      len=" << dist[u][v] << endl;
    } else {
      // input error
      cout << "wrong input!" << endl;
    }
  }
}
