// Keegan Calkins

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

// Decorators
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

    // User input to switch Decorating original object with ingredients
    int i = 0;
    while (ingredient != 'd') {
        cout << "\nWould you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
        cin >> ingredient;

        switch(ingredient) {
            case 's' : {
                madeDrink = new Sugar(madeDrink);
                ++i;
                break;
            }
            case 'c' : {
                madeDrink = new Cream(madeDrink);
                ++i;
                break;
            }
            case 'h' : {
                madeDrink = new Honey(madeDrink);
                ++i;
                break;
            }
            case 'd' : {
                break;
            }
            default :
                cout << "choose a valid response\n";
        }
    }
    cout << "\nCan I get your name? ";
    cin >> name;

    madeDrink->completeOrder(name, i);
    delete madeDrink;
}