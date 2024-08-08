#include <iostream>
#include "binary-tree.cpp"
#include "avl-tree.cpp"

void doBinaryTreeTests()
{
    BinaryTree<int> tree;

    // Insert nodes
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    // Print the tree
    std::cout << "In-order traversal: ";
    tree.inOrder();

    // Find a node
    int target = 40;
    auto node = tree.find(target);
    if (node)
    {
        std::cout << "Node " << target << " found.\n";
    }
    else
    {
        std::cout << "Node " << target << " not found.\n";
    }

    // Remove a node
    tree.remove(20);
    std::cout << "In-order traversal after removing 20: ";
    tree.inOrder();

    tree.remove(30);
    std::cout << "In-order traversal after removing 30: ";
    tree.inOrder();

    tree.remove(50);
    std::cout << "In-order traversal after removing 50: ";
    tree.inOrder();
}

void doAVLTreeTests()
{
    AVLTree<int> tree;

    // Insert nodes
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    // Print the tree (in-order traversal)
    std::cout << "In-order traversal: ";
    tree.inOrder();

    int target = 30;
    auto node = tree.find(target);
    if (node)
    {
        std::cout << "Node " << target << " found.\n";
    }
    else
    {
        std::cout << "Node " << target << " not found.\n";
    }

    // Remove a node and print the tree
    tree.remove(20);
    std::cout << "In-order traversal after removing 20: ";
    tree.inOrder();
}

int main(int argc, char const *argv[])
{
    std::cout << "\n\nRunning Binary Tree tests...\n";
    doBinaryTreeTests();

    std::cout << "\n\nRunning AVL Tree tests...\n";
    doAVLTreeTests();

    std::cout << "\n\nAll tests finished!" << std::endl;

    return 0;
}
