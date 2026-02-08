#pragma once
#include "tree_iface.h"

/**
 * @brief Self-balancing AVL Tree implementation.
 * Insert/search are O(log n) in worst case via rotations to maintain balance.
 */
class AvlTree : public ICourseTree {
public:
    AvlTree();
    ~AvlTree() override;

    AvlTree(const AvlTree&) = delete;
    AvlTree& operator=(const AvlTree&) = delete;

    void insert(const Course& course) override;
    const Course* search(const std::string& courseId) const override;
    void inOrder(std::vector<const Course*>& out) const override;
    size_t size() const override;

private:
    struct Node {
        Course course;
        Node* left = nullptr;
        Node* right = nullptr;
        int height = 1;
        explicit Node(const Course& c) : course(c) {}
    };

    Node* root_;
    size_t count_;

    static void destroy(Node* node);
    static int h(Node* n);
    static void updateHeight(Node* n);
    static int balanceFactor(Node* n);

    static Node* rotateLeft(Node* x);
    static Node* rotateRight(Node* y);
    static Node* rebalance(Node* node);

    static Node* insertRec(Node* node, const Course& course, bool& inserted);
    static const Node* searchRec(const Node* node, const std::string& courseId);
    static void inOrderRec(const Node* node, std::vector<const Course*>& out);
};
