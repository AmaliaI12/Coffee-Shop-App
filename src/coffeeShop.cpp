#include "..\lib\employee.hpp"
#include "..\lib\order.hpp"
#include "..\lib\product.hpp"
#include "..\lib\data.hpp"

using namespace std;

string city;

void importData()
{
    cout << "Choose a city: Bucuresti, Timisoara, Sibiu, Cluj, Rm Valcea. ";
    cin >> city;

    // import data from database
    DB::getInstance();
    DB::getInstance()->importEmployees(city);
    DB::getInstance()->importProducts(city);
    DB::getInstance()->importOrders(city);
    DB::getInstance()->importLoyalCostumers();
}

// function to call the manager methods
void managerAction()
{
    cout << "What is your employee ID? ";
    int id;
    cin >> id;
    getchar();

    // create manager object to access the specific methods
    auto it = DB::getInstance()->getEmployees().find(id);
    Employee emp = it->second;
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

float applyDiscount(int value, float total)
{
    cout << "You have a " << value << "% off cupon. Do you want to use it? [y/n] ";
    char useCupon;
    cin >> useCupon;
    if (useCupon == 'y' || useCupon == 'Y')
    {
        total = (total * (100 - value)) / 100;
    }
    return total;
}

// function to log client's order
void clientAction()
{
    string name;
    cout << "What is your name? ";
    getline(cin, name);

    Order order;
    cout << "Hello " << name << "! What would you like to order?\n";

    order.setClientName(name);
    char ans;
    do
    {
        cout << "What is the name of the product? ";
        string prodName;
        getline(cin, prodName);

        // cout << prodName;

        Product prod = DB::getInstance()->getProducts().at(prodName);

        if (!prod.isInStock())
        {
            cout << "We do not have " << prodName << " at this moment.\n";
        }
        else
        {
            cout << "How many? ";
            int num;
            cin >> num;
            // getchar();

            if (num > prod.getPcs())
            {
                cout << "There are only " << prod.getPcs() << " left. Do you still want this product? [y/n] ";

                char wantProd;

                cin >> wantProd;
                if (wantProd == 'y' || wantProd == 'Y')
                {
                    cout << "How many? (maximum " << prod.getPcs() << ") ";
                    cin >> num;
                    getchar();
                    order.addItem(prod, num);
                }
            }
            else
                order.addItem(prod, num);
        }

        cout << "Do you want something else? [y/n] ";
        cin >> ans;
        getchar();
    } while (ans == 'y' || ans == 'Y');

    char hasCard;
    cout << "Do you have a loyalty card? [y/n] ";
    cin >> hasCard;
    if (hasCard == 'N' || hasCard == 'n')
    {
        cout << "\n-----------------loyalty card info-------------------\n";
        cout << "A loyalty card gives you bonus points for every purchase in our store.\nFor every 2$ spent in our store you earn 1 point.\nHere are some examples of rewards you can get by accumulating points:\n";

        cout << "10p -> 5% off your next order!\n";
        cout << "20p -> 10 %off your next order!\n";
        cout << "25p -> 15 %off your next order!\n";
        cout << "50p -> 30 %off your next order!\n";

        cout << "Would you like to make a loyalty card? [y/n] ";
        char wantsCard;
        cin >> wantsCard;
        if (wantsCard == 'Y' || wantsCard == 'y')
        {
            DB::getInstance()->getLoyalClients().insert({name, 0});
            hasCard = 'y';
        }
    }

    // calculate total
    order.calculateTotal();

    if (hasCard == 'y' || hasCard == 'Y')
    {
        int pts = DB::getInstance()->getLoyalClients().at(name);
        if (pts >= 50)
        {
            order.setTotal(applyDiscount(30, order.getTotal()));
            DB::getInstance()->getLoyalClients()[name] = pts - 50;
        }
        else if (pts >= 25)
        {
            order.setTotal(applyDiscount(15, order.getTotal()));
            DB::getInstance()->getLoyalClients()[name] = pts - 25;
        }
        else if (pts >= 20)
        {
            order.setTotal(applyDiscount(10, order.getTotal()));
            DB::getInstance()->getLoyalClients()[name] = pts - 20;
        }
        else if (pts >= 10)
        {
            order.setTotal(applyDiscount(5, order.getTotal()));
            DB::getInstance()->getLoyalClients()[name] = pts - 10;
        }

        //add the earned points for this order
        DB::getInstance()->getLoyalClients()[name] += (int)order.getTotal() / 2;
    }

    // TODO apply discounts for client
    cout << "\n------------Total-----------------\n";
    cout << "Your total is: " << order.getTotal() << '\n';

    Barista barista;
    barista.logOrder(order);

    // used recursivity to simplify code
    cout << "Would you like to order again? [y/n] ";
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y')
        clientAction();
}

void stockerAction()
{
    cout << "What is your employee ID? ";
    int id;
    cin >> id;
    getchar();

    // create stocker object to access the specific methods
    auto it = DB::getInstance()->getEmployees().find(id);
    Employee emp = it->second;
    StockKeeper stocker(emp.getEmployeeID(), emp.getName(), emp.getJobTitle(), emp.getStartShift(), emp.getEndShift(), emp.getYearsEmployed());

    char ans;
    do
    {
        cout << "Hi " << stocker.getName() << "! Here's what you can do:\n";
        cout << "1) Add product\n";
        cout << "2) Delete product\n";
        cout << "3) Manage a product's stock\n";
        cout << "What would you like to do? [1/2/3]: ";

        int action;
        cin >> action;

        switch (action)
        {
        case 1:
            stocker.addProduct();
            break;
        case 2:
            stocker.deleteProduct();
            break;
        case 3:
            stocker.stockProduct();
            break;
        default:
            cout << "You have to choose 1/2/3.\n";
        }

        cout << "Would you like to do something else? (y/n) ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');

    cout << "Goodbye " << stocker.getName() << "!\n";
}

int action()
{
    // used exceptions to make sure the user input is correct
    try
    {
        int status;
        cout << "Are you a manager, stocker or client? (1 Manager / 2 Stocker/ 3 Client / 4 Exit): ";
        cin >> status;
        getchar();

        if (status == 1)
        {
            managerAction();
            // update database
            DB::getInstance()->exportEmployees(city);
        }
        else if (status == 2)
        {
            stockerAction();
            // update database
            DB::getInstance()->exportProducts(city);
        }
        else if (status == 3)
        {
            clientAction();
            // update database
            DB::getInstance()->exportProducts(city);
            DB::getInstance()->exportOrders(city);
            DB::getInstance()->exportLoyalCostumers();
        }
        else if (status == 4)
        {
            return -1;
        }
        else
        {
            throw invalid_argument("Invalid input! Please select 1, 2, 3 or 4.\n");
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