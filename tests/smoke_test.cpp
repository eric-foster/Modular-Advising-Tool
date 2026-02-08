// tests/smoke_test.cpp
// Minimal smoke test (no test framework) to validate basic behavior.
// Compile manually if desired:
//   g++ -std=c++17 -I../include ../src/avl.cpp ../src/benchmark.cpp ../src/bst.cpp ../src/csv_loader.cpp ../src/utils.cpp smoke_test.cpp -o smoke_test
//   ./smoke_test

#include <cassert>
#include <unordered_map>
#include <vector>
#include <string>
#include "bst.h"
#include "avl.h"
#include "course.h"
#include <iostream>

int main() {
    Course a{"CS100", "Intro", {}};
    Course b{"CS200", "DSA", {"CS100"}};
    Course c{"CS150", "Foundations", {}};

    BstTree bst;
    AvlTree avl;

    bst.insert(a); bst.insert(b); bst.insert(c);
    avl.insert(a); avl.insert(b); avl.insert(c);

    assert(bst.search("CS200") != nullptr);
    assert(avl.search("CS200") != nullptr);
    assert(bst.search("NOPE") == nullptr);
    assert(avl.search("NOPE") == nullptr);

    std::cout << "Smoke test passed.\n";

    return 0;
}
