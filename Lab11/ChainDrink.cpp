// Keegan Calkins

#include <iostream>
#include <string>
#include "ChainDrink.hpp"

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

// Method to display completed order to user
void Drink::completeOrder(std::string name, int ingredientCount) {
    cout << name << ", your " << this->getName(ingredientCount) << "is ready. "
         << "It will be $" << this->getPrice() << " please.\n";
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

// Chain of Responisbility

// Junior only makes plain coffee, or passes to Senior
Drink* JuniorBarista::handleRequest (Drink* drink, char& ingredient, int& i) {
    switch(ingredient) {
        case 'd' : {
            cout << "*Prepared by Junior Barista\n";
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
                cout << "*Prepared by Senior Barista\n";
                return drink;
            }
            default :
                return Barista::handleRequest(drink, ingredient, i);
        }
        if (ingredient != 'd') {
            cout << "\nWould you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
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
                cout << "*Prepared by Manager\n";
                return drink;
            }
            default :
                return Barista::handleRequest(drink, ingredient, i);
        }
        if (ingredient != 'd') {
            cout << "\nWould you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
            cin >> ingredient;
        }
    }
    return drink;
}


int main() {
    char inChar, ingredient;
    std::string name;

    Drink* madeDrink;

    // user input to switch dynamically allocating drink using DrinkType and initial price
    cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
    cin >> inChar;
    switch(inChar) {
        case 'l' : {
            madeDrink = new Drink(DrinkType::large, 10);
            break;
        }
        case 'm' : {
            madeDrink = new Drink(DrinkType::medium, 7);
            break;
        }
        case 's' : {
            madeDrink = new Drink(DrinkType::small, 5);
            break;
        }
        default :
            cout << "choose a valid response\n";
    }
    // initializing barista using chain of responsibilty design pattern
    Barista* newBarista = new JuniorBarista(new SeniorBarista(new Manager));
    int i = 0;
    
    cout << "\nWould you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
    cin >> ingredient;
    madeDrink = newBarista->handleRequest(madeDrink, ingredient, i);

    cout << "\nCan I get your name? ";
    cin >> name;

    madeDrink->completeOrder(name, i);
    delete madeDrink;
}