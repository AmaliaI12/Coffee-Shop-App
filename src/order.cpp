#include "../lib/order.hpp"
#include "../lib/data.hpp"

// default constructor
Order::Order()
{
    items.clear();
    totalSum = 0.0;
}

// getters and setters
void Order::setClientName(string name)
{
    clientName = name;
}

string Order::getClientName()
{
    return clientName;
}

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

void Order::calculateTotal()
{
    //calculate the total for the items
    totalSum = 0;
    for (ITEM item : items)
    {
        totalSum += item.product.getPrice() * item.numPcs;
    }
}

void Order::addItem(Product prod, int num)
{
    // substract the sold items from the stock
    DB::getInstance()->getProducts().at(prod.getName()).setPcs(prod.getPcs() - num);
    
    //add item to the order
    items.push_back({prod, num});
}
