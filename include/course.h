#pragma once
#include <string>
#include <vector>

/**
 * @brief Represents a single course record loaded from the advising CSV.
 */
struct Course {
    std::string courseId;               // e.g., "CS200"
    std::string title;                  // e.g., "Data Structures"
    std::vector<std::string> prereq;    // optional prerequisites (course IDs)
};
