#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

template <typename T>
class Node
{
public:
    T value;
    Node *next;
    Node *prev;
};

template <typename T>
class DoubleLinkedList
{
public:
    Node<T> *head;
    Node<T> *tail;
    int length;

    DoubleLinkedList()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // Add a value to the end of the list
    void append(T value)
    {
        auto *newNode = new Node<T>();
        newNode->value = value;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
            length++;
            return;
        }

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        length++;
    }

    // Add a value to the beginning of the list
    void prepend(T value)
    {
        auto *newNode = new Node<T>();
        newNode->value = value;
        newNode->next = head;
        newNode->prev = nullptr;

        if (head != nullptr)
        {
            head->prev = newNode;
        }

        head = newNode;

        if (tail == nullptr)
        {
            tail = newNode;
        }

        length++;
    }

    // Get a node by index
    Node<T> *getNode(int index)
    {
        Node<T> *temp = head;
        // maybe a better way?
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp;
    }

    // Get a value by index
    int getValue(int index)
    {
        return getNode(index)->value;
    }

    // Set a value by index
    int set(int index, T value)
    {
        auto *temp = getNode(index);
        temp->value = value;
        return temp->value;
    }

    // Find a value
    Node<T> *find(T value)
    {
        Node<T> *temp = head;
        while (temp != nullptr)
        {
            if (temp->value == value)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Reverse the linked list
    void reverse()
    {
        Node<T> *current = head;
        Node<T> *prev = nullptr;
        Node<T> *next = nullptr;

        while (current != nullptr)
        {
            next = current->next;
            current->next = prev;
            current->prev = next;
            prev = current;
            current = next;
        }

        // Swap the head and tail pointers
        Node<T> *temp = head;
        head = tail;
        tail = temp;
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const DoubleLinkedList<T> &list)
{
    os << "[ ";
    auto *temp = list.head;
    while (temp != nullptr)
    {
        os << temp->value << " ";
        temp = temp->next;
    }
    os << "]" << endl;
    return os;
}

void doIntegerTests()
{
    DoubleLinkedList<int> list{};

    const int size = 5;
    const int multiplier = 10;

    for (int i = 0; i < size; i++)
    {
        list.append(i * multiplier);
    }

    cout << "Original: " << list << endl;

    list.reverse();

    cout << "Reversed: " << list << endl;

    for (int i = 1; i < size; i++)
    {
        if (list.find(i * multiplier) == nullptr)
        {
            throw std::runtime_error("Could not find value " + std::to_string(i * multiplier));
        }
    }

    cout << "Found all values" << endl;
}

void doStringTests()
{
    DoubleLinkedList<string> list{};

    auto values = {"a", "b", "c", "d", "e"};
    for (auto value : values)
    {
        list.append(value);
    }
    cout << "Original: " << list << endl;
    list.reverse();
    cout << "Reversed: " << list << endl;

    const string target = "b";
    if (list.find(target) == nullptr)
    {
        throw std::runtime_error("Could not find value " + target);
    }

    cout << "Found target " << target << endl;
}

int main(int argc, char const *argv[])
{
    cout << "--- Integer Tests --- " << "\n\n";
    doIntegerTests();
    cout << "\n--- Done ---" << "\n\n";

    cout << "--- String Tests --- " << "\n\n";
    doStringTests();
    cout << "\n--- Done ---" << endl;

    return 0;
}
