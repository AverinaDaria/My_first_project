#include <array>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

long long norm(long long d, long long mod) {
  return ((d % mod) + mod) % mod;
}

void add(long long a, long long b, long long mod) {
    r = norm(norm(a, mod) + norm(b, mod), mod);
    thread t1(add, a, b, mod);
    t1.join();
    return;
}

int main() {
  int n;
  cin >> n;
  vector<long long> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  long long m;
  cin >> m;
  long long sum = 0;
  for (const auto num : a) {
    sum = add(sum, num, m);
  };
  cout << sum << '\n';
  return 0;
}






