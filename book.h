#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <unordered_map>
#include <vector>

// Enum для категорий книг
enum class BookCategory {
    FANTASY,
    SCIENCE_FICTION,
    ROMANCE,
    HISTORY
};

// attributes
struct Book {
    int id;
    std::string author;
    std::string title;
    int stock;
    double price;
    int year;
    BookCategory category;

    
    // Методы доступа к атрибутам
    const std::string& getName() const { return title; }
    int getQuantity() const { return stock; }
    double getPrice() const { return price; }
    void setQuantity(int newQuantity) { stock = newQuantity; }
};

// methods
void menu_books(std::unordered_map<int, Book>& booksMap);
void insert_book(std::unordered_map<int, Book>& booksMap);
void print_book(const Book& b);
void print_lst_books(const std::unordered_map<int, Book>& booksMap);
int search_book(const std::string& search_title, const std::unordered_map<int, Book>& booksMap);
Book get_book(int id, const std::unordered_map<int, Book>& booksMap);
void sort_books(std::unordered_map<int, Book>& booksMap,  // Добавил параметр для критерия сортировки
                  const std::string& sortBy);
void update_book(const std::string& search_title, std::unordered_map<int, Book>& booksMap);
void delete_book(const std::string& search_title, std::unordered_map<int, Book>& booksMap);
int get_cheapest_book(const std::unordered_map<int, Book>& booksMap);

// функции для работы с файлами
void readBooksFromFile(std::unordered_map<int, Book>& booksMap, const std::string& filename);
void saveBooksToFile(const std::unordered_map<int, Book>& booksMap, const std::string& filename);

#endif 