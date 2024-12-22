#include "lib\products.hpp"

// Product Class Implementation
Product::Product(string n, float pr, int num)
    : name(n), price(pr), numItems(num), inStock(num > 0) {}

void Product::isInStock()
{
    if (inStock)
        cout << name << " is in stock." << endl;
    else
        cout << name << " is out of stock." << endl;
}

// Coffee Class Implementation
Coffee::Coffee(string n, float pr, int num, string cat, float disc, int cal, string milk, int shots, string syrup, bool isIced)
    : Product(n, pr, num), milkType(milk), espressoShots(shots), flavouredSyrup(syrup), iced(isIced), hasFoam(true) {}

void Coffee::customizeMilk(string milk)
{
    milkType = milk;
    cout << "Milk type updated to: " << milkType << endl;
}

void Coffee::addShot()
{
    espressoShots++;
    cout << "Added an extra shot of espresso. Total shots: " << espressoShots << endl;
}

void Coffee::toggleIced()
{
    iced = !iced;
    cout << (iced ? "Iced coffee selected." : "Hot coffee selected.") << endl;
}

// tea class implementation
Tea::Tea(string n, float pr, int num, string cat, float disc, int cal, int scoops, string type, bool isIced)
    : Product(n, pr, num), sugarScoops(scoops), teaType(type), iced(isIced), hasCaffeine(true) {}

void Tea::adjustSugar(int scoops)
{
    sugarScoops = scoops;
    cout << "Sugar adjusted to " << sugarScoops << " scoops." << endl;
}

void Tea::toggleIced()
{
    iced = !iced;
    cout << (iced ? "Iced tea selected." : "Hot tea selected.") << endl;
}


Sweets::Sweets(string n, float pr, int num, string cat, float disc, int cal, string flavor, bool isGlutenFree)
    : Product(n, pr, num), flavor(flavor), glutenFree(isGlutenFree) {}

void Sweets::setFlavor(string flavor)
{
    this->flavor = flavor;
    cout << "Flavor updated to: " << flavor << endl;
}

string Sweets::getFlavor()
{
    return flavor;
}

void Sweets::setGlutenFree(bool isGlutenFree)
{
    glutenFree = isGlutenFree;
    cout << (glutenFree ? "Marked as gluten-free." : "Not gluten-free.") << endl;
}

bool Sweets::isGlutenFree()
{
    return glutenFree;
}


Sandwich::Sandwich(string n, float pr, int num, string cat, float disc, int cal, bool vegetarian, bool isToasted, vector<string> fillings)
    : Product(n, pr, num), isVegetarian(vegetarian), toasted(isToasted), fillings(fillings) {}