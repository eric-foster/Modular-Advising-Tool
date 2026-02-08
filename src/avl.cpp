#include "avl.h"
#include <algorithm>

AvlTree::AvlTree() : root_(nullptr), count_(0) {}

AvlTree::~AvlTree() {
    destroy(root_);
    root_ = nullptr;
    count_ = 0;
}

void AvlTree::destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

int AvlTree::h(Node* n) { return n ? n->height : 0; }

void AvlTree::updateHeight(Node* n) {
    if (!n) return;
    n->height = 1 + std::max(h(n->left), h(n->right));
}

int AvlTree::balanceFactor(Node* n) {
    return n ? (h(n->left) - h(n->right)) : 0;
}

AvlTree::Node* AvlTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

AvlTree::Node* AvlTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

AvlTree::Node* AvlTree::rebalance(Node* node) {
    updateHeight(node);
    int bf = balanceFactor(node);

    // Left heavy
    if (bf > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left); // LR
        }
        return rotateRight(node); // LL
    }

    // Right heavy
    if (bf < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right); // RL
        }
        return rotateLeft(node); // RR
    }

    return node;
}

AvlTree::Node* AvlTree::insertRec(Node* node, const Course& course, bool& inserted) {
    if (!node) {
        inserted = true;
        return new Node(course);
    }

    if (course.courseId < node->course.courseId) {
        node->left = insertRec(node->left, course, inserted);
    } else if (course.courseId > node->course.courseId) {
        node->right = insertRec(node->right, course, inserted);
    } else {
        // Duplicate ID: overwrite (no count change)
        node->course = course;
        inserted = false;
        return node;
    }

    return rebalance(node);
}

void AvlTree::insert(const Course& course) {
    bool inserted = false;
    root_ = insertRec(root_, course, inserted);
    if (inserted) count_++;
}

const AvlTree::Node* AvlTree::searchRec(const Node* node, const std::string& courseId) {
    const Node* curr = node;
    while (curr) {
        if (courseId == curr->course.courseId) return curr;
        curr = (courseId < curr->course.courseId) ? curr->left : curr->right;
    }
    return nullptr;
}

const Course* AvlTree::search(const std::string& courseId) const {
    const Node* n = searchRec(root_, courseId);
    return n ? &n->course : nullptr;
}

void AvlTree::inOrderRec(const Node* node, std::vector<const Course*>& out) {
    if (!node) return;
    inOrderRec(node->left, out);
    out.push_back(&node->course);
    inOrderRec(node->right, out);
}

void AvlTree::inOrder(std::vector<const Course*>& out) const {
    inOrderRec(root_, out);
}

size_t AvlTree::size() const { return count_; }
