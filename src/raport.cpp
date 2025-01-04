#include "..\lib\raport.hpp"

template <typename Lang>
void Raport<Lang>::generate(const string &filename)
{
    ofstream file(filename);

    // write the header
    file << Lang::header();

    double totalProfit = 0.0;

    for (auto order : DB::getInstance()->getOrders())
    {
        for (auto item : order.getItems())
        {
            auto product = item.product;
            int quantity = item.numPcs;
            double price = product.getPrice();
            double cost = product.getCost();
            double profit = (price - cost) * quantity;
            totalProfit += profit;

            file << product.getName() << ","
                 << quantity << ","
                 << fixed << setprecision(2) << price << ","
                 << cost << ","
                 << profit << "\n";
        }
    }

    // write the total profit
    file << '\n'
         << Lang::totalProfitLabel() << ","
         << fixed << setprecision(2) << totalProfit << '\n';

    // write the employee salary section
    file << Lang::employeeHeader();

    double totalSalaries = 0.0;

    for (auto [id, employee] : DB::getInstance()->getEmployees())
    {
        file << employee.getName() << ","
             << employee.getJobTitle() << ","
             << fixed << setprecision(2) << employee.getSalary() << "\n";
        totalSalaries += employee.getSalary();
    }

    file << "\n"
         << Lang::totalSalaryLabel() << ","
         << fixed << setprecision(2) << totalSalaries;

    file.close();
}

// Explicit template instantiation
template class Raport<Romanian>;
template class Raport<English>;
