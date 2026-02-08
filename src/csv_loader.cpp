#include "csv_loader.h"
#include "utils.h"
#include <fstream>

bool loadCoursesFromCSV(const std::string& fileName,
                        std::unordered_map<std::string, Course>& outIndex,
                        std::vector<std::string>& warnings) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        warnings.push_back("ERROR: File could not be opened. Ensure the CSV is in the working directory.");
        return false;
    }

    std::string line;
    size_t lineNo = 0;

    while (std::getline(inputFile, line)) {
        lineNo++;
        line = trim(line);
        if (line.empty()) continue;

        std::vector<std::string> fields = splitCSVLine(line);
        if (fields.size() < 2) {
            warnings.push_back("Line " + std::to_string(lineNo) + ": invalid format (expected at least CourseId,Title). Skipped.");
            continue;
        }

        Course c;
        c.courseId = toUpper(trim(fields[0]));
        c.title = trim(fields[1]);

        if (c.courseId.empty() || c.title.empty()) {
            warnings.push_back("Line " + std::to_string(lineNo) + ": missing CourseId or Title. Skipped.");
            continue;
        }

        for (size_t i = 2; i < fields.size(); i++) {
            std::string prereqId = toUpper(trim(fields[i]));
            if (!prereqId.empty()) c.prereq.push_back(prereqId);
        }

        // Insert/overwrite by courseId
        outIndex[c.courseId] = c;
    }

    return true;
}
