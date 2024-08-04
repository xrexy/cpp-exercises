#ifndef SHELF_H
#define SHELF_H

#include <string>

struct Book
{
    int pages;
    std::string title;
    std::string author;
};

struct BookNode
{
    BookNode *next;
    Book value;
};

class Shelf
{
public:
    Shelf();
    ~Shelf();

    // Add a value to the end of the list
    void append(const Book &book);

    // Get a value by index
    Book *getBook(int index);

    // Set a value by index
    void set(int index, const Book &value);

    // Find a value
    Book *find(std::string title);

    // Get the length
    int getLength();

private:
    BookNode *head;
    BookNode *tail;
    int length;

    // Get a node by index
    BookNode *getNode(int index);

    // Case insensitive string comparison
    bool caseInsensitiveCompare(const std::string &str1, const std::string &str2);
};

#endif // SHELF_H
