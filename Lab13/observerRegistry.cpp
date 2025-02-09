// Keegan Calkins

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout; using std::endl;
using std::map; using std::set;
using std::string;
using std::vector;

class Observer;
class Subject;

class EventRegistry{
public:
   static void registerObserver(string, Observer*);
   static void deregisterObserver(string, Observer*);
   static void handleMessage(string);
private:
   // each subject will key the registry using a map of string, observer pairs
   static map<string, map<string, Observer*>> observerMap_;
};

// initialize the static map
map<string, map<string, Observer*>> EventRegistry::observerMap_;


class Observer{
public:
   Observer(const string &name): name_(name) {}
   string getName() const {return name_;}
   void subscribe(string s) {EventRegistry::registerObserver(s, this);}
   void unsubscribe(string s){EventRegistry::deregisterObserver(s, this);}
   void handleMessage(string);
private:
   string name_;
};

class Subject{
public:
   Subject(const string &name): name_(name) {}
   string getName() const {return name_;}
   void generateMessage(){
      cout << name_ << " sent a message" << endl;
      EventRegistry::handleMessage(name_);}
private:
   string name_;
};

void EventRegistry::registerObserver(string s, Observer* o){
   // get map from current subject calling the handle on observer
   auto& nestedMap = observerMap_[s];

   // key map using string of observer's name_ object
   nestedMap[o->getName()] = o;
   cout << o->getName() << " subscribed to " << s << endl;
}

void EventRegistry::deregisterObserver(string s, Observer* o){
   // get map from current subject calling the handle on observer
   auto& nestedMap = observerMap_[s];

   // key map using string of observer's name_ object
   nestedMap.erase(o->getName());
   cout << o->getName() << " unsubscribed from " << s << endl;
}

void EventRegistry::handleMessage(string s){
   // get map from current subject name calling the handle on observer
   const auto nestedMap = observerMap_[s];
   for (auto e: nestedMap)
      e.second->handleMessage(s);
}

// observer's name_, then subject's name 
void Observer::handleMessage(string s) {
   cout << name_ << " received message from " << s << endl;
}


int main() {

   Subject  sue("Subject Sue"),  steve("Subject Steve");
   Observer olaf("Observer Olaf"), olga("Observer Olga");

   // uses string to subscribe
   olaf.subscribe(sue.getName()); olaf.subscribe(steve.getName());
   olga.subscribe(sue.getName());

   cout << endl;

   

   sue.generateMessage();
   steve.generateMessage();
   cout << endl;
   
   // uses string to unsubscribe
   olga.unsubscribe(sue.getName());
   sue.generateMessage();   
    
}