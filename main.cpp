#include <iostream>
#include <unordered_map>
#include "client.h"
#include "book.h"
#include "order.h"

using namespace std;

void menu_master(int *opt);

int main() {
    unordered_map<int, Client> clientsMap;
    unordered_map<int, Book> booksMap;
    unordered_map<int, Order> ordersMap;

    // Чтение данных из файлов при запуске программы
    readClientsFromFile(clientsMap, "data/clients.txt");
    readBooksFromFile(booksMap, "data/books.txt");
    readOrdersFromFile(ordersMap, "data/orders.txt");
    readOrderDetailsFromFile(ordersMap, booksMap, "data/order_details.txt");

    int opt;
    char cont;

    do {
        menu_master(&opt);

        switch (opt) {
            case 1:     // clients
                menu_clients(clientsMap);
                break;
            case 2:     // books
                menu_books(booksMap);
                break;
            case 3:     // orders
                menu_orders(clientsMap, booksMap, ordersMap);
                break;
            default:
                cout << "\nInvalid option" << endl;
                break;
        }

        // Request to user continue or not
        cout << "\nDo you want continue [Y|N]? " << endl;
        cin >> cont;
    } while (cont == 'y' || cont == 'Y');

    cout << "The program is over!" << endl;

    // Сохранение данных в файлы перед выходом
    saveClientsToFile(clientsMap, "data/clients.txt");
    saveBooksToFile(booksMap, "data/books.txt");
    saveOrdersToFile(ordersMap, "data/orders.txt");
    saveOrderDetailsToFile(ordersMap, "data/order_details.txt");

    return 0;
}

void menu_master(int *opt) {
    cout << "-----------------------------------------------" << endl;
    cout << "*** LIBRARY SYSTEM ***" << endl; // Изменил название
    cout << "-----------------------------------------------" << endl;
    cout << "\nSelect an option from [1-3] according to the menu:" << endl;
    cout << "[1]. Management of Clients" << endl;
    cout << "[2]. Management of Books" << endl; // Изменил название
    cout << "[3]. Management of Orders" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Enter option: ";
    cin >> *opt;
    cout << endl;
}