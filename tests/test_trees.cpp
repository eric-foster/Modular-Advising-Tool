#include <iostream>
#include <vector>
#include "avl.h"
#include "bst.h"
#include "utils.h"
#include <assert.h>

static Course makeCourse(const std::string& id, const std::string& title) {
    Course c;
    c.courseId = toUpper(id);
    c.title = title;
    return c;
}

int main() {
    {
        BstTree bst;
        AvlTree avl;

        // Insert in sorted order to create a worst-case unbalanced BST.
        std::vector<Course> courses = {
            makeCourse("CS100", "Intro"),
            makeCourse("CS200", "Intermediate"),
            makeCourse("CS300", "Advanced"),
            makeCourse("CS400", "Capstone")
        };

        for (const auto& c : courses) {
            bst.insert(c);
            avl.insert(c);
        }

        assert(bst.size() == 4);
        assert(avl.size() == 4);

        // Find checks
        assert(bst.search("CS300") != nullptr);
        assert(avl.search("CS300") != nullptr);
        assert(bst.search("CS999") == nullptr);
        assert(avl.search("CS999") == nullptr);

        // Overwrite check
        Course updated = makeCourse("CS200", "Intermediate II");
        bst.insert(updated);
        avl.insert(updated);
        assert(bst.search("CS200")->title == "Intermediate II");
        assert(avl.search("CS200")->title == "Intermediate II");
    }

    std::cout << "All tests passed.\n";
    return 0;
}
