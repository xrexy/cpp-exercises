#include <iostream>

class Node
{
public:
    int value;
    Node *next;
};

class DoubleLinkedList
{
public:
    Node *head;
    Node *tail;
    int length;

    DoubleLinkedList()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // Add a value to the end of the list
    void append(int value)
    {
        Node *newNode = new Node();
        newNode->value = value;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
            length++;
            return;
        }

        tail->next = newNode;
        tail = newNode;
        length++;
    }

    // Add a value to the beginning of the list
    void prepend(int value)
    {
        Node *newNode = new Node();
        newNode->value = value;
        newNode->next = head;
        head = newNode;
        length++;
    }

    // Print the list
    void print()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // Get a node by index
    Node *getNode(int index)
    {
        Node *temp = head;
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
    int set(int index, int value)
    {
        Node *temp = getNode(index);
        temp->value = value;
        return temp->value;
    }

    // Find a value
    Node *find(int value)
    {
        Node *temp = head;
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
};

int main(int argc, char const *argv[])
{
    DoubleLinkedList list{};

    const auto size = 50;
    for (int i = 0; i < size; i++)
    {
        list.append(i);
    }

    list.print();
    std::cout << "Length: " << list.length << "\n";

    std::cout << "Should be 6: " << list.find(5)->next->value << "\n";

    std::cout << "Should be 11: " << list.getValue(11) << "\n";
    std::cout << "Please be 16: " << list.getNode(16)->value << "\n";

    list.prepend(100);
    list.print();
    std::cout << "Length: " << list.length << "\n";

    std::cout << "Surely 15 now: " << list.getNode(16)->value << "\n";

    return 0;
}
