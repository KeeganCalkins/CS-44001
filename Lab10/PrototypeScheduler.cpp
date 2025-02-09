// Keegan Calkins

#include "PrototypeScheduler.hpp"
#include "PrototypeStates.hpp"

class Scheduler {
public:
    Scheduler();

    void createProcess();

    void scheduleProcesses(int);
private:
    Process* processPtr_;
    queue<Process*> readyQ_;
    queue<Process*> blockedQ_;
    deque<Process*> reportDQ_;
};

Scheduler::Scheduler() {
    processPtr_ = new Process();
}

void Scheduler::createProcess() {
    Process* temp = processPtr_->clone();
    temp->create();
    cout << "PID " << temp->getId() << " state: " << temp->report();
    
    // placing process on ready queue for functionality
    // and on report deque to display state to user
    readyQ_.push(temp);
    reportDQ_.push_back(temp);
}

void Scheduler::scheduleProcesses(int processCount) {
    // creates input value number of processes
    for (int i = 0; i < processCount; ++i) {
        cout << "PID " << i+1 << ": process created\n";
        createProcess();
    }
    cout << "\n";

    while (!readyQ_.empty() || !blockedQ_.empty()) {
        // 2/3 times will unblock if blocked queue is not empty
        if ((rand() % 3) > 0 && !blockedQ_.empty()) {
            Process* temp = blockedQ_.front();
            blockedQ_.pop();
            temp->unblock();
            readyQ_.push(temp);

            cout << "PID " << temp->getId() << " state: " << temp->report();
            cout << "\n";
        }
        else if (!readyQ_.empty()) {
            // dispatches front element of ready queue if ready
            // queue is not empty
            Process* temp = readyQ_.front();
            readyQ_.pop();
            temp->dispatch();
            cout << "PID " << temp->getId() << " state: " << temp->report();

            // either exits, blocks, or suspends running process randomly
            int choice = rand() % 3;
            switch(choice) {
                // exit running process
                case 0: {
                    temp->exit();
                    cout << "PID " << temp->getId() << " state: " << temp->report();
                    cout << "\n";
                    break;
                }
                // block running process
                case 1: {
                    temp->block();
                    blockedQ_.push(temp);
                    cout << "PID " << temp->getId() << " state: " << temp->report();
                    cout << "\n";
                    break;
                }                                   
                // suspend running process
                case 2: {
                    temp->suspend();
                    readyQ_.push(temp);
                    cout << "PID " << temp->getId() << " state: " << temp->report();
                    cout << "\n";
                    break;
                }
            }
            if (readyQ_.empty()) {
                cout << "The ready queue is empty\n\n";
            }
        }
    }
    cout << "All processes exited.\n";
}


int Process::idCount_ = 0;
const int numProcesses = 4;

int main(){
    srand(time(nullptr));

    Scheduler temp;
    temp.scheduleProcesses(numProcesses);
}