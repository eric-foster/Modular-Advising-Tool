#include "benchmark.h"
#include <chrono>
#include <iomanip>
#include <iostream>

void runSearchBenchmark(const ICourseTree& tree,
                        const std::vector<std::string>& ids,
                        size_t iterationsPerId,
                        const std::string& label) {
    if (ids.empty()) {
        std::cout << "Benchmark: no course IDs loaded.\n";
        return;
    }
    if (iterationsPerId == 0) iterationsPerId = 1;

    using clock = std::chrono::high_resolution_clock;

    size_t totalOps = 0;

    // Prevent the compiler from optimizing the loop away
    volatile std::uintptr_t sink = 0;

    auto start = clock::now();

    for (const auto& id : ids) {
        for (size_t i = 0; i < iterationsPerId; i++) {
            const Course* found = tree.search(id);
            sink ^= reinterpret_cast<std::uintptr_t>(found);
            totalOps++;
        }
    }

    auto end = clock::now();

    auto totalUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    double avgUs = static_cast<double>(totalUs) / static_cast<double>(totalOps);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "\n" << label << " Benchmark Results\n";
    std::cout << "  Total searches: " << totalOps << "\n";
    std::cout << "  Total time (us): " << totalUs << "\n";
    std::cout << "  Avg time per search (us): " << avgUs << "\n";

    // Use sink so it isn't "unused"
    if (sink == 0xFFFFFFFF) std::cout << "";
}

