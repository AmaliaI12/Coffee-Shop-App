#include "..\lib\employee.hpp"
#include "..\lib\order.hpp"
#include "..\lib\product.hpp"
#include "..\lib\data.hpp"

using namespace std;


void importData()
{
    string city;
    cout << "Choose a city: Bucuresti, Timisoara, Sibiu, Cluj, Rm Valcea.\n";
    cin >> city;

    // import data from database
    DB::getInstance();
    DB::getInstance()->importEmployees(city);
    DB::getInstance()->importOrders(city);
    DB::getInstance()->importProducts(city);
}


// function to call the manager methods
void managerAction()
{
    cout << "What is your employee ID? ";
    int id;
    cin >> id;

    // create manager object to access the specific methods
    Employee emp = DB::getInstance()->getEmployees().at(id);
    Manager manager(emp.getEmployeeID(), emp.getName(), emp.getJobTitle(), emp.getStartShift(), emp.getEndShift(), emp.getYearsEmployed());

    char ans;
    do
    {
        cout << "Hi " << manager.getName() << "! Here's what you can do:\n";
        cout << "1) Add an employee\n";
        cout << "2) Delete an employee\n";
        cout << "3) Change an employee's schedule\n";
        cout << "What would you like to do? [1/2/3]: ";

        int action;
        cin >> action;

        switch (action)
        {
        case 1:
            manager.addEmployee();
            break;
        case 2:
            manager.deleteEmployee();
            break;
        case 3:
            manager.changeSchedule();
            break;
        default:
            cout << "You have to choose 1/2/3.\n";
        }

        cout << "Would you like to do something else? (y/n) ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');

    cout << "Goodbye " << manager.getName() << "!\n";
}

//function to log client's order
void clientAction()
{
    Order order;
    cout << "What would you like to order?\n";
    char ans;
    do
    {
        cout << "What is the name of the product? ";
        string prodName;
        cin >> prodName;

        Product prod = DB::getInstance()->getProducts().at(prodName);

        cout << "How many? ";
        int num;
        cin >> num;
        order.addItem(prod, num);

        cout << "Do you want something else? [y/n]";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');

    // calculate total
    order.calculateTotal();
    cout << "Your total is: " << order.getTotal();

    Barista barista;
    barista.logOrder(order);

    // used recursivity to simplify code
    cout << "Would you like to order again? [y/n] ";
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y')
        clientAction();
}

int action()
{
    // used exceptions to make sure the user input is correct
    try
    {
        int status;
        cout << "Are you a manager or client? (1 Manager / 2  Client / 3 Exit): ";
        cin >> status;

        if (status == 1)
        {
            managerAction();
        }
        else if (status == 2)
        {
            clientAction();
        }
        else if (status == 3)
        {
            return -1;
        }
        else
        {
            throw invalid_argument("Invalid input! Please select 1 or 2.\n");
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: " << e.what();
        action();
    }
    return 0;
}

int main()
{
    importData();

    int ret;
    do
    {
        cout << "------------------WELCOME TO COOL COFFEE!------------------\n";
        ret = action();
    } while (ret == 0);

    return 0;
}