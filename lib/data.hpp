#ifndef DATA_H
#define DATA_H

#include <map>
#include <fstream>
#include <sstream>
#include "employee.hpp"
#include "order.hpp"
#include "product.hpp"
#include "event.hpp"

// using the singleton design pattern to manage the database
class DB
{
private:
    vector<Order> orders;
    map<string, Product> products;
    map<int, Employee> employees;
    map<string, int> loyalClients;
    map<string, MusicEvent> musicEvents;
    map<string, TastingEvent> tastingEvents;
    // private static instance and constructor for singleton pattern
    static DB *instance;
    DB() {}

public:
    // delete the copy constructor
    DB(const DB &obj) = delete;

    static DB *getInstance();

    // getters and setters
    void setOrders(vector<Order> o);
    vector<Order> &getOrders();

    void setProducts(map<string, Product> prod);
    map<string, Product> &getProducts();

    void setEmployees(map<int, Employee> emp);
    map<int, Employee> &getEmployees();

    void setLoyalClients(map<string, int> cli);
    map<string, int> &getLoyalClients();

    map<string, MusicEvent> &getMusicEvents();
    map<string, TastingEvent> &getTastingEvents();

    // import data from files methods
    void importEmployees(string city);
    void importOrders(string city);
    void importProducts(string city);
    void importLoyalCostumers();
    void importEvents(string city);

    // export data to files methods
    void exportEmployees(string city);
    void exportOrders(string city);
    void exportProducts(string city);
    void exportLoyalCostumers();
    void exportEvents(string city);
};

#endif