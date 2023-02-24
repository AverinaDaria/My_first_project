#include <chrono>
#include <cassert>
#include <iomanip>
#include <fstream>
#include <numeric>
#include <execution>
#include <latch>
using namespace std;

uint32_t task3(vector<uint32_t> const& nums, const size_t M) {
    size_t thread_count = thread::hardware_concurrency();
    atomic_uint32_t accum = 0;
    auto latch = latch(thread_count);
    atomic_uint32_t index = 0;

    auto fn = [&]() {
        uint32_t accum_local = 0;
        while (true) {
            auto idx_from = index.fetch_add(M);
            if (idx_from >= nums.size()) {
                accum.fetch_xor(accum_local, memory_order_relaxed);
                latch.count_down();
                return;
            }
            auto to = min(M, nums.size() - idx_from);
            for (size_t i = 0; i < to; i++) {
                accum_local ^= nums[idx_from + i];
            }
        }
    };
    auto threads = vector<jthread>();
    threads.reserve(thread_count);
    for (size_t i = 0; i < thread_count; i++) {
        threads.emplace_back(fn);
    }

    latch.wait();

    auto res = accum.load(memory_order_relaxed);
    assert(res == reduce(execution::par_unseq, nums.begin(), nums.end(), 0, bit_xor<> {}));
    return res;
}

int main() {
    auto f = ifstream("input.txt");
    assert(f.is_open());
    size_t n;
    f >> n;
    auto nums = vector<uint32_t>();
    nums.reserve(n);
    ranges::copy(
        ranges::istream_view<uint32_t>(f) | views::take(n),
        back_inserter(nums)
    );

    for (size_t m = 16; m < 4096; m += 16) {
        auto s = chrono::system_clock::now();
        task3(nums, m);
        auto e = chrono::system_clock::now();
        std::cout
            << m
            << ","
            << chrono::duration_cast<chrono::microseconds>(e - s).count()
            << endl
            ;
    }

    return 0;
}

// Copyright (C) 2007-2015 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file bits/c++0x_warning.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{iosfwd}
 */

#ifndef _CXX0X_WARNING_H
#define _CXX0X_WARNING_H 1

#if __cplusplus < 201103L
#error This file requires compiler and library support for the \
ISO C++ 2011 standard. This support is currently experimental, and must be \
enabled with the -std=c++11 or -std=gnu++11 compiler options.
#endif

#endif
