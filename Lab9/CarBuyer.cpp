// Keegan Calkins

#include <iostream>
#include <vector>
#include <cstdlib>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot{
public:
    CarLot();
    Car *testDriveCar(){return lot_[vehicleIndex_];}
    
    // if a car is bought, requests a new one to replace bought
    Car *buyCar(){ 
        Car *bought = lot_[vehicleIndex_];
        lot_[vehicleIndex_] = factories_[rand()%factories_.size()]->requestCar();
        return bought;
    }
    
    void nextCar() {
        ++vehicleIndex_;
        // if vehicle index greater than final index set index to 0
        if (vehicleIndex_ == LOT_SIZE) {
            vehicleIndex_ = 0;
        }
    }
    int lotSize() {
        return LOT_SIZE;
    }
		     
private:
    const int LOT_SIZE = 8;
    int vehicleIndex_ = 0;
    //Car *car4sale_; // single car for sale at the lot
    vector<Car*> lot_;
    vector<CarFactory *> factories_;
};


CarLot::CarLot(){
    // creates 2 Ford factories and 2 Toyota factories 
    factories_.push_back(new FordFactory());   
    factories_.push_back(new ToyotaFactory());
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());

    // fills lot with cars 
    for (int i = 0; i < LOT_SIZE; ++i) {
        lot_.push_back(factories_[rand() % factories_.size()] -> requestCar());
    }
}

CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id){
    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();
    
    // gets random Toyota model that Jill will buy if it is shown
    ToyotaFactory *jillFactory = new ToyotaFactory();
    Car *jillCar = jillFactory->requestCar();

    cout << "\nJill Toyoter " << id << " wants a Toyota " << jillCar->getModel() << "\n";
    
    for (int i = 0; i < carLotPtr->lotSize(); ++i) {
        // set object to car in lot to observe
        Car *toBuy = carLotPtr -> testDriveCar();
        cout << " test driving " 
            << toBuy->getMake() << " "
            << toBuy->getModel();

        // if car from lot matches Jill's favorite car, she will buy it 
        // and it will be replaced, else move to next car
        if (toBuy->getMake() == jillCar->getMake() && toBuy->getModel() == jillCar->getModel()) {
            cout << " love it! buying it!" << endl;
            
            Car *boughtCar = carLotPtr -> buyCar();
            cout << boughtCar->getMake() << " " << boughtCar->getModel()
                 << " replaced with a " << carLotPtr->testDriveCar()->getMake() << " " 
                 << carLotPtr->testDriveCar()->getModel() << "\n";
            break;
        } else
            cout << " did not like it!" << endl;
            carLotPtr->nextCar();
    }

    // deallocate objects
    delete jillFactory;
    delete jillCar;

    delete carLotPtr;
    carLotPtr = nullptr;
}

// test-drives a car
// buys it if Ford
void fordLover(int id){
    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();
    
    // gets random Ford model that Jack will buy if it is shown
    FordFactory *jackFactory = new FordFactory();
    Car *jackCar = jackFactory->requestCar();
    
    cout << "\nJack Fordman " << id << " wants a Ford " << jackCar->getModel() << "\n";
    
    for (int i = 0; i < carLotPtr->lotSize(); ++i) {
        // set object to car in lot to observe
        Car *toBuy = carLotPtr -> testDriveCar();
        cout << " test driving "
            << toBuy->getMake() << " "
            << toBuy->getModel();
    
        // if car from lot matches Jack's favorite car, he will buy it
        // and it will be replaced, else move to next car
        if (toBuy->getMake() == jackCar->getMake() && toBuy->getModel() == jackCar->getModel()){
            cout << " love it! buying it!" << endl;
            
            Car *boughtCar = carLotPtr -> buyCar();
            cout << jackCar->getMake() << " " << jackCar->getModel()    
                 << " replaced with a " << toBuy->getMake() << " " 
                 << toBuy->getModel() << "\n";
            break;
        } else
            cout << " did not like it!" << endl;
            carLotPtr->nextCar();
    }

    // deallocate objects
    delete jackFactory;
    delete jackCar;

    delete carLotPtr;
    carLotPtr = nullptr;
}



int main() {
    srand(time(nullptr));

    const int numBuyers=20;
    for(int i=0; i < numBuyers; ++i)
        if(rand()% 2 == 0)
	        toyotaLover(i);
        else
	        fordLover(i);
}