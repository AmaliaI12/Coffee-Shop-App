#ifndef ORDER_H
#define ORDER_H

#include "product.hpp"

// define item data type to associate product with number
typedef struct
{
    Product product;
    int numPcs;
} ITEM;

class Order
{
private:
    string clientName;
    vector<ITEM> items;
    float totalSum;

public:
    // constructor
    Order();

    // getters and setters
    void setClientName(string name);
    string getClientName();

    void setTotal(float sum);
    float getTotal();

    void setItems(vector<ITEM> it);
    vector<ITEM> getItems();

    void addItem(Product prod, int num);
    void calculateTotal();
};

#endif