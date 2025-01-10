#include "../lib/data.hpp"
#include <filesystem>

 namespace fs = std::filesystem;

// initialize null instance
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

map<string, MusicEvent> &DB::getMusicEvents()
{
    return musicEvents;
}

map<string, TastingEvent> &DB::getTastingEvents()
{
    return tastingEvents;
}

// manage file actions

void DB::importEmployees(string city)
{
    // parse the file path
    fs::path filepath = fs::path("database") / city / "employees.csv";

    // handle error
    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filepath << '\n';
        return;
    }

    // erase data from previous city
    employees.clear();

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

        // create new employee object
        Employee emp(employeeID, name, jobTitle, {startH, startM}, {endH, endM}, yearsEmployed);

        // add object to the map
        employees.insert({employeeID, emp});
    }

    file.close();
    // cout << "Data imported successfully from " << filepath << '\n';
}

void DB::exportEmployees(string city)
{
    fs::path filepath = fs::path("database") / city / "employees.csv";

    ofstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filepath << '\n';
        return;
    }

    // write employee information to the file
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
    // cout << "Data exported successfully to " << path << '\n';
}

void DB::importOrders(string city)
{
    fs::path filepath = fs::path("database") / city / "orders.csv";

    // erase data from previous city if needed
    orders.clear();

    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filepath << '\n';
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

        // parse products and their quantities
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

            // check if the product exists in the products map
            if (products.find(productName) == products.end())
            {
                cerr << "Error: Product '" << productName << "' not found in database. Skipping product.\n";
                continue;
            }

            // add the product and quantity to items
            int numPcs = stoi(numPcsStr);
            ITEM item = {products[productName], numPcs};
            items.push_back(item);
        }

        // parse the total sum
        float totalSum = stof(totalSumStr);

        // create a new order
        Order order;
        order.setItems(items);
        order.setTotal(totalSum);
        order.setClientName(cliName);

        importedOrders.push_back(order);
    }

    orders = importedOrders;

    file.close();
    // cout << "Data imported successfully from " << path << '\n';
}

void DB::exportOrders(string city)
{
    fs::path filepath = fs::path("database") / city / "orders.csv";

    ofstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filepath << '\n';
        return;
    }

    for (Order order : orders)
    {
        string client = order.getClientName();
        cout << '!' << client << '\n';
        vector<ITEM> items = order.getItems();

        file << client << ',';
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
    // cout << "Data exported successfully to " << path << '\n';
}

void DB::importProducts(string city)
{
    fs::path filepath = fs::path("database") / city / "products.csv";

    // erase data from previous city if needed
    products.clear();

    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filepath << '\n';
        return;
    }

    string line;
    while (getline(file, line))
    {
        // skip empty lines
        if (line.empty())
            continue;

        // parse the line
        stringstream ss(line);
        string name;
        string priceStr, pcsStr, costStr;

        // extract data separated by commas
        if (!getline(ss, name, ',') || !getline(ss, costStr, ',') || !getline(ss, priceStr, ',') || !getline(ss, pcsStr, ','))
        {
            cerr << "Error: Malformed line in file: " << line << '\n';
            continue;
        }

        float cost = stof(costStr);
        float price = stof(priceStr);
        int pcs = stoi(pcsStr);

        // create product object
        Product prod(name, cost, price, pcs);

        // add the product to the map
        products.insert({name, prod});
    }

    file.close();
    // cout << "Data imported successfully from " << path << '\n';
}

void DB::exportProducts(string city)
{
    fs::path filepath = fs::path("database") / city / "products.csv";

    ofstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filepath << '\n';
        return;
    }

    for (auto [name, product] : products)
    {
        file << product.getName() << ","
             << product.getCost() << ","
             << product.getPrice() << ","
             << product.getPcs() << "\n";
    }

    file.close();
    // cout << "Data exported successfully to " << path << '\n';
}

void DB::importLoyalCostumers()
{
    fs::path filepath = fs::path("database") / "loyalCostumers.csv";

    // erase data from previous city
    loyalClients.clear();

    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filepath << '\n';
        return;
    }

    string line;
    while (getline(file, line))
    {
        // skip empty lines
        if (line.empty())
            continue;

        // parse the line
        stringstream ss(line);
        string name, pointstr;

        // extract data separated by commas
        if (!getline(ss, name, ',') || !getline(ss, pointstr, ','))
        {
            cerr << "Error: Malformed line in file: " << line << '\n';
            continue;
        }

        int points = stoi(pointstr);

        // add the client to the map
        loyalClients.insert({name, points});
    }

    file.close();
    // cout << "Data imported successfully from " << path << '\n';
}

void DB::exportLoyalCostumers()
{
    fs::path filepath = fs::path("database") / "loyalCustomers.csv";

    ofstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filepath << '\n';
        return;
    }

    for (auto [name, points] : loyalClients)
    {
        file << name << ","
             << points
             << "\n";
    }

    file.close();
    // cout << "Data exported successfully to " << path << '\n';
}

// import events from a single CSV file
void DB::importEvents(string city)
{
    fs::path filepath = fs::path("database") / city / "events.csv";
    ifstream file(filepath);

    // erase data from previous city if needed
    musicEvents.clear();
    tastingEvents.clear();

    if (!file.is_open())
    {
        cerr << "Error: Could not open file at " << filepath << '\n';
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string type, dateStr, productGuest;
        float bandCostOrCost;

        // read event type
        getline(ss, type, ',');

        // read date (dd/mm/yyyy)
        getline(ss, dateStr, ',');

        // read product/guest name
        getline(ss, productGuest, ',');

        // read band cost or product count
        ss >> bandCostOrCost;

        // add the event to the respective map
        if (type == "Music")
        {
            MusicEvent mus(dateStr, productGuest, bandCostOrCost);
            musicEvents.insert({dateStr, mus});
        }
        else if (type == "Tasting")
        {
            int num = bandCostOrCost;
            TastingEvent t;
            t.setDate(dateStr);
            t.setProd(productGuest);
            t.setNumProd(num);
            tastingEvents.insert({dateStr, t});
        }
        else
        {
            cerr << "Unknown event type: " << type << '\n';
        }
    }

    file.close();
    // cout << "Data imported successfully from " << path << '\n';
}

void DB::exportEvents(string city)
{
    fs::path filepath = fs::path("database") / city / "events.csv";
    ofstream outFile(filepath);

    if (!outFile.is_open())
    {
        cerr << "Error: Could not open file for exporting events!" << endl;
        return;
    }

    // export MusicEvents
    for (auto entry : musicEvents)
    {
        string dateStr = entry.first;
        MusicEvent musicEvent = entry.second;
        outFile << "Music," << dateStr << "," << musicEvent.getGuest() << "," << musicEvent.getBandCost() << "\n";
    }

    // Export TastingEvents
    for (auto entry : tastingEvents)
    {
        string dateStr = entry.first;
        TastingEvent tastingEvent = entry.second;
        outFile << "Tasting," << dateStr << "," << tastingEvent.getProduct() << "," << tastingEvent.getNumProd() << "\n";
    }

    outFile.close();
    // cout << "Events exported successfully to " << path << '\n';
}
