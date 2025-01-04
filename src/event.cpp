#include "../lib/event.hpp"
#include "../lib/data.hpp"

// default constructor
MusicEvent::MusicEvent() : guest("Unknown"), bandCost(0.0f), totalCost(0.0f)
{
    dateStr = "1/1/2025";
}

// constructor
MusicEvent::MusicEvent(string d, string g, float bCost) : dateStr(d), guest(g), bandCost(bCost), totalCost(bandCost + lightingCost + sceneCost) {}

void MusicEvent::eventInfo()
{
    cout << "Music Event Details:" << '\n';
    cout << "Date: " << dateStr << '\n';
    cout << "Special Guest: " << guest << '\n';
}

// getters
string MusicEvent::getDate()
{
    return dateStr;
}

string MusicEvent::getGuest()
{
    return guest;
}

float MusicEvent::getBandCost()
{
    return bandCost;
}

// default constructor
TastingEvent::TastingEvent() : prod("Unknown"), cost(0.0f)
{
    dateStr = "1/1/2025";
}

// constructor
TastingEvent::TastingEvent(string d, string p, int num) : dateStr(d), prod(p), numProd(num), cost(flowerCost + personalizedMugs + num * DB::getInstance()->getProducts().at(p).getPrice()) {}

void TastingEvent::eventInfo()
{
    cout << "Tasting Event Details:" << '\n';
    cout << "Date: " << dateStr << '\n';
    cout << "Special Product: " << prod << '\n';
    cout << "Come try our special product of the day! The first 100 people get one for free\n";
}

// getters
string TastingEvent::getDate()
{
    return dateStr;
}

string TastingEvent::getProduct()
{
    return prod;
}

int TastingEvent::getNumProd()
{
    return numProd;
}
