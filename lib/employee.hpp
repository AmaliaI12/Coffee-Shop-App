#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <cstring>
#include <iostream>
#include "orders.hpp"

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
    int employeeID;
    string name;
    string jobTitle;
    TIME startShift;
    TIME endShift;
    int salary;
    int yearsEmployed;
    float shiftDuration;

public:
    // constructor
    Employee(int id, string n, string job, int startH, int startM, int endH, int endM, int y);

    //gettes and setters
    string getName();
    void setName(string n);
    string getJobTitle();
    void setJobTitle(string job);
    int getSalary();

    void calculateSalary();
    void calculateShiftDuration();
};

class Barista : public Employee
{
private:
    int tips;
    bool certified;
public:
    Barista(int id, string n, string job, int startH, int startM, int endH, int endM, int y, bool cert);

    void calculateTips();
    void logOrder(Order order);
};

class Manager : public Employee
{
private:
    int numOfPeople;
    string branchLocation;

public:
    Manager(int id, string n, string job, int startH, int startM, int endH, int endM, int y, int numPeople, string location);

    //getter and setter
    int getNumOfPeople();
    void setNumOfPeople(int num);

    //void generateReport();

    void addEmployee();
    void deleteEmployee();
    void changeSchedule(Employee employee);
};

#endif