// Keegan Calkins
#ifndef OBSERVERRINK_HPP_
#define OBSERVERRINK_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using std::cout; using std::cin;
using std::vector;
using std::find;

enum class DrinkType {small, medium, large};

// Decorator

class Drink{
public:
    Drink(DrinkType type=DrinkType::small, int price=0):
                 type_(type), price_(price){}

    // Adds price of ingredient to wrapped object's price
    virtual int getPrice() const;
    // concatenates ingredient name to wrapped object
    // passed int used to add "with " to name string
    virtual std::string getName(int) const;

private: 
    int price_;
    DrinkType type_;
};

class Sugar : public Drink {
public:
    Sugar(const Drink* wrapped) : wrapped_(wrapped) {}

    int getPrice() const override;
    std::string getName(int) const override;
private:
    const Drink *wrapped_;
};

class Cream : public Drink {
public:
    Cream(const Drink* wrapped) : wrapped_(wrapped) {}

    int getPrice() const override;
    std::string getName(int) const override;
private:
    const Drink *wrapped_;
};

class Honey : public Drink {
public:
    Honey(const Drink* wrapped) : wrapped_(wrapped) {}

    int getPrice() const override;
    std::string getName(int) const override;
private:
    const Drink *wrapped_;
};

// Observer
 
class Barista;

class Customer {
public:
    // constructor
    Customer(std::string name, Drink* drink, Barista* barista) : 
        name_(name), cDrink_(drink), cBarista_(barista) {}
    
    std::string getName() const {return name_;}
    Drink* getDrink() const {return cDrink_;}

    // Push alert to current customer
    void alert() const;
private:
    std::string name_;
    Drink* cDrink_;
    Barista* cBarista_;
};

// Chain

class Barista {
public:
    // constructs the successor of each barista level allocating an address
    Barista(Barista *successor = nullptr):successor_(successor){} 
    
    std::string getCustName() {
        return customers_[customerId_]->getName();
    }

    // Will add or remove observer
    void addCustomer(Customer*);
    void removeCustomer(int);

    // pushes alert to observer vector
    void alertObserver() const;

    // checks if there are any observers
    bool anyOrders() { return !(customers_.empty()); }
    
    void completeOrder(int&);

    // This method to be overridden will have the lowest level barista, that
    // is allowed to, make the requested drink using ingredient.
    virtual Drink* handleRequest (Drink* drink, char& ingredient, int& i) {
        if (successor_ != nullptr)
	        return successor_->handleRequest(drink, ingredient, i);
        else 
	        cout << "nobody can handle this request, you will recieve plain\n";
            return drink;
    }
private:
    Barista *successor_;
    vector<Customer*> customers_;
    int customerId_;
};

class JuniorBarista : public Barista {
public:
    JuniorBarista(Barista* successor=nullptr):Barista(successor){} 
    Drink* handleRequest (Drink*, char&, int&);
};

class SeniorBarista : public Barista {
public:
    SeniorBarista(Barista* successor=nullptr):Barista(successor){} 
    Drink* handleRequest (Drink*, char&, int&);
};

class Manager : public Barista {
public:
    Manager(Barista* successor=nullptr):Barista(successor){} 
    Drink* handleRequest (Drink*, char&, int&);
};

#endif