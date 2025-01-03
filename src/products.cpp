#include "..\lib\product.hpp"

// constructor
Product::Product(string n, float pr, int num)
    : prodName(n), price(pr), pcs(num), inStock(isInStock()) {}

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

// // Coffee Class Implementation
// Coffee::Coffee(string n, float pr, int num, string cat, float disc, int cal, string milk, int shots, string syrup, bool isIced)
//     : Product(n, pr, num), milkType(milk), espressoShots(shots), flavouredSyrup(syrup), iced(isIced), hasFoam(true) {}

// void Coffee::customizeMilk(string milk)
// {
//     milkType = milk;
//     cout << "Milk type updated to: " << milkType << endl;
// }

// void Coffee::addShot()
// {
//     espressoShots++;
//     cout << "Added an extra shot of espresso. Total shots: " << espressoShots << endl;
// }

// void Coffee::toggleIced()
// {
//     iced = !iced;
//     cout << (iced ? "Iced coffee selected." : "Hot coffee selected.") << endl;
// }

// // tea class implementation
// Tea::Tea(string n, float pr, int num, string cat, float disc, int cal, int scoops, string type, bool isIced)
//     : Product(n, pr, num), sugarScoops(scoops), teaType(type), iced(isIced), hasCaffeine(true) {}

// void Tea::adjustSugar(int scoops)
// {
//     sugarScoops = scoops;
//     cout << "Sugar adjusted to " << sugarScoops << " scoops." << endl;
// }

// void Tea::toggleIced()
// {
//     iced = !iced;
//     cout << (iced ? "Iced tea selected." : "Hot tea selected.") << endl;
// }

// Sweets::Sweets(string n, float pr, int num, string cat, float disc, int cal, string flavor, bool isGlutenFree)
//     : Product(n, pr, num), flavor(flavor), glutenFree(isGlutenFree) {}

// void Sweets::setFlavor(string flavor)
// {
//     this->flavor = flavor;
//     cout << "Flavor updated to: " << flavor << endl;
// }

// string Sweets::getFlavor()
// {
//     return flavor;
// }

// void Sweets::setGlutenFree(bool isGlutenFree)
// {
//     glutenFree = isGlutenFree;
//     cout << (glutenFree ? "Marked as gluten-free." : "Not gluten-free.") << endl;
// }

// bool Sweets::isGlutenFree()
// {
//     return glutenFree;
// }

// Sandwich::Sandwich(string n, float pr, int num, string cat, float disc, int cal, bool vegetarian, bool isToasted, vector<string> fillings)
//     : Product(n, pr, num), isVegetarian(vegetarian), toasted(isToasted), fillings(fillings) {}