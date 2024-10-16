// Keegan Calkins

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

struct Fruit{
    Variety v;
    string color; // red, green or orange
};


int main(){
    srand(time(nullptr));
    multimap<Variety, Fruit> tree;

    // random fruit and color selection
    int num = (rand() % 100) + 1;
    for(int i = 0; i < num; ++i){
        Fruit f;
        // sets key and value to be emplaced into tree
        f.v = static_cast<Variety>(rand() % 3);
        f.color = colors[rand()%3];

        tree.emplace(f.v, f);
    }

    // printing colors of oranges
    cout << "Colors of the oranges: ";

    for(auto f = tree.lower_bound(Variety::orange); 
            f != tree.upper_bound(Variety::orange); ++f) {
        cout << f->second.color << ", ";
    }
    cout << endl;

}
