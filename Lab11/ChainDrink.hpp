// Keegan Calkins
#ifndef CHAINDRINK_HPP_
#define CHAINDRINK_HPP_

#include <iostream>
#include <string>

using std::cout; using std::cin;

enum class DrinkType {small, medium, large};

class Drink{
public:
    Drink(DrinkType type=DrinkType::small, int price=0):
                 type_(type), price_(price){}

    // Adds price of ingredient to wrapped object's price
    virtual int getPrice() const;
    // concatenates ingredient name to wrapped object
    // passed int used to add "with " to name string
    virtual std::string getName(int) const;

    void completeOrder(std::string, int);
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

class Barista {
public:
    // constructs the successor of each barista level allocating an address
    Barista(Barista *successor = nullptr):successor_(successor){} 

    // This method to be overridden will have the lowest level barista, that
    // is allowed to, make the requested drink using ingredient.
    virtual Drink* handleRequest (Drink* drink, char& ingredient, int& i) {
        if (successor_ != nullptr)
	        return successor_->handleRequest(drink, ingredient, i);
        else 
	        cout << "nobody can handle this request\n";
            return drink;
    }
private:
    Barista *successor_;
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