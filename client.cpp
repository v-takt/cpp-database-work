#include "client.h"
#include <cstdio>
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <unordered_map>

using namespace std;

// --- Функции для работы с файлами ---

void readClientsFromFile(std::unordered_map<int, Client>& clientsMap, const std::string& filename) {
    FILE* inputFile = fopen(filename.c_str(), "r");
    if (!inputFile) {
        cerr << "Error" << filename << endl;
        return;
    }

    int id, age;
    char name[100]; // assuming the name won't exceed 99 characters
    double salary;

    while (fscanf(inputFile, "%d %99s %d %lf", &id, name, &age, &salary) == 4) {
        clientsMap[id] = Client{id, string(name), age, salary};
    }

    fclose(inputFile);
}

void saveClientsToFile(const std::unordered_map<int, Client>& clientsMap, const std::string& filename) {
    FILE* outputFile = fopen(filename.c_str(), "w");
    if (!outputFile) {
        cerr << "Error" << filename << endl;
        return;
    }

    for (const auto& pair : clientsMap) {
        fprintf(outputFile, "%d %s %d %.2f\n",
                pair.second.id,
                pair.second.name.c_str(),
                pair.second.age,
                pair.second.salary);
    }

    fclose(outputFile);
}

   // --- Функции меню и операций ---

void menu_clients(std::unordered_map<int, Client>& clientsMap) {
       int opt;
       string search_name;

       do {
           cout << left;    
           cout << setw(20) << "\n --- MANAGMENT OF CLIENTS ---" << endl;
           cout << "\nSelect an option from [1-5] according to the menu:" << endl;
           cout << "[1]. Insert client" << endl;
           cout << "[2]. Read list of clients" << endl;
           cout << "[3]. Update client" << endl; 
           cout << "[4]. Delete client" << endl; 
           cout << "[5]. Exit" << endl;
           cin >> opt;
           switch (opt) {
               case 1:     // insert
                   insert_client(clientsMap);
                   break;
               case 2:     // read 
                   print_lst_clients(clientsMap);
                   break;
               case 3:     // update client
                   cout << "\n*** Update Client ***" << endl;
                   cout << "\nWrite the client name to update: ";
                   cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
                   getline(cin, search_name); // Считывание строки с пробелами
                   update_client(search_name, clientsMap);
                   break;
               case 4:     // delete client
                   cout << "\n*** Delete Client ***" << endl;
                   cout << "\nWrite the client name to delete: ";
                   cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
                   getline(cin, search_name); // Считывание строки с пробелами
                   delete_client(search_name, clientsMap);
                   break;
               case 5:
                   cout << "Exiting to main menu..." << endl;
                   break;
               default:
                   cout << "\nInvalid option" << endl;
                   break;
           }
       } while (opt != 5);    
   }

   // insert new client
   void insert_client(std::unordered_map<int, Client>& clientsMap) {
       cout << "\n*** Insert new Client ***" << endl;

       int id;
       if (clientsMap.empty()) {
           id = 1;
       } else {
           id = std::max_element(clientsMap.begin(), clientsMap.end(),
                               [](const auto& p1, const auto& p2) {
                                   return p1.first < p2.first;
                               })->first + 1;
       }

       string name;
       int age;
       double salary;

       cout << "Name: ";
       cin >> name;

       do {
           cout << "Age: ";
           cin >> age;
       } while (age <= 0);

       do {
           cout << "Salary: ";
           cin >> salary;
       } while (salary < 20000 || salary > 500000);

       clientsMap[id] = Client{id, name, age, salary};
       cout << "Client successfully added.\n";
   }
 
   // print list of clients
void print_lst_clients(const std::unordered_map<int, Client>& clientsMap) {
    cout << "\n*** List of clients ***" << endl;
    cout << left;
    cout << setw(10) << "ID" << setw(15) << "Name" << setw(10) << "Age"
         << setw(10) << "Salary" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    for (const auto& pair : clientsMap) {
        print_client(pair.second);
    }
}

// print 1 client
void print_client(const Client& c) {
    cout << setw(10) << c.id <<
         setw(15) << c.name <<
         setw(10) << c.age <<
         setw(10) << c.salary << endl;
}

// search some client given the name
int search_client(const std::string& search_name, const std::unordered_map<int, Client>& clientsMap) {
    for (const auto& pair : clientsMap) {
        if (pair.second.name == search_name) {
            return pair.second.id; // Возвращаем ID клиента
        }
    }
    return -1; // Клиент не найден
}

// get 1 client
Client get_client(int id, const std::unordered_map<int, Client>& clientsMap) {
    auto it = clientsMap.find(id);
    if (it != clientsMap.end()) {
        return it->second;
    } else {
        return Client{-1, "", 0, 0.0}; // Возвращаем "пустого" клиента
    }
}

// update client
void update_client(const std::string& search_name, std::unordered_map<int, Client>& clientsMap) {
    int id = search_client(search_name, clientsMap);
    if (id != -1) {
        cout << "\n*** Update Client ***" << endl;

        auto& client = clientsMap[id];

        cout << "Name (" << client.name << "): ";
        string name;
        getline(cin >> ws, name); // Считываем строку с пробелами
        if (!name.empty()) {
            client.name = name;
        }

        do {
            cout << "Age (" << client.age << "): ";
            cin >> client.age;
        } while (client.age <= 0);

        do {
            cout << "Salary (" << client.salary << "): ";
            cin >> client.salary;
        } while (client.salary < 20000 || client.salary > 500000);

        cout << "\nClient updated!" << endl;
    } else {
        cout << "\nClient not found!" << endl;
    }    
}

// delete client
void delete_client(const std::string& search_name, std::unordered_map<int, Client>& clientsMap) {
    int id = search_client(search_name, clientsMap);
    if (id != -1) {
        clientsMap.erase(id);
        cout << "\nClient deleted!" << endl;
    } else {
        cout << "\nClient not found" << endl;
    }
}
