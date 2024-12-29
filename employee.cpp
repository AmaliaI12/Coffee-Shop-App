#include "lib\employee.hpp"

// employee class implementation
Employee::Employee(int id, string n, string job, int startH, int startM, int endH, int endM, int y)
{
    employeeID = id;
    name = n;
    jobTitle = job;
    startShift.hour = startH;
    startShift.minute = startM;
    endShift.hour = endH;
    endShift.minute = endM;
    yearsEmployed = y;
    calculateSalary();
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


// getters and setters
string Employee::getName() 
{ 
    return name;
}
void Employee::setName(string n)
{ 
    name = n;
}

string Employee::getJobTitle()
{
    return jobTitle;
}

void Employee::setJobTitle(string job) 
{ 
    jobTitle = job;
}

int Employee::getSalary() { return salary; }


// barista class implementation
Barista::Barista(int id, string n, string job, int startH, int startM, int endH, int endM, int y, bool cert)
    : Employee(id, n, job, startH, startM, endH, endM, y), certified(cert){}


void Barista::calculateTips()
{ 
}

void Barista::logOrder(Order order)
{
    cout << "Barista logged an order." << endl;
}

// Manager Class Implementation
Manager::Manager(int id, string n, string job, int startH, int startM, int endH, int endM, int y, int numPeople, string location)
    : Employee(id, n, job, startH, startM, endH, endM, y), numOfPeople(numPeople), branchLocation(location){}

int Manager::getNumOfPeople() { return numOfPeople; }
void Manager::setNumOfPeople(int num) { numOfPeople = num; }


void Manager::addEmployee()
{
    cout << "Adding employee: " << getName() << endl;
}

void Manager::deleteEmployee()
{
    cout << "Deleting employee: " << getName() << endl;
}