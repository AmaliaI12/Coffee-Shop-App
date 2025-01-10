#include "../lib/employee.hpp"
#include "../lib/order.hpp"
#include "../lib/product.hpp"
#include "../lib/data.hpp"
#include "../lib/event.hpp"
#include <time.h>

using namespace std;

string city;

// import data from the database
void importData()
{
    int goodInput;
    do
    {
        goodInput = 1;
        cout << "Choose a city: Bucuresti, Timisoara, Sibiu, Cluj, Rm Valcea. ";
        getline(cin, city);
        if (city != "Bucuresti" && city != "Timisoara" && city != "Sibiu" && city != "Cluj" && city != "Rm Valcea")
        {
            goodInput = 0;
            cout << "Please select one of the listed cities.\n";
        }
    } while (goodInput != 1);

    DB::getInstance();
    DB::getInstance()->importEmployees(city);
    DB::getInstance()->importProducts(city);
    DB::getInstance()->importOrders(city);
    DB::getInstance()->importLoyalCostumers();
    DB::getInstance()->importEvents(city);
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
    // manager can do multiple actions
    do
    {
        cout << "Hi " << manager.getName() << "! Here's what you can do:\n";
        cout << "1) Add an employee\n";
        cout << "2) Delete an employee\n";
        cout << "3) Change an employee's schedule\n";
        cout << "4) Close the shop and create daily raport\n";
        cout << "What would you like to do? [1/2/3/4]: ";

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
        case 4:
            manager.generateReport(city);
            break;
        default:
            cout << "You have to choose 1/2/3/4.\n";
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

void makeLoyaltyCard(char *hasCard, Order *order)
{
    cout << "Would you like to make a loyalty card? [y/n] ";
    char wantsCard;
    cin >> wantsCard;
    if (wantsCard == 'Y' || wantsCard == 'y')
    {
        DB::getInstance()->getLoyalClients().insert({order->getClientName(), 0});
        *hasCard = 'y';
    }
}

// handle loyalty card actions
void loyaltyCardAction(Order *order)
{
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

        makeLoyaltyCard(&hasCard, order);
    }

    // calculate total
    order->calculateTotal();

    if (hasCard == 'y' || hasCard == 'Y')
    {
        auto it = DB::getInstance()->getLoyalClients().find(order->getClientName());
        if (it == DB::getInstance()->getLoyalClients().end())
        {
            cout << "You do not have a loyalty card.\n";
            return;
        }
        int pts = DB::getInstance()->getLoyalClients().at(order->getClientName());
        if (pts >= 50)
        {
            order->setTotal(applyDiscount(30, order->getTotal()));
            DB::getInstance()->getLoyalClients()[order->getClientName()] = pts - 50;
        }
        else if (pts >= 25)
        {
            order->setTotal(applyDiscount(15, order->getTotal()));
            DB::getInstance()->getLoyalClients()[order->getClientName()] = pts - 25;
        }
        else if (pts >= 20)
        {
            order->setTotal(applyDiscount(10, order->getTotal()));
            DB::getInstance()->getLoyalClients()[order->getClientName()] = pts - 20;
        }
        else if (pts >= 10)
        {
            order->setTotal(applyDiscount(5, order->getTotal()));
            DB::getInstance()->getLoyalClients()[order->getClientName()] = pts - 10;
        }

        // add the earned points for this order
        DB::getInstance()->getLoyalClients()[order->getClientName()] += (int)order->getTotal() / 2;
    }
}

// function to log client's order
void clientAction()
{
    string name;
    cout << "What is your name? ";
    getline(cin, name);

    Order order;
    cout << "Hello " << name << "! What would you like to order?\n";

    // add name to the order
    order.setClientName(name);

    // client can order multiple items
    char ans;
    do
    {
        cout << "What is the name of the product? ";
        string prodName;
        getline(cin, prodName);

        // search the product by name in database
        auto it = DB::getInstance()->getProducts().find(prodName);

        if (it != DB::getInstance()->getProducts().end())
        {
            Product prod = it->second;
            if (!prod.isInStock())
            {
                cout << "We do not have " << prodName << " at this moment.\n";
            }
            else
            {
                cout << "How many? ";
                int num;
                cin >> num;

                // handle insufficient stock
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

                        // add item to order
                        order.addItem(prod, num);
                    }
                }
                else
                    // add item to order
                    order.addItem(prod, num);
            }
        }
        else
        {
            cout << "We don't currently have " << prodName << '\n';
        }

        cout << "Do you want something else? [y/n] ";
        cin >> ans;
        getchar();
    } while (ans == 'y' || ans == 'Y');

    // make loyalty card and apply discounts
    loyaltyCardAction(&order);

    cout << "\n------------Total-----------------\n";
    cout << "Your total is: " << order.getTotal() << '\n';

    // log order using barista object
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
        cout << "Here's what you can do!\n";
        cout << "1) Log in as Manager.\n";
        cout << "2) Log in as Stocker.\n";
        cout << "3) Log in as Client and place an order.\n";
        cout << "4) Switch cities.\n";
        cout << "5) Exit.\n";

        cout << "What do you want to do? (1/2/3/4/5): ";
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
            return 1;
        }
        else if (status == 5)
        {
            return -1;
        }
        else
        {
            throw invalid_argument("Invalid input! Please select 1, 2, 3, 4 or 5.\n");
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: " << e.what();
        action();
    }
    return 0;
}

string getTodayDate()
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);

    // format the date as "dd/mm/yyyy"
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", now);

    return string(buffer);
}

int main()
{

    int ret = 1;
    do
    {
        // if user changed the city reimport data
        if (ret == 1)
            importData();

        // check if there's a music event today
        auto it = DB::getInstance()->getMusicEvents().find(getTodayDate());
        // check if there's a tasting event today
        auto it2 = DB::getInstance()->getTastingEvents().find(getTodayDate());

        if (it != DB::getInstance()->getMusicEvents().end())
        {
            cout << "Today is a special music event!\n";
            it->second.eventInfo();
        }
        else if (it2 != DB::getInstance()->getTastingEvents().end())
        {
            cout << "Today is a special event!\n";
            it2->second.eventInfo();
        }
        else
            cout << "There's no event today\n";
        cout << "------------------WELCOME TO COOL COFFEE!------------------\n";
        ret = action();

    } while (ret != -1);

    return 0;
}