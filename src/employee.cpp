#include "../lib/employee.hpp"
#include "../lib/data.hpp"
#include "../lib/raport.hpp"

// EMPLOYEE CLASS IMPLEMENTATION

// constructor
Employee::Employee(int id, string n, string job, TIME startS, TIME endS, int y)
{
    employeeID = id;
    name = n;
    jobTitle = job;
    startShift = startS;
    endShift = endS;
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
int Employee::getEmployeeID()
{
    return employeeID;
}
void Employee::setEmployeeID(int id)
{
    employeeID = id;
}

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

TIME Employee::getStartShift()
{
    return startShift;
}

void Employee::setStartShift(TIME st)
{
    startShift = st;
}

TIME Employee::getEndShift()
{
    return endShift;
}

void Employee::setEndShift(TIME st)
{
    endShift = st;
}

int Employee::getSalary()
{
    return salary;
}

int Employee::getYearsEmployed()
{
    return yearsEmployed;
}

void Employee::setYearsEmployed(int years)
{
    yearsEmployed = years;
}

// special employee actions
void Employee::logOrder(Order order)
{
    cout << "Normal employees cannot log orders, contact a barista for this.";
}

void Employee::addEmployee()
{
    cout << "Normal employees cannot do this, contact a manager for this.";
}

void Employee::deleteEmployee()
{
    cout << "Normal employees cannot do this, contact a manager for this.";
}

void Employee::changeSchedule(Employee emp)
{
    cout << "Normal employees cannot do this, contact a manager for this.";
}

void Employee::addProduct()
{
    cout << "Normal employees cannot do this, contact a stock keeper for this.";
}

void Employee::deleteProduct()
{
    cout << "Normal employees cannot do this, contact a stock keeper for this.";
}

void Employee::stockProduct()
{
    cout << "Normal employees cannot do this, contact a stock keeper for this.";
}

// BARISTA CLASS IMPLEMENTATION

// constructor
Barista::Barista(int id, string n, string job, TIME startS, TIME endS, int y)
    : Employee(id, n, job, startS, endS, y) {}

// default constructor
Barista::Barista() : Employee(0, "", "Barista", {0, 0}, {0, 0}, 0) {}

// special barista action -> order management
void Barista::logOrder(Order order)
{
    DB::getInstance()->getOrders().push_back(order);
    cout << "The order has been logged successfully!\n";
}

// MANAGER CLASS IMPLEMENTATION

// constructor
Manager::Manager(int id, string n, string job, TIME startS, TIME endS, int y)
    : Employee(id, n, job, startS, endS, y) {}

// special manager actions
void Manager::addEmployee()
{
    int id;
    string name;
    string jobTitle;
    TIME startShift;
    TIME endShift;
    int yearsEmployed;

    // get new employee information
    cout << "Enter employee information:\n";

    cout << "ID: ";
    cin >> id;
    getchar();
    cout << "Name: ";
    getline(cin, name);
    cout << "Job title: ";
    getline(cin, jobTitle);
    cout << "Start of shift: [hh mm] ";
    cin >> startShift.hour >> startShift.minute;
    cout << "End of shift: [hh mm] ";
    cin >> endShift.hour >> endShift.minute;
    cout << "Years employed in this coffee shop: ";
    cin >> yearsEmployed;

    // create new employee object
    Employee emp(id, name, jobTitle, startShift, endShift, yearsEmployed);

    // add employee to the map
    DB::getInstance()->getEmployees().insert({id, emp});
    cout << "Successfully added the employee.\n";
}

void Manager::deleteEmployee()
{
    cout << "What is the ID of the employee you want to delete? ";
    int id;
    cin >> id;
    DB::getInstance()->getEmployees().erase(id);
    cout << "Successfully deleted the employee.\n";
}

void Manager::changeSchedule()
{
    cout << "What is the ID of the employee you want to change the schedule for? ";
    int id;
    cin >> id;

    TIME startShift;
    TIME endShift;

    // read new program
    cout << "New start of shift: [hh mm] ";
    cin >> startShift.hour >> startShift.minute;
    cout << "New end of shift: [hh mm] ";
    cin >> endShift.hour >> endShift.minute;

    // modify data structure
    DB::getInstance()->getEmployees().at(id).setStartShift(startShift);
    DB::getInstance()->getEmployees().at(id).setEndShift(endShift);
}

void Manager::generateReport(string city) {
    try {
         string filename = "database\\" + city + "\\raport";

        // generate reports in both languages.
        Raport<Romanian>::generate(filename + "_ro.csv");
        Raport<English>::generate(filename + "_en.csv");

        cout << "Reports generated successfully by Manager: " << getName() << "\n";

    } catch (const exception &e) {
        cerr << "Error generating reports: " << e.what() << "\n";
    }
}


// STOCKKEEPER CLASS IMPLEMENTATION

// constructor
StockKeeper::StockKeeper(int id, string n, string job, TIME startS, TIME endS, int y)
    : Employee(id, n, job, startS, endS, y) {}

void StockKeeper::addProduct()
{
    string name;
    float cost, price;
    int pcs;

    // read new product information
    cout << "Enter product information:\n";
    cout << "Name: ";
    getchar();
    getline(cin, name);
    cout << "Cost: ";
    cin >> cost;
    cout << "Price: ";
    cin >> price;
    cout << "Pieces in stock: ";
    cin >> pcs;

    //create new product object
    Product prod(name, cost, price, pcs);

    //add object to the map
    DB::getInstance()->getProducts().insert({name, prod});
}

void StockKeeper::deleteProduct()
{
    cout << "What product do you want to delete? ";
    string name;
    getchar();
    getline(cin, name);

    DB::getInstance()->getProducts().erase(name);
}

void StockKeeper::stockProduct()
{
    string name;
    int newpcs;
    cout << "Enter product information:\n";
    cout << "Name: ";
    getchar();
    getline(cin, name);
    cout << "Updated stock: ";
    cin >> newpcs;

    // modify number of pieces in stock
    DB::getInstance()->getProducts().at(name).setPcs(newpcs);
}
