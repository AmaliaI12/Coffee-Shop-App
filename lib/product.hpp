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
    float cost;
    float price;
    int pcs;
    bool inStock;

public:
    //constructor
    Product(string n,float cst, float pr, int num);
    Product();

    //getters and setters
    void setName(string name);
    string getName();

    void setCost(float cst);
    float getCost();

    void setPrice(float pr);
    float getPrice();

    void setPcs(int p);
    int getPcs();

    bool isInStock();

};

#endif