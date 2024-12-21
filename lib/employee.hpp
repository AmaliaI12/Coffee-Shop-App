#include <cstring>
#include <iostream>
#include <vector>

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
    string phoneNumber;
    string email;
    string address;
    float performanceRating;
    float shiftDuration;
    vector<string> attendance;

public:
    // Constructor
    Employee(string n, string job, int startH, int startM, int endH, int endM, int y);

    void calculateSalary();
    void calculateShiftDuration();
    void updateAttendance(string date, string status);
    void viewPerformanceRating();
    void addEmployee();
    void deleteEmployee();
};

class Barista : public Employee
{
private:
    int tips;
    vector<string> specializations;
    int ordersFulfilled;
    bool certifications;
    int errorsInOrders;

public:
    Barista(string n, string job, int startH, int startM, int endH, int endM, int y);

    // Methods
    void calculateTips();
    void logOrder();
    void updateSpecializations(string skill);
    void trackErrors(int errorCount);
    void viewCertifications();
};


class Manager : public Employee
{
private:
    int numOfPeople;
    string branchLocation;
    float budgetResponsibility;
    int complaintsResolved;
    int teamMeetingsOrganized;
    int reportsGenerated;

public:
    Manager(string n, string job, int startH, int startM, int endH, int endM, int y, int numPeople);

    // Methods
    void approveLeave(string employeeID);
    void scheduleShifts();
    void resolveComplaint();
    void generateReport();
};


class Waiter : public Employee
{
private:
    int numTables;
    int tips;
    string assignedSection;
    int ordersTaken;
    vector<string> customerFeedback;
    float averageServiceTime;
    int breaksTaken;

public:
    Waiter(string n, string job, int startH, int startM, int endH, int endM, int y, int numtab);

    void calculateTips();
    void assignSection(string section);
    void logOrder();
    void collectFeedback(string feedback);
    void calculateServiceTime();
    void trackBreaks(int breakCount);
};
