#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include "employee.hpp"
#include "order.hpp"
#include "product.hpp"

// Using the singleton design pattern to manage the database

class DB
{
private:
    vector<Order> orders;
    map<string, Product> products;
    map<int, Employee> employees;
    map<string,int> loyalClients;
    static DB *instance;
    DB() {}

public:
    DB(const DB &obj) = delete;

    static DB *getInstance();

    void setOrders(vector<Order> o);
    vector<Order> &getOrders();

    void setProducts(map<string, Product> prod);
    map<string, Product> &getProducts();

    void setEmployees(map<int, Employee> emp);
    map<int, Employee> &getEmployees();

    void setLoyalClients(map<string, int> cli);
    map<string, int> &getLoyalClients();

    //import methods
    void importEmployees(string city);
    void importOrders(string city);
    void importProducts(string city);
    void importLoyalCostumers();

    //export methods
    void exportEmployees(string city);
    void exportOrders(string city);
    void exportProducts(string city);
    void exportLoyalCostumers();
};

#endif