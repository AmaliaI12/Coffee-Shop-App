#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <cstring>
#include <vector>
#include "product.hpp"

typedef struct{
    Product product;
    int numPcs;
}ITEM;

class Order {
private:
    vector<ITEM> items;
    float totalSum;
public:
    //constructor
    Order();

    //getters and setters
    void setTotal(float sum);
    float getTotal();

    void setItems(vector<ITEM> it);
    vector<ITEM> getItems();


    void addItem(Product prod, int num);
    void calculateTotal();

};

#endif