// Keegan Calkins

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::priority_queue;

struct Lemon {
    double quality;
    friend bool operator<(const Lemon& left, const Lemon& right) {
        return left.quality < right.quality;
    }
};

const int maxBoxSize = 30;
const int highestQuality = 10;

int main() {
    srand(time(nullptr));
    vector <Lemon> box(rand() % maxBoxSize + 1); // random box size

    // random quality assingment
    for (auto& lemon : box)
        lemon.quality = static_cast<double>(rand()) / RAND_MAX * highestQuality;
    
    priority_queue<Lemon> boxQueue;

    for (auto lemon : box) {    // push each element from vec onto prio queue
        boxQueue.push(lemon);
    }
    cout << "Here are the lemons (best first): ";

    // replace this code with priority queue
    // loop printing top quality then pop top
    while (!boxQueue.empty()) {
        cout << boxQueue.top().quality << ", ";
        boxQueue.pop();
    }
    cout << endl;
}
