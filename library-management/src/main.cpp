#include <iostream>
#include <unordered_map>

#include "shelf.h"

class Library
{
public:
    std::unordered_map<u_int16_t, Shelf> shelves;

    Library(u_int16_t maxShelves)
    {
        maximumShelves = maxShelves;
    }

    void addBook(const Book &book)
    {
        auto idx = getShelfIndex(book.title);
        if (shelves.find(idx) == shelves.end())
        {
            shelves[idx] = Shelf();
        }

        auto foundBook = shelves[idx].find(book.title);
        if (foundBook == nullptr)
        {
            shelves[idx].append(book);
        }
    }

    Book *getBook(const std::string title)
    {
        auto idx = getShelfIndex(title);
        if (shelves.find(idx) == shelves.end())
        {
            shelves[idx] = Shelf();
        }

        return shelves[idx].find(title);
    }

private:
    u_int16_t maximumShelves = 50;

    u_int16_t getShelfIndex(const std::string str)
    {
        return str.length() % maximumShelves;
    }

    // TODO fix
    // Shelf &getShelf(u_int16_t idx)
    // {
    //     // If the shelf doesn't exist, create it
    //     if (shelves.find(idx) == shelves.end())
    //     {
    //         shelves[idx] = Shelf();
    //     }

    //     return shelves[idx];
    // };
};

int main(int argc, char const *argv[])
{
    Library library{5};
    library.addBook({100, "The Great Gatsby", "F. Scott Fitzgerald"});
    library.addBook({102, "The Catcher in the Rye", "J. D. Salinger"});
    library.addBook({200, "The Lord of the Rings", "J. R. R. Tolkien"});
    library.addBook({300, "The Hobbit", "J. R. R. Tolkien"});
    library.addBook({400, "Walking Dead", "Frank Darabont"});

    std::cout << "Shelves: " << std::to_string(library.shelves.size()) << std::endl;

    auto foundBook = library.getBook("The Great Gatsby");
    if (foundBook != nullptr)
    {
        std::cout << foundBook->title << " by " << foundBook->author << " has " << std::to_string(foundBook->pages) << " pages" << std::endl;
    }
    return 0;
}
