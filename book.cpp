   #include "book.h"
#include <cstdio>
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <unordered_map>

using namespace std;

// --- Функции для работы с файлами ---

void readBooksFromFile(std::unordered_map<int, Book>& booksMap, const std::string& filename) {
    FILE* inputFile = fopen(filename.c_str(), "r");
    if (!inputFile) {
        cerr << "Error" << filename << endl;
        return;
    }

    int id, year, categoryInt, stock;
    char author[100], title[100];
    double price;

    while (fscanf(inputFile, "%d %99s %99s %d %lf %d %d", &id, author, title, &stock, &price, &year, &categoryInt) == 7) {
        BookCategory category = static_cast<BookCategory>(categoryInt);
        booksMap[id] = Book{id, string(author), string(title), stock, price, year, category};
    }

    fclose(inputFile);
}

void saveBooksToFile(const std::unordered_map<int, Book>& booksMap, const std::string& filename) {
    FILE* outputFile = fopen(filename.c_str(), "w");
    if (!outputFile) {
        cerr << "Error" << filename << endl;
        return;
    }

    for (const auto& pair : booksMap) {
        fprintf(outputFile, "%d %s %s %d %.2f %d %d\n",
                pair.second.id,
                pair.second.author.c_str(),
                pair.second.title.c_str(),
                pair.second.stock,
                pair.second.price,
                pair.second.year,
                static_cast<int>(pair.second.category));
    }

    fclose(outputFile);
}

   // --- Функции меню и операций ---

    void menu_books(std::unordered_map<int, Book>& booksMap) {
       int opt;
       string search_title;
       int bookId;
       do {
           cout << left;
           cout << setw(20) << "\n --- MANAGMENT OF BOOKS ---" << endl;
           cout << "\nSelect an option from [1-8] according to the menu:" << endl;
           cout << "[1]. Insert book" << endl;
           cout << "[2]. Read list of books" << endl;
           cout << "[3]. Search book" << endl;
           cout << "[4]. Sort books" << endl; //  Изменено меню сортировки
           cout << "[5]. Update book" << endl;
           cout << "[6]. Delete book" << endl;
           cout << "[7]. Exit" << endl;
           cout << "------------------------------------------------" << endl;
           cout << "Enter option: ";
           cin >> opt;

           switch (opt) {
               case 1:     // insert
                   insert_book(booksMap);
                   break;
               case 2:     // read 
                   print_lst_books(booksMap);
                   break;
               case 3:     // search                
                   cout << "\n*** Search Book ***" << endl;
                   cout << "\nWrite the book title to search: ";
                   cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
                   getline(cin, search_title);

                
                   if (bookId != -1) {
                       cout << "\nSearched book: " << endl;
                       print_book(booksMap.at(bookId));
                   } else {
                       cout << "\nBook not found" << endl;
                   }
                   break;
               case 4: { // sort books
                   cout << "\nChoose sorting criteria:\n";
                   cout << "[1] Author\n";
                   cout << "[2] Title\n";
                   cout << "[3] Price\n";
                   cout << "[4] Year\n";
                   cout << "[5] Category\n";
                   cout << "Enter your choice: ";
                   int sortChoice;
                   cin >> sortChoice;

                   string sortBy;
                   switch (sortChoice) {
                       case 1: sortBy = "author"; break;
                       case 2: sortBy = "title"; break;
                       case 3: sortBy = "price"; break;
                       case 4: sortBy = "year"; break;
                       case 5: sortBy = "category"; break;
                       default: cout << "\nInvalid choice!\n"; continue; //  Возврат к меню сортировки
                   }

                   sort_books(booksMap, sortBy);
                   print_lst_books(booksMap);
                   break;
               }
               case 5:     // update book
                   cout << "\n*** Update Book ***" << endl;
                   cout << "\nWrite the book title to update: ";
                   cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
                   getline(cin, search_title);
                   update_book(search_title, booksMap);
                   break;
               case 6:     // delete book
                   cout << "\n*** Delete Book ***" << endl;
                   cout << "\nWrite the book title to delete: ";
                   cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
                   getline(cin, search_title);
                   delete_book(search_title, booksMap);
                   break;
               case 7:
                   cout << "Exiting to main menu..." << endl;
                   break;
               default:
                   cout << "\nInvalid option" << endl;
                   break;
           }
       } while (opt != 7);
   }

