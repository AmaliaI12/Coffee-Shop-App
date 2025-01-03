#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <cstring>
#include <iostream>
#include "order.hpp"

using namespace std;

//define base salary and bonus
#define baseSalary 4500 // brut
#define bonusPerYear 350

//define time structure for shifts
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
    int getEmployeeID();
    void setEmployeeID(int id);

    string getName();
    void setName(string n);

    string getJobTitle();
    void setJobTitle(string job);

    TIME getStartShift();
    void setStartShift(TIME time);

    TIME getEndShift();
    void setEndShift(TIME time);

    int getYearsEmployed();
    void setYearsEmployed(int years);

    int getSalary();

    //calculate the other attributes
    void calculateSalary();
    void calculateShiftDuration();

    //special employee actions
    void logOrder(Order order);
    void addEmployee();
    void deleteEmployee();
    void changeSchedule();
};


//inheritance
class Barista : public Employee
{
public:
    //constructor
    Barista(int id, string n, string job, int startH, int startM, int endH, int endM, int y);

    //overriding the employee method
    void logOrder (Order order);
};


class Manager : public Employee
{
public:
    Manager(int id, string n, string job, int startH, int startM, int endH, int endM, int y);

    //void generateReport();

    //overriding the employee methods
    void addEmployee();
    void deleteEmployee();
    void changeSchedule();
};

#endif