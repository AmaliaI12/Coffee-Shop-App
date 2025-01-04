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

void TastingEvent::eventInfo()
{
    cout << "Tasting Event Details:" << '\n';
    cout << "Date: " << dateStr << '\n';
    cout << "Special Product: " << prod << '\n';
    cout << "Come try our special product of the day! The first 100 people get one for free\n";
}

// getters and setters
string TastingEvent::getDate()
{
    return dateStr;
}

void TastingEvent::setDate(string date)
{
    dateStr = date;
}

string TastingEvent::getProduct()
{
    return prod;
}

void TastingEvent::setProd(string p)
{
    prod = p;
}

int TastingEvent::getNumProd()
{
    return numProd;
}

void TastingEvent::setNumProd(int num)
{
    numProd = num;
}
