#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <cstring>

using namespace std;

#define lightingCost 300
#define sceneCost 400
#define flowerCost 100
#define personalizedMugs 500

typedef struct 
{
    int day, month, year;    
}DATE;


// use abstractization
class Event
{
public:
    virtual void eventInfo() = 0;
    virtual void specialGuest();
    virtual string specialProduct();
    virtual float calculateCost() = 0;
};


class MusicEvent : public Event
{
private:
    DATE date;
    string guest;
    float bandCost;
    float totalCost;
public:
    MusicEvent();
    MusicEvent(DATE d, string g, float bandCost);
    void eventInfo() override;
    void specialGuest();
    float calculateCost() override;
};

class TastingEvent : public Event
{
private:
    DATE date;
    string prod;
    float cost;
public:
    TastingEvent();
    TastingEvent(DATE d, string p);
    void eventInfo() override;
    string specialProduct();
    float calculateCost() override;
};

#endif