#include "bst.h"

BstTree::BstTree() : root_(nullptr), count_(0) {}

BstTree::~BstTree() {
    destroy(root_);
    root_ = nullptr;
    count_ = 0;
}

void BstTree::destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

void BstTree::insert(const Course& course) {
    if (!root_) {
        root_ = new Node(course);
        count_++;
        return;
    }

    Node* curr = root_;
    while (curr) {
        if (course.courseId < curr->course.courseId) {
            if (!curr->left) {
                curr->left = new Node(course);
                count_++;
                return;
            }
            curr = curr->left;
        } else if (course.courseId > curr->course.courseId) {
            if (!curr->right) {
                curr->right = new Node(course);
                count_++;
                return;
            }
            curr = curr->right;
        } else {
            // Duplicate ID: overwrite existing node data (no count change)
            curr->course = course;
            return;
        }
    }
}

const Course* BstTree::search(const std::string& courseId) const {
    const Node* curr = root_;
    while (curr) {
        if (courseId == curr->course.courseId) return &curr->course;
        curr = (courseId < curr->course.courseId) ? curr->left : curr->right;
    }
    return nullptr;
}

void BstTree::inOrderRec(const Node* node, std::vector<const Course*>& out) {
    if (!node) return;
    inOrderRec(node->left, out);
    out.push_back(&node->course);
    inOrderRec(node->right, out);
}

void BstTree::inOrder(std::vector<const Course*>& out) const {
    inOrderRec(root_, out);
}

size_t BstTree::size() const { return count_; }
