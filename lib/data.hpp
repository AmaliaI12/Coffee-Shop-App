#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include "employee.hpp"
#include "orders.hpp"
#include "products.hpp"

class DB
{
private:
    vector<Order> orders;
    vector<Product> products;
    map<int, Employee> employees;
    static DB *instance;
    DB(){}
public:
    DB(const DB &obj) = delete;

    static DB *getInstance();

    void importEmployees(string city);
    void importOrders(string city);
    void importProducts(string city);

    void exportEmployees(string city);
    void exportOrders(string city);
    void exportProducts(string city);
    
};

#endif