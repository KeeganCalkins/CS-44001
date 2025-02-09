// Keegan Calkins

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <map>

// for timed sleep
#include <thread>
#include <chrono>


using std::cout; using std::cin; using std::endl;
using std::string;
using std::map;

enum class AirlineLogo {AirFrance, KLM, Aeroflot, Lufthansa, Delta, United, Spirit};

// asbstract flyweight
class Logo {
public:
	virtual std::string logo() = 0;
};

// flyweight classes
class AirFrance : public Logo {
public:
	std::string logo() override { return "AIRFRANCE"; }
};

class KLM : public Logo {
public:
	std::string logo() override { return "KLM"; }
};

class Aeroflot : public Logo {
public:
	std::string logo() override { return "AEROFLOT"; }
};

class Lufthansa : public Logo {
public:
	std::string logo() override { return "LUFTHANSA"; }
};

class Delta : public Logo {
public:
	std::string logo() override { return "DELTA"; }
};

class United : public Logo {
public:
	std::string logo() override { return "UNITED"; }
};

class Spirit : public Logo {
public:
	std::string logo() override { return "SPIRIT"; }
};

// flyweight factory
class Airport {
public:
	static Logo* makeLogo(AirlineLogo l) {
		if (logos_.find(l) == logos_.end()) { // not present
			//cout << "making new logo plane\n";
			switch (l) {
				case AirlineLogo::AirFrance:
					logos_[l] = new AirFrance;
					break;
				case AirlineLogo::KLM:
					logos_[l] = new KLM;
					break;
				case AirlineLogo::Aeroflot:
					logos_[l] = new Aeroflot;
					break;
				case AirlineLogo::Lufthansa:
					logos_[l] = new Lufthansa;
					break;
				case AirlineLogo::Delta:
					logos_[l] = new Delta;
					break;
				case AirlineLogo::United:
					logos_[l] = new United;
					break;
				case AirlineLogo::Spirit:
					logos_[l] = new Spirit;
					break;
			}
		}
		return logos_[l];
	}
private:
	// static will have one map of airline logos to prevent 2 or more 
	// creation's of the same logo
	static std::map<AirlineLogo, Logo*> logos_;
};
std::map<AirlineLogo, Logo*> Airport::logos_;

// abstract mediator
class Controller{
public:
   virtual void join(class Flight*)=0;
   virtual void leave(class Flight*)=0;
   virtual void broadcast() = 0;
   virtual void observe() = 0;
};


// concrete mediator
// tower, runway clearance
class Tower: public Controller{
public:
    void join(class Flight*) override; 
    void leave(class Flight*) override;
    void broadcast() override;
    void observe() override;
private:
    std::set<class Flight*> waiting_;
};


// abstract colleague
class Flight {
public:
    Flight(Controller *controller):controller_(controller),
				  status_(Status::waiting){
        task_ = rand() % 2 ? Task::taxiing : Task::approaching;
        controller_->join(this);
    }
    void receive(const string &msg){
        if (msg.find(flightNo_) != string::npos || msg.find("all") != string::npos){
	        if(msg.find("clear") != string::npos){
	            cout << flightNo_ << " roger that, ";
	            cout << (task_ == Task::taxiing ? "taking off" : "landing") << endl;
	            status_ = Status::cleared;
	        } else if(msg.find("status") != string::npos) {
	            cout << flightNo_
		             << (status_ == Status::waiting ? " waiting to " : " cleared to ")   
	                 << (task_ == Task::taxiing ? "take off" : "land") << endl;
	        } else
	            cout << "Tower, this is " << flightNo_ << " please repeat." << endl;
        }
    }
    bool isCleared() const {return status_ == Status::cleared;}
    void proceed(){
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3+1)); // wait a while    
        // cout << flightNo_
	    //      << (task_ == Task::taxiing ? " took off" : " landed")
	    //      << ". Have a good day!" << endl; 
		
		// extra printout
		cout << "..." << logo_->logo() << logoNumber()
			 << (task_ == Task::taxiing ? " took off" : " landed") << "...\n";


        controller_->leave(this);
    }

	std::string logoNumber() {
		std::string result;
		for (int i = flightNo_.size() - 3; i < flightNo_.size(); ++i) {
			result += flightNo_[i];
		}
		return result;
	}

protected:
	Logo* logo_;
    string flightNo_;
    Controller *controller_;
    enum class Task {taxiing, approaching};  Task task_;
    enum class Status {waiting, cleared};    Status status_;
};

// concrete colleagues
class Airbus: public Flight{
public:
    Airbus(Tower *tower): Flight(tower){
        static const std::vector<string> companies = 
	        {"AirFrance", "KLM", "Aeroflot", "Lufthansa"};

		flightNo_ = companies[rand() % companies.size()];

        if (flightNo_ == "AirFrance") {
			logo_ = Airport::makeLogo(AirlineLogo::AirFrance);
		}
		if (flightNo_ == "KLM") {
			logo_ = Airport::makeLogo(AirlineLogo::KLM);
		}
		if (flightNo_ == "Aeroflot") {
			logo_ = Airport::makeLogo(AirlineLogo::Aeroflot);
		}
		if (flightNo_ == "Lufthansa") {
			logo_ = Airport::makeLogo(AirlineLogo::Lufthansa);
		}
		flightNo_ += std::to_string(rand() % 1000);
        
        cout << flightNo_ << " requesting "
	     	 << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
    }
};

class Boeing: public Flight{
public:
    Boeing(Tower *tower): Flight(tower){
        static const std::vector<string> companies = 
	        {"Delta", "United", "Spirit"};
        flightNo_ = companies[rand() % companies.size()];
        
        if (flightNo_ == "Delta") {
			logo_ = Airport::makeLogo(AirlineLogo::Delta);
		}
		if (flightNo_ == "United") {
			logo_ = Airport::makeLogo(AirlineLogo::United);
		}
		if (flightNo_ == "Spirit") {
			logo_ = Airport::makeLogo(AirlineLogo::Spirit);
		}
		flightNo_ += std::to_string(rand() % 1000);

        cout << flightNo_ << " requesting "
	         << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
    }
};


// member functions for Tower
void Tower::broadcast() {
    cout << "Tower: ";
    string msg;
    getline(cin,msg);
    if(!msg.empty())
        for(auto f: waiting_) f->receive(msg);
}


void Tower::observe() {
    auto findCleared = [](Flight *f){return f->isCleared();};
   
    auto toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);
   
    while (toProceed != waiting_.end()){ // found a cleared flight
        (*toProceed) -> proceed();
        toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);
        if(toProceed != waiting_.end())
	        cout << "MAYDAY! MAYDAY! MAYDAY! " << endl; // more than a single flight cleared
    }
}


void Tower::join(Flight *f) {
    waiting_.insert(f);
}


void Tower::leave(Flight *f) {
    waiting_.erase(f);
    delete f;
}

int main(){
    srand(time(nullptr));
    Tower jfk;

    new Boeing(&jfk);
    new Airbus(&jfk);
    new Boeing(&jfk);
    new Airbus(&jfk);

    while(true){
        jfk.broadcast();
        jfk.observe();
        if(rand() % 2){
	        if (rand() % 2)
	            new Boeing(&jfk);
	        else
	            new Airbus(&jfk);
        }
    }
}