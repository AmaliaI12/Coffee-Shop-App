#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class Product
{
private:
    string prodName;
    float price;
    int pcs;
    bool inStock;

public:
    //constructor
    Product(string n, float pr, int num);
    Product();

    //getters and setters
    void setName(string name);
    string getName();

    void setPrice(float pr);
    float getPrice();

    void setPcs(int p);
    int getPcs();

    bool isInStock();

};

#endif