#include "..\lib\product.hpp"

// constructor
Product::Product(string n, float pr, int num)
    : prodName(n), price(pr), pcs(num), inStock(isInStock()) {}

Product::Product()
    : prodName(""), price(0), pcs(0), inStock(isInStock()) {}

// getters and setters
void Product::setName(string name)
{
    prodName = name;
}
string Product::getName()
{
    return prodName;
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