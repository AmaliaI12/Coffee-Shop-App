#include "../lib/event.hpp"
#include "../lib/data.hpp"

// default constructor
MusicEvent::MusicEvent() : guest("Unknown"), bandCost(0.0f), totalCost(0.0f)
{
    date = {1, 1, 2025};
}

// constructor
MusicEvent::MusicEvent(DATE d, string g, float bCost) : date(d), guest(g), bandCost(bCost), totalCost(bandCost + lightingCost + sceneCost) {}

void MusicEvent::eventInfo()
{
    cout << "Music Event Details:" << '\n';
    cout << "Date: " << date.day << "/" << date.month << "/" << date.year << '\n';
    cout << "Special Guest: " << guest << '\n';
}

// date getter
DATE MusicEvent::getDate()
{
    return date;
}

// default constructor
TastingEvent::TastingEvent() : prod("Unknown"), cost(0.0f)
{
    date = {1, 1, 2025};
}

// constructor
TastingEvent::TastingEvent(DATE d, string p, int num) : date(d), prod(p), numFreeProd(num), cost(flowerCost + personalizedMugs + num * DB::getInstance()->getProducts().at(p).getPrice()) {}

void TastingEvent::eventInfo()
{
    cout << "Tasting Event Details:" << '\n';
    cout << "Date: " << date.day << "/" << date.month << "/" << date.year << '\n';
    cout << "Special Product: " << prod << '\n';
    cout << "Come try our special product of the day! The first 100 people get one for free\n";
}

// date getter
DATE TastingEvent::getDate()
{
    return date;
}
