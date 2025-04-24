// // This is a personal academic project. Dear PVS-Studio, please check it.
// // PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// #include <iostream>
// #include <my_vector.h>
// #include <string>
// #include <vector>
//
// int main() {
//     // my_vector<my_vector<....>>
//     // v.push_back(v.back())
//     // The container has to be suitable for usage with adapter of type std::back_inserter.
//     my_vector<std::pair<int, std::string>> vec;
//     vec.emplace_back(42, "answer");
//
//     std::vector<int> std_vec = {1, 2, 3, 4};
//     my_vector<int> myvec(std_vec.begin(), std_vec.end());
//
//     for (auto x : myvec) std::cout << x << " ";  // Output: 1 2 3 4
//
//     return 0;
// }

#include <iostream>
#include <cassert>
#include "my_vector.h"
#include <string>
#include <vector>

void test_constructors() {
    my_vector<int> v1;
    assert(v1.is_empty());

    my_vector<int> v2(5);
    assert(v2.size() == 5);

    // my_vector<int> v3(3, 42);
    // assert(v3.size() == 3);
    // assert(v3[0] == 42 && v3[1] == 42 && v3[2] == 42);

    my_vector<int> v4 = {1, 2, 3};
    assert(v4.size() == 3);
    assert(v4[1] == 2);

    my_vector<int> v5(v4);
    assert(v5 == v4);

    my_vector<int> v6(std::move(v5));
    assert(v6 == v4);
}

void test_assignment() {
    my_vector<int> v1 = {1, 2, 3};
    my_vector<int> v2;
    v2 = v1;
    assert(v2 == v1);

    my_vector<int> v3;
    v3 = {4, 5};
    assert(v3[0] == 4);

    my_vector<int> v4;
    v4 = std::move(v3);
    assert(v4[1] == 5);
}

void test_accessors() {
    my_vector<int> v = {7, 8, 9};
    assert(v.front() == 7);
    assert(v.back() == 9);
    assert(v[1] == 8);
    try {
        v.at(5);
        assert(false);
    } catch (const std::out_of_range &) {
        assert(true);
    }
}

void test_modifiers() {
    my_vector<int> v;
    v.push_back(1);
    v.push_back(2);
    assert(v.size() == 2);
    assert(v.back() == 2);

    v.pop_back();
    assert(v.size() == 1);
    assert(v.back() == 1);

    v.resize(5, 100);
    assert(v.size() == 5);
    assert(v[4] == 100);

    v.shrink_to_fit();

    v.clear();
    assert(v.is_empty());
}

void test_insert_erase() {
    my_vector<int> v = {1, 2, 3};
    v.insert(v.begin() + 1, 99);
    assert(v[1] == 99);

    my_vector<int> range = {5, 6};
    v.insert(v.begin(), range.begin(), range.end());
    assert(v[0] == 5);
    assert(v[1] == 6);

    v.erase(v.begin() + 1);
    assert(v[1] == 5);

    v.erase(v.begin(), v.begin() + 2);
    assert(v[0] == 1);
}

void test_iterators() {
    my_vector<int> v = {10, 20, 30};
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }
    assert(sum == 60);

    auto r_it = v.rbegin();
    assert(*r_it == 30);
    ++r_it;
    assert(*r_it == 20);
}

int main() {
    test_constructors();
    test_assignment();
    test_accessors();
    test_modifiers();
    test_insert_erase();
    test_iterators();

    std::cout << "All tests passed successfully.\n";
    return 0;
}
