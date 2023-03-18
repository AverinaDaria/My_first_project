#include <iostream>
#include <thread>
#include <future>
#include <vector>
using namespace std;

vector<long long> v;
long long M;

mutex mtx;

int f(int st, int end) {
    int n = end - st;
    if(n <= 2) {
        long long sum = 0;
        for(int i = st; i < end; i++) {
            sum += v[i];
            sum %= M;
        }
        return sum;
    }
    
    
    if(n % 3 == 0 || n % 3 == 1){
        auto t1 = async(launch::async, f, st, st + n / 3);
        t1.wait();
        int sum1 = t1.get();
        auto t2 = async(launch::async, f, st + n / 3, st + 2 * n / 3);
        t2.wait();
        int sum2 = t2.get();
        auto t3 = async(launch::async, f, st + 2 * n / 3, end);
        t3.wait();
        int sum3 = t3.get();
        return (sum1 + sum2 + sum3) % M; 
    }
    auto t1 = async(launch::async, f, st, st + 1 + n / 3);
    t1.wait();
    int sum1 = t1.get();
    auto t2 = async(launch::async, f, st + 1 + n / 3, st + 2 + 2 * n / 3);
    t2.wait();
    int sum2 = t2.get();
    auto t3 = async(launch::async, f, st + 2 + 2 * n / 3, end);
    t3.wait();
    int sum3 = t3.get();
    return (sum1 + sum2 + sum3) % M; 
}

int main() {
    int n;
    cin >> n >> M;
    v.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    
    cout << f(0, n);
}