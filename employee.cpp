#include "lib\employee.hpp"

// employee class implementation
Employee::Employee(string n, string job, int startH, int startM, int endH, int endM, int y, float performance)
{
    name = n;
    jobTitle = job;
    startShift.hour = startH;
    startShift.minute = startM;
    endShift.hour = endH;
    endShift.minute = endM;
    yearsEmployed = y;
    calculateSalary();
    performanceRating = performance;
    calculateShiftDuration();
}

void Employee::calculateSalary()
{
    salary = baseSalary + (yearsEmployed * bonusPerYear);
}

void Employee::calculateShiftDuration()
{
    shiftDuration = (endShift.hour + endShift.minute / 60.0) - (startShift.hour + startShift.minute / 60.0);
    if (shiftDuration < 0)
        shiftDuration += 24;
}

void Employee::viewPerformanceRating()
{
    cout << "Performance Rating for " << name << ": " << performanceRating << endl;
}

void Employee::addEmployee()
{
    cout << "Adding employee: " << name << endl;
}

void Employee::deleteEmployee()
{
    cout << "Deleting employee: " << name << endl;
}

// getters and setters
string Employee::getName() { return name; }
void Employee::setName(string n) { name = n; }

string Employee::getJobTitle() { return jobTitle; }
void Employee::setJobTitle(string job) { jobTitle = job; }

int Employee::getSalary() { return salary; }

float Employee::getPerformanceRating() { return performanceRating; }
void Employee::setPerformanceRating(float rating) { performanceRating = rating; }

// barista class implementation
Barista::Barista(string n, string job, int startH, int startM, int endH, int endM, int y, float performance, bool cert)
    : Employee(n, job, startH, startM, endH, endM, y,performance), certified(cert){}

void Barista::calculateTips()
{ 
}

void Barista::logOrder()
{
    cout << "Barista logged an order." << endl;
}

// Manager Class Implementation
Manager::Manager(string n, string job, int startH, int startM, int endH, int endM, int y, float performance, int numPeople, string location)
    : Employee(n, job, startH, startM, endH, endM, y, performance), numOfPeople(numPeople), branchLocation(location){}

void Manager::generateReport()
{
    cout << "Manager generated a report." << endl;
}

int Manager::getNumOfPeople() { return numOfPeople; }
void Manager::setNumOfPeople(int num) { numOfPeople = num; }


// Waiter Class Implementation
Waiter::Waiter(string n, string job, int startH, int startM, int endH, int endM, int y, float performance, int numtab, string section)
    : Employee(n, job, startH, startM, endH, endM, y, performance), numTables(numtab), assignedSection(section){}

void Waiter::calculateTips()
{
    cout << "Tips for Waiter: " << tips << endl;
}

int Waiter::getNumTables() { return numTables; }
void Waiter::setNumTables(int num) { numTables = num; }

string Waiter::getAssignedSection() { return assignedSection; }
void Waiter::setAssignedSection(string section) { assignedSection = section; }

