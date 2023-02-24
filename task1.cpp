#include <future>
#include <iostream>
#include <ranges>
#include <syncstream>
#include <thread>
#include <vector>
#include <algorithm>

using namespace std;

int main1() {
    auto fut = async(launch::async, []() {
        auto name = string {};
        cin >> name;
        return name;
    });
    fut.wait();
    cout << "Добро пожаловать!" << fut.get() << endl;
    return 0;
}
