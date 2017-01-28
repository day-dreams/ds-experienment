#include "completeGraph.h"

int main(int argc, char **argv) {
  completeGraph map(atoi(argv[1]));
  map.show_weight();
  map.Floyd_Warshall();
  // map.show_weight();
  // cout << "Dijkstra::::" << endl;
  // map.Dijkstra(atoi(argv[2]));
  // cout << "BellmanFord::::" << endl;
  // map.BellmanFord(atoi(argv[2]));
  // cout << "Floyd_Warshall::::" << endl;
}
// map.show_dist();
