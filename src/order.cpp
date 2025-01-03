#include "..\lib\order.hpp"
#include "..\lib\data.hpp"

// constructor
Order::Order()
{
    items.clear();
    totalSum = 0.0;
}

// getters and setters
void Order::setTotal(float sum)
{
    totalSum = sum;
}
float Order::getTotal()
{
    return totalSum;
}

void Order::setItems(vector<ITEM> it)
{
    items = it;
}
vector<ITEM> Order::getItems()
{
    return items;
}

void Order::calculateTotal() {
    totalSum = 0;
    for (ITEM item : items) {
        totalSum += item.product.getPrice() * item.numPcs;
    }
}

void Order::addItem(Product prod, int num) {
    items.push_back({prod, num});
}