// insert new book
void insert_book(std::unordered_map<int, Book>& booksMap) {
    cout << "\n*** Insert new Book ***" << endl;

    int id;
    if (booksMap.empty()) {
        id = 1;
    } else {
        id = std::max_element(booksMap.begin(), booksMap.end(),
                            [](const auto& p1, const auto& p2) {
                                return p1.first < p2.first;
                            })->first + 1;
    }

    string author, title;
    int stock;
    double price;
    int year;
    int categoryInt;

    cout << "Author: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера
    getline(cin, author);

    cout << "Title: ";
    getline(cin, title);

    do {
        cout << "Stock: ";
        cin >> stock;
    } while (stock <= 0);

    do {
        cout << "Price: ";
        cin >> price;
    } while (price <= 0);

    do {
        cout << "Year (not less than 2000): ";
        cin >> year;
    } while (year < 2000);

    cout << "Category:\n";
    cout << "[1] Fantasy\n";
    cout << "[2] Science Fiction\n";
    cout << "[3] Romance\n";
    cout << "[4] History\n";
    cout << "Enter your choice: ";
    cin >> categoryInt;
    BookCategory category = static_cast<BookCategory>(categoryInt - 1); //  Коррекция индекса

    booksMap[id] = Book{id, author, title, stock, price, year, category};
    cout << "Book successfully added.\n";
}

// print list of books
void print_lst_books(const std::unordered_map<int, Book>& booksMap) {
    cout << "\n*** List of books ***" << endl;
    cout << left;
    cout << setw(10) << "ID" << setw(25) << "Author" << setw(30) << "Title" 
         << setw(10) << "Stock" << setw(10) << "Price" << setw(10) << "Year" 
         << setw(15) << "Category" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;

    for (const auto& pair : booksMap) {
        print_book(pair.second);
    }
}

// print 1 book
void print_book(const Book& b) {
    string categoryStr;
    switch (b.category) {
        case BookCategory::FANTASY: categoryStr = "Fantasy"; break;
        case BookCategory::SCIENCE_FICTION: categoryStr = "Science Fiction"; break;
        case BookCategory::ROMANCE: categoryStr = "Romance"; break;
        case BookCategory::HISTORY: categoryStr = "History"; break;
    }

    cout << setw(10) << b.id <<
            setw(25) << b.author <<
            setw(30) << b.title << 
            setw(10) << b.stock <<
            setw(10) << b.price <<
            setw(10) << b.year <<
            setw(15) << categoryStr << endl;
}

// search some book given the title
int search_book(const std::string& search_title, const std::unordered_map<int, Book>& booksMap) {
    for (const auto& pair : booksMap) {
        if (pair.second.title == search_title) {
            return pair.second.id; 
        }
    }
    return -1; 
}

// get 1 book
Book get_book(int id, const std::unordered_map<int, Book>& booksMap) {
    auto it = booksMap.find(id);
    if (it != booksMap.end()) {
        return it->second;
    } else {
        return Book{0, "", "", 0, 0.0, 0, BookCategory::FANTASY}; // Возвращаем "пустую" книгу
    }
}

// sort books  
void sort_books(std::unordered_map<int, Book>& booksMap, const std::string& sortBy) {
    // TODO:  Реализовать сортировку для unordered_map, 
    //        например, скопировать данные во временный вектор и отсортировать его
    cout << "\nФункция сортировки пока не реализована для unordered_map\n"; 
}

// update book
void update_book(const std::string& search_title, std::unordered_map<int, Book>& booksMap) {
    int id = search_book(search_title, booksMap);
    if (id != -1) {
        cout << "\n*** Update Book ***" << endl;

        auto& book = booksMap[id];

        cout << "Author (" << book.author << "): ";
        string author;
        getline(cin >> ws, author);
        if (!author.empty()) {
            book.author = author;
        }

        cout << "Title (" << book.title << "): ";
        string title;
        getline(cin, title);
        if (!title.empty()) {
            book.title = title;
        }

        do {
            cout << "Stock (" << book.stock << "): ";
            cin >> book.stock;
        } while (book.stock <= 0);

        do {
            cout << "Price (" << book.price << "): ";
            cin >> book.price;
        } while (book.price <= 0);

        do {
            cout << "Year (" << book.year << "): ";
            cin >> book.year;
        } while (book.year < 2000);

        // ... (обновление категории -  аналогично insert_book)

        cout << "\nBook updated!" << endl;
    } else {
        cout << "\nBook not found!" << endl;
    }    
}

// delete book
void delete_book(const std::string& search_title, std::unordered_map<int, Book>& booksMap) {
    int id = search_book(search_title, booksMap);
    if (id != -1) {
        booksMap.erase(id);
        cout << "\nBook deleted!" << endl;
    } else {
        cout << "\nBook not found!" << endl;
    }
}