#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class Product
{
private:
    string name;
    float price;
    int numItems;
    bool inStock;

public:
    Product(string n, float pr, int num);
    void isInStock();
};

class Coffee : public Product
{
private:
    bool hasFoam;
    string milkType;
    int espressoShots;
    string flavouredSyrup;
    bool iced;

public:
    Coffee(string n, float pr, int num, string cat, float disc, int cal, string milk, int shots, string syrup, bool isIced);

    void customizeMilk(string milk);
    void addShot();
    void toggleIced();

};

class Tea : public Product 
{
private:
    bool hasCaffeine;
    int sugarScoops;
    string teaType;
    bool iced;

public:
    Tea(string n, float pr, int num, string cat, float disc, int cal, int scoops, string type, bool isIced);

    void adjustSugar(int scoops);
    void toggleIced();

};

class Sweets : public Product
{
private:
    string flavor;
    bool glutenFree;

public:
    Sweets(string n, float pr, int num, string cat, float disc, int cal, string flavor, bool isGlutenFree);

    void setFlavor(string flavor);
    string getFlavor();

    void setGlutenFree(bool glutenFree);
    bool isGlutenFree();
};

class Sandwich : public Product
{
private:
    bool isVegetarian;
    bool toasted;
    vector<string> fillings;

public:
    Sandwich(string n, float pr, int num, string cat, float disc, int cal, bool vegetarian, bool isToasted, vector<string> fillings);
};
