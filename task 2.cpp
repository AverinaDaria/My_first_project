#include <future>
#include <iostream>
#include <ranges>
#include <syncstream>
#include <thread>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
constexpr T fact(T n, T accum = 1) {
    return n <= 1 ? accum : fact(n - 1, n * accum);
}

static_assert(fact(4) == 24);

int main2() {
    size_t n, s;
    cin >> n >> s;
    srand(s);
    using fact_t = uint64_t;
    auto nums
        = views::iota(0)
        | views::take(n)
        | views::transform([](auto) { return rand() % 100 + 1; })
        | views::transform([](auto r) {
                return jthread([r]() {
                    osyncstream(cout)
                        << r
                        << " : "
                        << fact<fact_t>(static_cast<fact_t>(r))
                        << '\n'
                        ;
                });
            })
        ;
    auto waiters = vector<jthread>();
    ranges::copy(
        nums,
        back_inserter(waiters)
    );
    return 0;
}
