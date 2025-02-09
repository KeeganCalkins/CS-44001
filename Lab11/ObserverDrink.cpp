// Keegan Calkins

#include <iostream>
#include <string>
#include "ObserverDrink.hpp"

// Drink
int Drink::getPrice() const {
    return price_;
}

// Based on DrinkType and ingredientCount, choose original name string
std::string Drink::getName(int ingredientCount) const {
    std::string drinkName;
    switch(type_) {
        case DrinkType::small : {
            if (ingredientCount > 0) { drinkName = "small coffee with "; }
            else drinkName = "small coffee ";
            break;
        }
        case DrinkType::medium : {
            if (ingredientCount > 0) { drinkName = "medium coffee with "; }
            else drinkName = "medium coffee ";
            break;
        }
        case DrinkType::large : {
            if (ingredientCount > 0) { drinkName = "large coffee with "; }
            else drinkName = "large coffee ";
            break;
        }
        default :
            cout << "error ";
    }
    return drinkName;
}

// Method to display completed order to observers
void Barista::completeOrder(int& ingredientCount) {
    // Chooses random order to fulfill
    customerId_ = rand() % customers_.size();

    cout << customers_[customerId_]->getName() << ", your " 
         << customers_[customerId_]->getDrink()->getName(ingredientCount) << "is ready. "
         << "It will be $" << customers_[customerId_]->getDrink()->getPrice() << " please.\n";

    this->alertObserver();
    this->removeCustomer(customerId_);

    ingredientCount = 0;
}


// Sugar
int Sugar::getPrice() const {
    return wrapped_->getPrice() + 1;
}

std::string Sugar::getName(int ingredientCount) const {
    return wrapped_->getName(ingredientCount) + "sugar, ";
}

// Cream
int Cream::getPrice() const {
    return wrapped_->getPrice() + 2;
}

std::string Cream::getName(int ingredientCount) const {
    return wrapped_->getName(ingredientCount) + "cream, ";
}

// Honey
int Honey::getPrice() const {
    return wrapped_->getPrice() + 3;
}

std::string Honey::getName(int ingredientCount) const {
    return wrapped_->getName(ingredientCount) + "honey, ";
}

// Observer

void Barista::addCustomer(Customer* customer) {
    customers_.push_back(customer);
    cout << "Please wait, " << customer->getName() << ".\n";
}
void Barista::removeCustomer(int customerId) {
    customers_.erase(customers_.begin() + customerId);
}

void Barista::alertObserver() const {
    for (auto c : customers_) { c->alert(); }
}


void Customer::alert() const {
    if (this->name_ == cBarista_->getCustName()) {
        cout << "This is " << name_ 
             << ", I got my coffee, thank you!\n";
    } else {
        cout << this->name_ << " sees it is not their coffee\n";
    }
}

// Chain of Responisbility

// Junior only makes plain coffee, or passes to Senior
Drink* JuniorBarista::handleRequest (Drink* drink, char& ingredient, int& i) {
    char inChar;
    cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
    cin >> inChar;
    switch(inChar) {
        case 'l' : {
            drink = new Drink(DrinkType::large, 10);
            break;
        }
        case 'm' : {
            drink = new Drink(DrinkType::medium, 7);
            break;
        }
        case 's' : {
            drink = new Drink(DrinkType::small, 5);
            break;
        }
        default :
            cout << "not valid, giving medium\n";
            drink = new Drink(DrinkType::medium, 7);
    }
    cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
    cin >> ingredient;
    
    switch(ingredient) {
        case 'd' : {
            cout << "\n*Prepared by Junior Barista\n\n";
            return drink;
        }
        default :
            return Barista::handleRequest(drink, ingredient, i);
    }
}

// Senior only makes sugar/cream coffee, or passes to Manager
Drink* SeniorBarista::handleRequest (Drink* drink, char& ingredient, int& i) {
    while (true) {
        switch(ingredient) {
            case 's' : {
                drink = new Sugar(drink);
                ++i;
                break;
            }
            case 'c' : {
                drink = new Cream(drink);
                ++i;
                break;
            }
            case 'd' : {
                cout << "\n*Prepared by Senior Barista\n\n";
                return drink;
            }
            default :
                return Barista::handleRequest(drink, ingredient, i);
        }
        if (ingredient != 'd') {
            cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
            cin >> ingredient;
        }
    }
    return drink;
}

// Senior makes coffee with all ingredients
Drink* Manager::handleRequest (Drink* drink, char& ingredient, int& i) {
    while (true) {
        switch(ingredient) {
            case 's' : {
                drink = new Sugar(drink);
                ++i;
                break;
            }
            case 'c' : {
                drink = new Cream(drink);
                ++i;
                break;
            }
            case 'h' : {
                drink = new Honey(drink);
                ++i;
                break;
            }
            case 'd' : {
                cout << "\n*Prepared by Manager\n\n";
                return drink;
            }
            default :
                return Barista::handleRequest(drink, ingredient, i);
        }
        if (ingredient != 'd') {
            cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
            cin >> ingredient;
        }
    }
    return drink;
}


int main() {
    srand(time(nullptr));

    const int CUSTOMER_COUNT = 3;
    int custCnt = 0, ingCnt = 0;
    char ingredient;
    std::string name;

    Barista* newBarista = new JuniorBarista(new SeniorBarista(new Manager));
    Customer* newCustomer;
    Drink* customerDrink;
    
    while (custCnt < CUSTOMER_COUNT || newBarista->anyOrders()) {
        int newOrder = rand() % 2;
        if (!newOrder && custCnt < CUSTOMER_COUNT) {
            char ingredient;
            
            customerDrink = newBarista->handleRequest(customerDrink, ingredient, ingCnt);

            cout << "Can I get your name? ";
            cin >> name;
            
            newCustomer = new Customer(name, customerDrink, newBarista);
            newBarista->addCustomer(newCustomer);
            cout << '\n';
            
            ++custCnt;
        } else if (newOrder && newBarista->anyOrders()) {
            newBarista->completeOrder(ingCnt);
        }
    }
    delete newBarista;
    delete newCustomer;
    delete customerDrink;
}