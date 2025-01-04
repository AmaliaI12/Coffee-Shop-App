#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <cstring>

using namespace std;

#define lightingCost 300
#define sceneCost 400
#define flowerCost 100
#define personalizedMugs 500

// use abstractization
class Event
{
public:
    virtual void eventInfo() = 0;
    virtual string getDate() = 0;
};

class MusicEvent : public Event
{
private:
    string dateStr;
    string guest;
    float bandCost;
    float totalCost;

public:
    MusicEvent();
    MusicEvent(string d, string g, float bandCost);
    void eventInfo() override;
    string getDate() override;
    string getGuest();
    float getBandCost();
};

class TastingEvent : public Event
{
private:
    string dateStr;
    string prod;
    int numProd;
    float cost;
public:
    TastingEvent();
    TastingEvent(string d, string p, int num);
    void eventInfo() override;
    string getDate() override;
    string getProduct();
    int getNumProd();
};

#endif