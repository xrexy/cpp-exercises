#include <iostream>
#include <memory>

template <typename T>
class BinaryTreeNode
{
public:
    T data;
    std::unique_ptr<BinaryTreeNode<T>> left;
    std::unique_ptr<BinaryTreeNode<T>> right;

    BinaryTreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree
{
private:
    std::unique_ptr<BinaryTreeNode<T>> root;

    /// @brief A helper function to insert a new node
    /// @param node The node to insert
    /// @param val The value to insert
    void insertHelper(std::unique_ptr<BinaryTreeNode<T>> &node, T val)
    {
        if (!node)
        {
            node = std::make_unique<BinaryTreeNode<T>>(val);
        }

        else if (val < node->data)
        {
            insertHelper(node->left, val);
        }
        else
        {
            insertHelper(node->right, val);
        }
    }

    /// @brief A helper function to find a node
    /// @param node The node to search
    /// @param val The value to search for
    BinaryTreeNode<T> *findHelper(BinaryTreeNode<T> *node, T val) const
    {
        if (!node || node->data == val)
        {
            return node;
        }
        else if (val < node->data)
        {
            return findHelper(node->left.get(), val);
        }
        else
        {
            return findHelper(node->right.get(), val);
        }
    }

    /// @brief Helper function to find the minimum value node. Should always be on the left subtree
    /// @package node The node to start the search from
    BinaryTreeNode<T> *findMin(BinaryTreeNode<T> *node) const
    {
        while (node && node->left)
        {
            node = node->left.get();
        }
        return node;
    }

    /// @brief Helper function to remove a node
    /// @param node The node to remove
    /// @param val The value to remove
    std::unique_ptr<BinaryTreeNode<T>> removeHelper(std::unique_ptr<BinaryTreeNode<T>> node, T val)
    {
        if (!node)
            return nullptr;

        if (val < node->data)
        {
            node->left = removeHelper(std::move(node->left), val);
        }
        else if (val > node->data)
        {
            node->right = removeHelper(std::move(node->right), val);
        }
        else
        {
            // Node with only one child or no child
            if (!node->left)
            {
                return std::move(node->right);
            }
            else if (!node->right)
            {
                return std::move(node->left);
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            BinaryTreeNode<T> *temp = findMin(node->right.get());
            node->data = temp->data;
            node->right = removeHelper(std::move(node->right), temp->data);
        }
        return node;
    }

    /// @brief Helper function to print the tree (in-order traversal, recursive)
    /// @param node The node to print
    void inOrderHelper(BinaryTreeNode<T> *node) const
    {
        if (node)
        {
            inOrderHelper(node->left.get());
            std::cout << node->data << " ";
            inOrderHelper(node->right.get());
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    /// @brief Insert a new node
    /// @param val The value to insert
    void insert(T val)
    {
        insertHelper(root, val);
    }

    /// @brief Find a node
    /// @param val The value to find
    BinaryTreeNode<T> *find(T val) const
    {
        return findHelper(root.get(), val);
    }

    /// @brief Remove a node
    /// @param val The value to remove
    void remove(T val)
    {
        root = removeHelper(std::move(root), val);
    }

    /// @brief Print the tree (in-order traversal)
    void inOrder() const
    {
        inOrderHelper(root.get());
        std::cout << std::endl;
    }
};
