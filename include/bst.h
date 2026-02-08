#pragma once
#include "tree_iface.h"

/**
 * @brief Unbalanced Binary Search Tree (BST) implementation.
 * Average-case insert/search is O(log n); worst-case is O(n).
 */
class BstTree : public ICourseTree {
public:
    BstTree();
    ~BstTree() override;

    BstTree(const BstTree&) = delete;
    BstTree& operator=(const BstTree&) = delete;

    void insert(const Course& course) override;
    const Course* search(const std::string& courseId) const override;
    void inOrder(std::vector<const Course*>& out) const override;
    size_t size() const override;

private:
    struct Node {
        Course course;
        Node* left = nullptr;
        Node* right = nullptr;
        explicit Node(const Course& c) : course(c) {}
    };

    Node* root_;
    size_t count_;

    static void destroy(Node* node);
    static void inOrderRec(const Node* node, std::vector<const Course*>& out);
};
