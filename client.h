#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <unordered_map>

// attributes
struct Client {
    int id;
    std::string name;
    int age; 
    double salary;
    const std::string& getName() const { return name; }
};

// methods
void menu_clients(std::unordered_map<int, Client>& clientsMap);
void insert_client(std::unordered_map<int, Client>& clientsMap);
void print_client(const Client& c);
void print_lst_clients(const std::unordered_map<int, Client>& clientsMap);
int search_client(const std::string& search_name, const std::unordered_map<int, Client>& clientsMap);
Client get_client(int id, const std::unordered_map<int, Client>& clientsMap);
void sort_by_names(std::unordered_map<int, Client>& clientsMap);
void update_client(const std::string& search_name, std::unordered_map<int, Client>& clientsMap);
void delete_client(const std::string& search_name, std::unordered_map<int, Client>& clientsMap);
int get_highest_salary(const std::unordered_map<int, Client>& clientsMap);

// функции для работы с файлами
void readClientsFromFile(std::unordered_map<int, Client>& clientsMap, const std::string& filename);
void saveClientsToFile(const std::unordered_map<int, Client>& clientsMap, const std::string& filename);

#endif