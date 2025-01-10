# Cool Coffee Program

## Overview

The **Cool Coffee** program simulates a coffee shop management system that includes functionalities for:

- Managing employees and their schedules (Manager role).
- Managing product stock (Stocker role).
- Placing orders for customers, handling loyalty programs, and applying discounts (Client role).
- Data management with different cities and events.
  
This system allows managers, stockers, and clients to interact with the coffee shop’s operations. The program also handles data imports and exports related to employees, orders, products, and loyalty discounts for customers.

---

## Features

1. **Manager Features:**
   - Add, delete, or modify employee schedules.
   - Generate daily reports.
   - Manage employee data.

1. **Stocker Features:**
   - Add, delete, or update product stock.
   - Track inventory.

1. **Client Features:**
   - Place orders, select products, and choose quantities.
   - Loyalty card system to earn points and receive discounts.
   - Ability to apply discount coupons during orders.

1. **City Switching:**
   - The system supports different cities (Bucuresti, Timisoara, Sibiu, Cluj, Rm Valcea) and allows the user to switch between them, affecting available data.

1. **Events:**
   - Music or tasting events on the current date are displayed to the user.

1. **Loyalty Program:**
   - Clients can earn loyalty points and use them for discounts on future purchases.

---

## Database Management

The system interacts with a database to import and export data related to:

- **Employees** (managers, baristas, stockers)
- **Products** (menu items)
- **Orders** (client orders)
- **Loyalty Customers** (clients with loyalty cards)
- **Events** (music and testing events)

You can switch cities to import and export data related to each city's coffee shop.

---

## Example Usage

1. **Manager Logs In**:
   - Input employee ID.
   - Select an action (e.g., Add employee, Generate report).

1. **Stocker Logs In**:
   - Input employee ID.
   - Select an action (e.g., Add product, Update stock).

1. **Client Orders**:
   - Input client name.
   - Select products and quantities.
   - Apply loyalty points/discount coupons.
   - View the total.

1. **City Switching**:
   - Choose a city to import/export data.

1. **Exit**:
   - Choose "Exit" to terminate the program.

---

## OOP concepts used

1. **Classes and objects**
   - Represent entities like employees (Barista, Manager, Stocker), products, events and orders.

1. **Encapsulation**
   - Details like employee or product information are encapsulated and accessed only via specific `getter` and `setter` methods.

1. **Inheritance**
   - `Barista`, `Manager`, and `Stocker` inherit common attributes and methods (e.g., name, age) from a generic `Employee` class.
   - Specialized behaviors for each role are added in their respective classes.

1. **Polymorphism**
   - In the Employee class, methods like `logOrder()`, `addEmployee()`, `addProduct()`, `deleteProduct()`, and `stockProduct()` are defined generically but overridden in derived classes (Barista, Manager, Stocker) to provide role-specific functionality.
   - A Barista will override `logOrder()` to handle order tracking at the counter, while an Stocker will handle stock management (`addProduct()`).

1. **Abstraction**
   - The `Event` class is an abstract class that defines a blueprint for different types of events.
   - It declares pure virtual methods like `eventInfo()` and `getDate()` that must be implemented by any derived class, ensuring a consistent interface.
   - Derived classes such as `MusicEvent` and `TastingEvent` provide concrete implementations for these methods, customizing their behavior based on the event type.
   - The abstract class ensures that the application handles all events uniformly, regardless of their specific type.

1. **Templates**
   - The `Raport` class is implemented as a template that takes a `Lang` parameter, enabling the generation of reports in different languages (e.g., Romanian, English).
   - The template separates the reporting logic from the language-specific details, ensuring flexibility and scalability.
   - By passing either the `Romanian` or `English` class as the `Lang` parameter, the report dynamically adapts its headers and label based on the specified language.

1. **Exceptions**
   - The system uses `try-catch` blocks to manage user input errors and ensure that the program provides appropriate feedback without crashing.
   - In cases where an invalid action is selected (e.g., an incorrect menu option), an `invalid_argument` exception is thrown, caught, and handled.

1. **Design Patterns**

   Singleton Pattern
   - The `DB` (Database) class follows the Singleton Pattern to manage the application's data, ensuring there is only one instance of the database throughout the program's execution. This helps in managing global access to the data without creating unnecessary multiple instances of the `DB` class.
   - The instance of `DB` is created lazily, meaning it will be created only when it is needed for the first time.
