// Keegan Calkins

#include <iostream>
#include <string>
using std::cin; using std::cout; using std::endl; using std::string;

class State;

// context
class Process {
public:
    Process();

    // behaviors
    void create();
    void dispatch();
    void suspend();
    void block();
    void unblock();
    void exit();
    string report();

    // part of implementation of state pattern
    void changeState(State* state){state_=state;}
private:
    State* state_;
};

// absract state
class State{
public:
    // provides default implementation
    virtual void create(Process*){} 
    virtual void dispatch(Process*){} 
    virtual void suspend(Process*){} 
    virtual void block(Process*){} 
    virtual void unblock(Process*){}  
    virtual void exit(Process*){}

    virtual string report() =0;
    void changeState(Process* c, State* s){
        c->changeState(s);
    }
};

class Created: public State{
public:
    static State* instance(){
        static State* onlyInstance = new Created;
        return onlyInstance;
    }
    // Created can only create
    void create(Process*) override;
    string report() override {return "Created";}
private:
    Created(){}
    Created(const Created&) = delete;
    Created& operator=(const Created&) = delete;
};

class Ready: public State{
public:
    static State* instance(){
        static State* onlyInstance = new Ready;
        return onlyInstance;
    }
    // Ready can only dispatch
    void dispatch(Process*) override;
    string report() override {return "Ready";}
private:
    Ready(){}
    Ready(const Ready&) = delete;
    Ready& operator=(const Ready&) = delete;
};


class Running: public State{
public:
    static State* instance(){
        static State* onlyInstance = new Running;
        return onlyInstance;
    }
    // Running can only suspend, block, and exit
    void suspend(Process*) override;
    void block(Process*) override;
    void exit(Process*) override;
    string report() override {return "Running";}
private:
    Running(){}
    Running(const Running&) = delete;
    Running& operator=(const Running&) = delete;
};


class Blocked: public State{
public:
    static State* instance(){
        static State* onlyInstance = new Blocked;
        return onlyInstance;
    }
    // Blocked can only unblock
    void unblock(Process*) override;
    string report() override {return "Blocked";}
private:
    Blocked(){}
    Blocked(const Blocked&) = delete;
    Blocked& operator=(const Blocked&) = delete;
};

class Destroyed: public State{
public:
    static State* instance(){
        static State* onlyInstance = new Destroyed;
        return onlyInstance;
    }
    string report() override {return "Destroyed";}
private:
    Destroyed(){}
    Destroyed(const Destroyed&) = delete;
    Destroyed& operator=(const Destroyed&) = delete;
};


// state transitions member functions
// Created process
void Created::create(Process *c) {
    changeState(c, Ready::instance());
}

// Ready
void Ready::dispatch(Process *c) {
    changeState(c, Running::instance());
} 

// Running
void Running::suspend(Process *c) {
    changeState(c, Ready::instance());
}
void Running::block(Process *c) {
    changeState(c, Blocked::instance());
}
void Running::exit(Process *c) {
    changeState(c, Destroyed::instance());
}

// Blocked
void Blocked::unblock(Process *c) {
    changeState(c, Ready::instance());
}

// Process member functions
Process::Process(){state_=Created::instance();}

// handles/behaviors
void Process::create(){state_->create(this);}
void Process::dispatch(){state_->dispatch(this);}
void Process::suspend(){state_->suspend(this);}
void Process::block(){state_->block(this);}
void Process::unblock(){state_->unblock(this);}
void Process::exit(){state_->exit(this);}

string Process::report(){return state_->report();}

int main(){
    Process Process1;
    cout << "Process1 is " << Process1.report() << endl;

    // operating system scheduler controlled by user input
    while(Process1.report() != "Destroyed"){
        cout << "What would you like Process to do? Create, suspend, dispatch, block, unblock, or exit [c, s, d, b, u , e] ";
        char action; cin >> action;
        switch (action) {
        case 'c':
            Process1.create();
            break;
        case 's':
            Process1.suspend();
            break;
        case 'd':
            Process1.dispatch();
            break;
        case 'b':
            Process1.block();
            break;
        case 'u':
            Process1.unblock();
            break;
        case 'e':
            Process1.exit();
            break;
        default:
            cout << "Enter a valid character, " << action << " is not valid.\n";
        }
        cout << "Process1 is " << Process1.report() << endl;
    }

   
    // demonstrates that two Processs 
    // may be in two different states
    Process Process2;
    Process2.create();
    Process2.dispatch();

    cout << "Process1 is " << Process1.report() << " while "
         << "Process2 is " << Process2.report() << endl;
   
}