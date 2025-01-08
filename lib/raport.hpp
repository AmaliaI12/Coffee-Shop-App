#ifndef RAPORT_H
#define RAPORT_H

#include <iomanip>
#include "data.hpp"

//using tamplate to generate raport in multiple languages
template <typename Lang>
class Raport {
public:
    static void generate(const string &filename);
};

class Romanian {
public:
    static string header() {
        return "Produs,Cantitate,Pret,Cost,Profit\n";
    }

    static string totalProfitLabel() {
        return "Profit total";
    }

    static string employeeHeader() {
        return "Angajat,Functie,Salariu\n";
    }

    static string totalSalaryLabel() {
        return "Salarii totale";
    }
};

class English {
public:
    static string header() {
        return "Product,Quantity,Price,Cost,Profit\n";
    }

    static string totalProfitLabel() {
        return "Total Profit";
    }

    static string employeeHeader() {
        return "Employee,Position,Salary\n";
    }

    static string totalSalaryLabel() {
        return "Total Salaries";
    }
};
#endif
