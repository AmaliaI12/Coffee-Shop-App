#ifndef RAPORT_H
#define RAPORT_H

#include <iomanip>
#include "..\lib\data.hpp"

//using tamplate to generate raport in multiple languages
template <typename Lang>
class Raport {
public:
    static void generate(const string &filename);
};

class Romanian {
public:
    static std::string header() {
        return "Produs,Cantitate,Pret,Cost,Profit\n";
    }

    static std::string totalProfitLabel() {
        return "Profit total";
    }

    static std::string employeeHeader() {
        return "Angajat,Functie,Salariu\n";
    }

    static std::string totalSalaryLabel() {
        return "Salarii totale";
    }
};

class English {
public:
    static std::string header() {
        return "Product,Quantity,Price,Cost,Profit\n";
    }

    static std::string totalProfitLabel() {
        return "Total Profit";
    }

    static std::string employeeHeader() {
        return "Employee,Position,Salary\n";
    }

    static std::string totalSalaryLabel() {
        return "Total Salaries";
    }
};
#endif
