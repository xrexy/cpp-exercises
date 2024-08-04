#include <iostream>
#include <string>

#include "shelf.h"

Shelf::Shelf()
{
    head = nullptr;
    tail = nullptr;
    length = 0;
}

Shelf::~Shelf()
{
    BookNode *temp = head;
    while (temp != nullptr)
    {
        BookNode *next = temp->next;
        delete temp;
        temp = next;
    }
}

void Shelf::append(const Book &book)
{
    BookNode *newBook = new BookNode();
    newBook->value = book;
    newBook->next = nullptr;

    if (head == nullptr)
    {
        head = newBook;
        tail = newBook;
        length++;
        return;
    }

    tail->next = newBook;
    tail = newBook;
    length++;
}

BookNode *Shelf::getNode(int index)
{
    BookNode *temp = head;
    // maybe a better way?
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp;
}

Book *Shelf::getBook(int index)
{
    return &getNode(index)->value;
}

void Shelf::set(int index, const Book &value)
{
    BookNode *node = getNode(index);
    node->value = value;
}

Book *Shelf::find(std::string title)
{
    BookNode *temp = head;
    while (temp != nullptr)
    {
        if (caseInsensitiveCompare(temp->value.title, title))
        {
            return &temp->value;
        }
        temp = temp->next;
    }
    return nullptr;
}

int Shelf::getLength()
{
    return length;
}

bool Shelf::caseInsensitiveCompare(const std::string &str1, const std::string &str2)
{
    if (str1.size() != str2.size())
    {
        return false;
    }
    for (size_t i = 0; i < str1.size(); ++i)
    {
        // TODO: looks sad
        if (std::tolower(static_cast<unsigned char>(str1[i])) != std::tolower(static_cast<unsigned char>(str2[i])))
        {
            return false;
        }
    }
    return true;
}
