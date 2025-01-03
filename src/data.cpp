#include "..\lib\data.hpp"
#include <fstream>
#include <sstream>

DB *DB::instance = nullptr;

DB *DB::getInstance()
{
    if (instance == nullptr)
    {
        instance = new DB();
    }
    return instance;
}

// getters and setters
void DB::setOrders(vector<Order> o)
{
    orders = o;
}
vector<Order> &DB::getOrders()
{
    return orders;
}

void DB::setProducts(map<string, Product> prod)
{
    products = prod;
}
map<string, Product> &DB::getProducts()
{
    return products;
}

void DB::setEmployees(map<int, Employee> emp)
{
    employees = emp;
}
map<int, Employee> &DB::getEmployees()
{
    return employees;
}

map<string, int> &DB::getLoyalClients()
{
    return loyalClients;
}
void DB::setLoyalClients(map<string, int> cli)
{
    loyalClients = cli;
}

// manage file actions
void DB::importEmployees(string city)
{
    string path = "database\\" + city + "\\employees.csv";

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
    string path = "database\\" + city + "\\employees.csv";

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

    vector<Order> importedOrders;
    string line;

    while (getline(file, line))
    {
        // Skip empty lines
        if (line.empty())
            continue;

        stringstream ss(line);
        string cliName;
        vector<ITEM> items;
        string productEntry, totalSumStr;

        getline(ss, cliName, ',');

        // Parse products and their quantities
        while (getline(ss, productEntry, ','))
        {
            size_t colonPos = productEntry.find(':');
            if (colonPos == string::npos)
            {
                totalSumStr = productEntry;
                break;
            }

            string productName = productEntry.substr(0, colonPos);
            string numPcsStr = productEntry.substr(colonPos + 1);

            // Check if the product exists in the products map
            if (products.find(productName) == products.end())
            {
                cerr << "Error: Product '" << productName << "' not found in database. Skipping product.\n";
                continue;
            }

            // Add the product and quantity to items
            int numPcs = stoi(numPcsStr);
            ITEM item = {products[productName], numPcs};
            items.push_back(item);
        }

        // Parse the total sum
        float totalSum = stof(totalSumStr);

        // Create a new Order
        Order order;
        order.setItems(items);
        order.setTotal(totalSum);

        importedOrders.push_back(order);
    }

    orders = importedOrders;

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

    for (Order order : orders)
    {
        file << order.getClientName() << ',';
        vector<ITEM> items = order.getItems();

        for (size_t i = 0; i < items.size(); ++i)
        {
            ITEM item = items[i];
            file << item.product.getName() << ":" << item.numPcs;

            if (i < items.size() - 1)
                file << ",";
        }

        file << "," << order.getTotal() << '\n';
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

    string line;
    while (getline(file, line))
    {
        // Skip empty lines
        if (line.empty())
            continue;

        // Parse the line
        stringstream ss(line);
        string name;
        string priceStr, pcsStr;

        // Extract data separated by commas
        if (!getline(ss, name, ',') || !getline(ss, priceStr, ',') || !getline(ss, pcsStr, ','))
        {
            cerr << "Error: Malformed line in file: " << line << '\n';
            continue;
        }

        float price = stof(priceStr);
        int pcs = stoi(pcsStr);

        // Create Product object
        Product prod(name, price, pcs);

        // Add the product to the map
        products.insert({name, prod});
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

    for (auto [name, product] : products)
    {
        file << product.getName() << ","
             << product.getPrice() << ","
             << product.getPcs() << "\n";
    }

    file.close();
    cout << "Data exported successfully to " << path << '\n';
}

void DB::importLoyalCostumers()
{
    string path = "database\\loyalCostumers.csv";

    ifstream file(path);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << path << '\n';
        return;
    }

    string line;
    while (getline(file, line))
    {
        // Skip empty lines
        if (line.empty())
            continue;

        // Parse the line
        stringstream ss(line);
        string name, pointstr;

        // Extract data separated by commas
        if (!getline(ss, name, ',') || !getline(ss, pointstr, ','))
        {
            cerr << "Error: Malformed line in file: " << line << '\n';
            continue;
        }

        int points = stoi(pointstr);

        // Add the client to the map
        loyalClients.insert({name, points});
    }

    file.close();
    cout << "Data imported successfully from " << path << '\n';
}

void DB::exportLoyalCostumers()
{
    string path = "database\\loyalCostumers.csv";

    ofstream file(path);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << path << '\n';
        return;
    }

    for (auto [name, points] : loyalClients)
    {
        file << name << ","
             << points << ","
             << "\n";
    }

    file.close();
    cout << "Data exported successfully to " << path << '\n';
}