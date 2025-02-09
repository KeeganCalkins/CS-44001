// Keegan Calkins
#include <iostream>
#include <string>
#include <queue>
#include <deque>

#ifndef SCHEDULER_
#define SCHEDULER_

using std::cin; using std::cout; using std::endl; using std::string;
using std::queue;
using std::deque;

class State;

// context
class Process {
public:
    Process();
    Process* clone();
    int getId() { return processId_; }
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
    static int idCount_;
    int processId_;
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
    string report() override {
        return "created\n";
    }
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
    string report() override {
        return "READY\n";
    }
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
    string report() override {
        return "RUNNING\n";
    }
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
    string report() override {
        return "BLOCKED\n";
    }
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
    string report() override {
        return "exited\n";
    }
private:
    Destroyed(){}
    Destroyed(const Destroyed&) = delete;
    Destroyed& operator=(const Destroyed&) = delete;
};

#endif //SCHEDULER_