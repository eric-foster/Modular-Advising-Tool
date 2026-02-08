//============================================================================
// Name        : Course Planner (Modular Enhanced)
// Author      : Eric Foster
// Version     : 2.1
// Description : Modular CS 300 artifact enhanced for CS 499.
//               - CSV parsing hardened (trim, normalize, safe skipping)
//               - Modular design for testability (separate tree + loader)
//               - Benchmark compares BST vs AVL search performance
//============================================================================

#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

#include "avl.h"
#include "benchmark.h"
#include "bst.h"
#include "csv_loader.h"
#include "utils.h"

using namespace std;

static void printCourseDetails(const Course& course) {
    cout << course.courseId << ", " << course.title << "\n";
    cout << "Prerequisites: ";
    if (course.prereq.empty()) {
        cout << "No prerequisites";
    } else {
        for (size_t i = 0; i < course.prereq.size(); i++) {
            cout << course.prereq[i] << (i + 1 < course.prereq.size() ? " " : "");
        }
    }
    cout << "\n\n";
}

static int readMenuChoice() {
    int choice;
    cout << "Enter selection: ";
    while (!(cin >> choice)) {
        cout << "Not a valid input. Try a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter selection: ";
    }
    return choice;
}

static size_t readPositiveSizeT(const string& prompt) {
    cout << prompt;
    size_t value = 0;
    while (!(cin >> value)) {
        cout << "Not a valid input. Enter a positive integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << prompt;
    }
    return value;
}

int main(int argc, char* argv[]) {
    string csvPath = (argc == 2) ? argv[1] : "CS 300 ABCU_Advising_Program_Input.csv";

    unordered_map<string, Course> index;
    vector<string> warnings;
    vector<string> ids; // normalized IDs for benchmarking

    // Two trees built from identical input for apples-to-apples comparison
    BstTree bst;
    AvlTree avl;

    bool loaded = false;

    cout << "Welcome to Course Planner.\n";

    int choice = 0;
    while (choice != 9) {
        cout << "\nMenu:\n";
        cout << "  1. Load Courses\n";
        cout << "  2. Print Schedule (AVL)\n";
        cout << "  3. Print Course (AVL)\n";
        cout << "  4. Benchmark Search (BST vs AVL)\n";
        cout << "  9. Exit\n";

        choice = readMenuChoice();

        if (choice == 1) {
            index.clear();
            warnings.clear();
            ids.clear();

            loaded = loadCoursesFromCSV(csvPath, index, warnings);
            if (!loaded) {
                for (const auto& w : warnings) cout << w << "\n";
                continue;
            }

            // Insert into both trees
            for (const auto& kv : index) {
                bst.insert(kv.second);
                avl.insert(kv.second);
            }

            ids.reserve(index.size());
            for (const auto& kv : index) ids.push_back(kv.first);
            sort(ids.begin(), ids.end());

            cout << avl.size() << " courses read\n";
            for (const auto& w : warnings) cout << w << "\n";
        }
        else if (choice == 2) {
            if (!loaded) {
                cout << "Please load courses first (option 1).\n";
                continue;
            }
            vector<const Course*> ordered;
            avl.inOrder(ordered);

            cout << "\nHere is a sample schedule:\n\n";
            for (const Course* c : ordered) {
                cout << c->courseId << ": " << c->title << " | ";
                if (c->prereq.empty()) cout << "No prerequisites";
                else {
                    for (size_t i = 0; i < c->prereq.size(); i++) {
                        cout << c->prereq[i] << (i + 1 < c->prereq.size() ? " " : "");
                    }
                }
                cout << "\n";
            }
        }
        else if (choice == 3) {
            if (!loaded) {
                cout << "Please load courses first (option 1).\n";
                continue;
            }
            cout << "What course do you want to know about?\n";
            string input;
            cin >> input;

            string courseId = toUpper(trim(input));
            const Course* found = avl.search(courseId);

            if (found) {
                printCourseDetails(*found);
            } else {
                cout << "Course Id " << courseId << " not found.\n\n";
            }
        }
        else if (choice == 4) {
            if (!loaded) {
                cout << "Please load courses first (option 1).\n";
                continue;
            }

            size_t iters = readPositiveSizeT("Iterations per courseId (e.g., 10000): ");
            runSearchBenchmark(bst, ids, iters, "BST");
            runSearchBenchmark(avl, ids, iters, "AVL");
        }
        else if (choice == 9) {
            // exit
        }
        else {
            cout << choice << " is not a valid menu option. Try again.\n";
        }
    }

    cout << "\nThank you for using the course planner. See you soon.\n";
    return 0;
}
