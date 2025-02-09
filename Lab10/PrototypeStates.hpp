// Keegan Calkins

#include "PrototypeScheduler.hpp"

// clones prototype process
Process* Process::clone() {
    Process *process = new Process();
    return process;
}

// state transitions member functions
// Created process
void Created::create(Process *c) {
    changeState(c, Ready::instance());
}

// Ready
void Ready::dispatch(Process *c) {
    changeState(c, Running::instance());
    cout << "Dispatching...\n";
} 

// Running
void Running::suspend(Process *c) {
    changeState(c, Ready::instance());
    cout << "Suspending...\n";
}
void Running::block(Process *c) {
    changeState(c, Blocked::instance());
    cout << "Blocking...\n";
}
void Running::exit(Process *c) {
    changeState(c, Destroyed::instance());
    cout << "Exiting...\n";
}

// Blocked
void Blocked::unblock(Process *c) {
    changeState(c, Ready::instance());
    cout << "Unblocking...\n";
}

// Process constructor
Process::Process(){
    state_=Created::instance();
    processId_ = idCount_;
    ++idCount_;
}

string Process::report(){return state_->report();}

// handles/behaviors
void Process::create(){state_->create(this);}
void Process::dispatch(){state_->dispatch(this);}
void Process::suspend(){state_->suspend(this);}
void Process::block(){state_->block(this);}
void Process::unblock(){state_->unblock(this);}
void Process::exit(){state_->exit(this);}
