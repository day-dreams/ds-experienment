// it's easier to solve the problem by double-side list
// but you have to be care about the boundary conditions!
#include <cstdlib>
#include <iostream>
#include <new>
using namespace std;

struct node {
  int pos;
  struct node *next;
  struct node *prv;
};

void Josephu(int n, int m, int k) {
  struct node *head = new node();
  head->pos = 1;
  struct node *prv = head, *now;
  for (int i = 1; i < n; ++i) {
    now = new node();
    now->pos = i + 1;
    prv->next = now;
    now->prv = prv;
    prv = now;
    now = now->next;
  }
  prv->next = head;
  head->prv = prv;
  now = head;
  for (int i = 1; i != m; ++i)
    now = now->next;
  while (now) {
    for (int i = 1; i != k; ++i)
      now = now->next;
    cout << now->pos << "-";
    prv = now->prv;
    prv->next = now->next;
    now->next->prv = prv;
    // cout << "delete: " << now->pos;
    if (now->next != now)
      delete (now);
    else {
      delete (now);
      break;
    }
    now = prv->next;
  }
  cout << endl;
}
int main(int argc, char **argv) {
  Josephu(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
}
