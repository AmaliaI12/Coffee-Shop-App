#include "lib\employee.hpp"

Employee::Employee(string n, string job, int startH, int startM, int endH, int endM, int y)
{
    name = n;
    jobTitle = job;
    startShift.hour = startH;
    startShift.minute = startM;
    endShift.hour = endH;
    endShift.minute = endM;
    yearsEmployed = y;
    calculateSalary();
}

void Employee::calculateSalary(){
    int actualSalary;
    actualSalary = baseSalary + yearsEmployed * bonusPerYear;
    salary = actualSalary;
}

