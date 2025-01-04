#ifndef DATA_H
#define DATA_H

#include <map>
#include <fstream>
#include <sstream>
#include "employee.hpp"
#include "order.hpp"
#include "product.hpp"

// using the singleton design pattern to manage the database
class DB
{
private:
    vector<Order> orders;
    map<string, Product> products;
    map<int, Employee> employees;
    map<string, int> loyalClients;

    // private static instance and constructor for singleton pattern
    static DB *instance;
    DB() {}

public:
    // delete the copy constructor
    DB(const DB &obj) = delete;

    static DB *getInstance();

    //getters and setters
    void setOrders(vector<Order> o);
    vector<Order> &getOrders();

    void setProducts(map<string, Product> prod);
    map<string, Product> &getProducts();

    void setEmployees(map<int, Employee> emp);
    map<int, Employee> &getEmployees();

    void setLoyalClients(map<string, int> cli);
    map<string, int> &getLoyalClients();

    // import data from files methods
    void importEmployees(string city);
    void importOrders(string city);
    void importProducts(string city);
    void importLoyalCostumers();

    // export data to files methods
    void exportEmployees(string city);
    void exportOrders(string city);
    void exportProducts(string city);
    void exportLoyalCostumers();
};

#endif