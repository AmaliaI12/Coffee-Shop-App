#include "..\lib\event.hpp"

// Default constructor for MusicEvent
MusicEvent::MusicEvent() : bandCost(0.0f), guest("Unknown")
{
    date = {1, 1, 2025};
}

MusicEvent::MusicEvent(DATE d, string g, float bandCost) : bandCost(bandCost), date(d), guest(g) {}

void MusicEvent::eventInfo()
{
    cout << "Music Event Details:" << '\n';
    cout << "Date: " << date.day << "/" << date.month << "/" << date.year << '\n';
    cout << "Special Guest: " << guest << '\n';
}

void MusicEvent::specialGuest()
{
    cout << "Special Guest: " << guest << '\n';
}

// Implementation of calculateCost for MusicEvent
float MusicEvent::calculateCost()
{
    return bandCost + lightingCost + sceneCost;
}

// Default constructor for TastingEvent
TastingEvent::TastingEvent() : cost(0.0f), prod("Unknown")
{
    date = {1, 1, 2025};
}

TastingEvent::TastingEvent(DATE d, string p) : date(d), prod(p) {}

void TastingEvent::eventInfo()
{
    cout << "Tasting Event Details:" << '\n';
    cout << "Date: " << date.day << "/" << date.month << "/" << date.year << '\n';
    cout << "Only today the first 100 costumers get this special product for free: " << prod << '\n';
}

// Implementation of specialProduct for TastingEvent
string TastingEvent::specialProduct()
{
    return prod;
}

// Implementation of calculateCost for TastingEvent
float TastingEvent::calculateCost()
{
    return flowerCost + personalizedMugs /*+ prod.price*/;
}
