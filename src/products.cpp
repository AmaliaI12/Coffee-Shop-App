#include "..\lib\product.hpp"

// constructor
Product::Product(string n, float cst, float pr, int num)
    : prodName(n), cost(cst), price(pr), pcs(num), inStock(isInStock()) {}

// default constructor
Product::Product()
    : prodName(""), cost(0), price(0), pcs(0), inStock(isInStock()) {}

// getters and setters
void Product::setName(string name)
{
    prodName = name;
}
string Product::getName()
{
    return prodName;
}

void Product::setCost(float cst)
{
    cost = cst;
}
float Product::getCost()
{
    return cost;
}

void Product::setPrice(float pr)
{
    price = pr;
}
float Product::getPrice()
{
    return price;
}

void Product::setPcs(int p)
{
    pcs = p;
    if (p == 0)
        inStock = false;
}
int Product::getPcs()
{
    return pcs;
}

bool Product::isInStock()
{
    if (pcs > 0)
        return true;
    return false;
}