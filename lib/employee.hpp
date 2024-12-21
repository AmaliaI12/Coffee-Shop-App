#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <random>

using namespace std;

#define baseSalary 4500 // brut
#define bonusPerYear 350

typedef struct
{
    int hour;
    int minute;
} TIME;

class Employee
{
private:
    string name;
    string jobTitle;
    TIME startShift;
    TIME endShift;
    int salary;
    int yearsEmployed;
    int employeeID;
    float performanceRating;
    float shiftDuration;

public:
    // constructor
    Employee(string n, string job, int startH, int startM, int endH, int endM, int y, float performance);

    //gettes and setters
    string getName();
    void setName(string n);
    string getJobTitle();
    void setJobTitle(string job);
    int getSalary();
    float getPerformanceRating();
    void setPerformanceRating(float rating);


    void calculateSalary();
    void calculateShiftDuration();
    void viewPerformanceRating();

    void addEmployee();
    void deleteEmployee();
};

class Barista : public Employee
{
private:
    int tips;
    bool certified;

public:
    Barista(string n, string job, int startH, int startM, int endH, int endM, int y, float performance, bool cert);

    void calculateTips();
    void logOrder();
};


class Manager : public Employee
{
private:
    int numOfPeople;
    string branchLocation;

public:
    Manager(string n, string job, int startH, int startM, int endH, int endM, int y, float performance, int numPeople, string location);

    //getter and setter
    int getNumOfPeople();
    void setNumOfPeople(int num);

    void generateReport();
};


class Waiter : public Employee
{
private:
    int numTables;
    int tips;
    string assignedSection;

public:
    Waiter(string n, string job, int startH, int startM, int endH, int endM, int y, float performance, int numtab, string section);

    int getNumTables();
    void setNumTables(int num);

    string getAssignedSection();
    void setAssignedSection(string section);

    void calculateTips();
};
