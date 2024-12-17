#ifndef ORDER_H
#define ORDER_H

#include "client.h"
#include "book.h" //  Заменил Product на Book
#include <string>
#include <unordered_map>
#include <vector>

// order details attributes
struct OrderDetail {
    int bookId;
    int quantity;
    double subtotal;

    OrderDetail(int bookId, int quantity, double subtotal) :
        bookId(bookId), quantity(quantity), subtotal(subtotal) {}
};

// order attributes
struct Order {
    int id;
    int clientId;
    std::vector<OrderDetail> details;
    double total;

    Order(int id, int clientId) :
        id(id), clientId(clientId), total(0.0) {}

    Order() = default; // Конструктор по умолчанию
};

// --- Объявления функций ---

// Меню
void menu_orders(std::unordered_map<int, Client>& clientsMap, std::unordered_map<int, Book>& booksMap, std::unordered_map<int, Order>& ordersMap);

// Функции для работы с заказами
void insert_order(std::unordered_map<int, Client>& clientsMap, std::unordered_map<int, Book>& booksMap, std::unordered_map<int, Order>& ordersMap);
void print_list_orders(const std::unordered_map<int, Client>& clientsMap, std::unordered_map<int, Book>& booksMap, const std::unordered_map<int, Order>& ordersMap);
void print_order(const Order& order, const std::unordered_map<int, Client>& clientsMap, std::unordered_map<int, Book>& booksMap);
void deleteOrder(std::unordered_map<int, Order>& ordersMap);

// Функции для работы с деталями заказов
void insert_order_detail(Order& order, std::unordered_map<int, Book>& booksMap); 

// Функции для работы с файлами
void readOrdersFromFile(std::unordered_map<int, Order>& ordersMap, const std::string& filename);
void saveOrdersToFile(const std::unordered_map<int, Order>& ordersMap, const std::string& filename);
void readOrderDetailsFromFile(std::unordered_map<int, Order>& ordersMap, std::unordered_map<int, Book>& booksMap, const std::string& filename);
void saveOrderDetailsToFile(const std::unordered_map<int, Order>& ordersMap, const std::string& filename);

#endif