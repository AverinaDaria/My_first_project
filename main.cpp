#include <iostream>
#include "Queue.h"
using namespace std;

int main() {
  Queue q = *new Queue();
  const int len = 15;
  for (int i = 0; i < len; i++) {
    q.put(i);
  }
  cout << q.size() << '\n';
  for (int i = 0; i < len; i++) {
    cout << q.pop() << ' ';
  }
  cout << '\n';
  return 0;
}
