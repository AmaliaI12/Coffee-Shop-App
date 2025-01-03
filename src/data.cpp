#include "..\lib\data.hpp"
#include <fstream>
#include <sstream>

DB* DB::instance = nullptr;

DB* DB::getInstance() {
    if (instance == nullptr) {
        instance = new DB();
    }
    return instance;
}

//getters and setters
void DB::setOrders(vector<Order> o) {
    orders = o;
}
vector<Order> DB::getOrders() {
    return orders;
}

void DB::setProducts(map<string, Product> prod) {
    products = prod;
}
map<string, Product> DB::getProducts() {
    return products;
}

void DB::setEmployees(map<int, Employee> emp) {
    employees = emp;
}
map<int, Employee> DB::getEmployees() {
    return employees;
}


//manage file actions
void DB::importEmployees(string city)
{
    string path = "database\\" + city + "\\employee.csv";

    ifstream file(path);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << path << '\n';
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string field, f1, f2;

        int employeeID;
        string name;
        string jobTitle;
        int startH, startM, endH, endM;
        int yearsEmployed;

        getline(ss, field, ',');
        employeeID = stoi(field);

        getline(ss, name, ',');

        getline(ss, jobTitle, ',');

        getline(ss, field, ',');
        stringstream startTm(field);
        getline(startTm, f1, ':');
        getline(startTm, f2, ':');
        startH = stoi(f1);
        startM = stoi(f2);

        getline(ss, field, ',');
        stringstream endTm(field);
        getline(endTm, f1, ':');
        getline(endTm, f2, ':');
        endH = stoi(f1);
        endM = stoi(f2);

        getline(ss, field, ',');
        yearsEmployed = stoi(field);

        Employee emp(employeeID, name, jobTitle, {startH, startM}, {endH, endM}, yearsEmployed);

        employees.insert({employeeID, emp});
    }

    file.close();
    cout << "Data imported successfully from " << path << '\n';
}

void DB::exportEmployees(string city)
{
    string path = "database\\" + city + "\\employee.csv";

    ofstream file(path);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << path << '\n';
        return;
    }

    for (auto [id, emp] : employees)
    {
        TIME startShift = emp.getStartShift();
        TIME endShift = emp.getEndShift();
        file << emp.getEmployeeID() << ','
             << emp.getName() << ','
             << emp.getJobTitle() << ','
             << startShift.hour << ':'
             << startShift.minute << ','
             << endShift.hour << ':'
             << endShift.minute << ','
             << emp.getYearsEmployed() << '\n';
    }

    file.close();
    cout << "Data exported successfully to " << path << '\n';
}

void DB::importOrders(string city)
{
    string path = "database\\" + city + "\\orders.csv";

    ifstream file(path);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << path << '\n';
        return;
    }

    

    file.close();
    cout << "Data imported successfully from " << path << '\n';
}

void DB::exportOrders(string city)
{
    string path = "database\\" + city + "\\orders.csv";

    ofstream file(path);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << path << '\n';
        return;
    }

    file.close();
    cout << "Data exported successfully to " << path << '\n';
}

void DB::importProducts(string city)
{
    string path = "database\\" + city + "\\products.csv";

    ifstream file(path);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << path << '\n';
        return;
    }

    file.close();
    cout << "Data imported successfully from " << path << '\n';
}

void DB::exportProducts(string city)
{
    string path = "database\\" + city + "\\products.csv";

    ofstream file(path);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << path << '\n';
        return;
    }

    file.close();
    cout << "Data exported successfully to " << path << '\n';
}