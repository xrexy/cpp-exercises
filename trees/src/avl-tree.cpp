#include <iostream>
#include <memory>

// AVLTreeNode definition with height information
template <typename T>
class AVLTreeNode
{
public:
    T data;
    int height;
    std::unique_ptr<AVLTreeNode<T>> left;
    std::unique_ptr<AVLTreeNode<T>> right;

    AVLTreeNode(T val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

// AVL Tree implementation
template <typename T>
class AVLTree
{
public:
    AVLTree() : root(nullptr) {}

    /// @brief Insert a new node
    /// @param val The value to insert
    void insert(T val)
    {
        root = insertHelper(std::move(root), val);
    }

    /// @brief Remove a node
    /// @param val The value of the node to remove
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

    /// @brief Find a node
    /// @param val The value of the node to find
    AVLTreeNode<T> *find(T val) const
    {
        return findHelper(root.get(), val);
    }

private:
    std::unique_ptr<AVLTreeNode<T>> root;

    /// @brief Get the height of the node
    /// @param node The node to get the height of
    int height(AVLTreeNode<T> *node) const
    {
        return node ? node->height : 0;
    }

    /// @brief Get the balance factor of the node
    /// @param node The node to get the balance factor of
    int getBalance(AVLTreeNode<T> *node) const
    {
        return node ? height(node->left.get()) - height(node->right.get()) : 0;
    }

    /// @brief Right rotate the subtree rooted with y
    /// @param y The node to rotate
    std::unique_ptr<AVLTreeNode<T>> rightRotate(std::unique_ptr<AVLTreeNode<T>> y)
    {
        std::unique_ptr<AVLTreeNode<T>> x = std::move(y->left);
        std::unique_ptr<AVLTreeNode<T>> T2 = std::move(x->right);

        x->right = std::move(y);
        x->right->left = std::move(T2);

        // Update heights (no idea what I wrote but it works)
        x->right->height = std::max(height(x->right->left.get()), height(x->right->right.get())) + 1;
        x->height = std::max(height(x->left.get()), height(x->right.get())) + 1;

        return x;
    }

    /// @brief Left rotate the subtree rooted with x
    /// @param x The node to rotate
    std::unique_ptr<AVLTreeNode<T>> leftRotate(std::unique_ptr<AVLTreeNode<T>> x)
    {
        std::unique_ptr<AVLTreeNode<T>> y = std::move(x->right);
        std::unique_ptr<AVLTreeNode<T>> T2 = std::move(y->left);

        y->left = std::move(x);
        y->left->right = std::move(T2);

        // Update heights (no idea what I wrote but it works)
        y->left->height = std::max(height(y->left->left.get()), height(y->left->right.get())) + 1;
        y->height = std::max(height(y->left.get()), height(y->right.get())) + 1;

        return y;
    }

    /// @brief Insert a new node and balance the tree
    /// @param node The node to insert at
    /// @param val The value to insert
    std::unique_ptr<AVLTreeNode<T>> insertHelper(std::unique_ptr<AVLTreeNode<T>> node, T val)
    {
        if (!node)
        {
            return std::make_unique<AVLTreeNode<T>>(val);
        }

        if (val < node->data)
        {
            node->left = insertHelper(std::move(node->left), val);
        }
        else if (val > node->data)
        {
            node->right = insertHelper(std::move(node->right), val);
        }
        else
        {
            return node;
        }

        // Update height of this ancestor node (1 + max(height(left), height(right)))
        node->height = 1 + std::max(height(node->left.get()), height(node->right.get()));

        int balance = getBalance(node.get());

        // Left Left Case
        if (balance > 1 && val < node->left->data)
        {
            return rightRotate(std::move(node));
        }

        // Right Right Case
        if (balance < -1 && val > node->right->data)
        {
            return leftRotate(std::move(node));
        }

        // Left Right Case
        if (balance > 1 && val > node->left->data)
        {
            node->left = leftRotate(std::move(node->left));
            return rightRotate(std::move(node));
        }

        // Right Left Case
        if (balance < -1 && val < node->right->data)
        {
            node->right = rightRotate(std::move(node->right));
            return leftRotate(std::move(node));
        }

        return node;
    }

    /// @brief Find the node with the minimum value (used in deletion)
    /// @param node The node to start the search from
    AVLTreeNode<T> *findMin(AVLTreeNode<T> *node) const
    {
        while (node && node->left)
        {
            node = node->left.get();
        }
        return node;
    }

    /// @brief Remove a node and balance the tree
    /// @param node The node to remove
    /// @param val The value to remove
    std::unique_ptr<AVLTreeNode<T>> removeHelper(std::unique_ptr<AVLTreeNode<T>> node, T val)
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
            if (!node->left || !node->right)
            {
                node = std::move((node->left) ? node->left : node->right);
            }
            else
            {
                AVLTreeNode<T> *temp = findMin(node->right.get());
                node->data = temp->data;
                node->right = removeHelper(std::move(node->right), temp->data);
            }
        }

        if (!node)
            return node;

        // Update height of the current node (1 + max(height(left), height(right)))
        node->height = 1 + std::max(height(node->left.get()), height(node->right.get()));

        int balance = getBalance(node.get());

        // Left Left Case
        if (balance > 1 && getBalance(node->left.get()) >= 0)
        {
            return rightRotate(std::move(node));
        }

        // Left Right Case
        if (balance > 1 && getBalance(node->left.get()) < 0)
        {
            node->left = leftRotate(std::move(node->left));
            return rightRotate(std::move(node));
        }

        // Right Right Case
        if (balance < -1 && getBalance(node->right.get()) <= 0)
        {
            return leftRotate(std::move(node));
        }

        // Right Left Case
        if (balance < -1 && getBalance(node->right.get()) > 0)
        {
            node->right = rightRotate(std::move(node->right));
            return leftRotate(std::move(node));
        }

        return node;
    }

    /// @brief In-order traversal of the tree
    /// @param node The node to start the traversal from
    void inOrderHelper(AVLTreeNode<T> *node) const
    {
        if (node)
        {
            inOrderHelper(node->left.get());
            std::cout << node->data << " ";
            inOrderHelper(node->right.get());
        }
    }

    /// @brief Find a node
    /// @param node The node to start the search from
    /// @param val The value to search for
    AVLTreeNode<T> *findHelper(AVLTreeNode<T> *node, T val) const
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
};
