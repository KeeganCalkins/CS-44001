// Keegan Calkins

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::iterator;
using std::string;
using std::vector; using std::deque;
using std::generate; using std::for_each; 
using std::count_if; using std::max_element;
using std::transform; using std::remove_if;
using std::sort; using std::accumulate;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};



int main(){
    srand(time(nullptr));
    const double minWeight = 3.;
    const double maxWeight = 8.;

    cout << "Input crate size: ";
    int size;
    cin >> size;

    vector <Apples> crate(size);

    // assign random weight and color to apples in the crate
    // replace with generate()
    generate(crate.begin(), crate.end(), [=](){
        Apples a;
        a.weight = minWeight + 
                   static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
        a.color = rand() % 2 == 1 ? "green" : "red";
        return a;
    });
    /*           
    for(auto it = crate.begin(); it != crate.end(); ++it){
        it->weight = minWeight + 
	            static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
        it->color = rand() % 2 == 1 ? "green" : "red";
    }*/


    // for_each() possibly
    cout << "all apples"<< endl;
    for_each(crate.begin(), crate.end(), [](Apples a){
        // prints each apple's color and weight
        a.print();
    });

   
    cout << "Enter weight to find: ";
    double toFind;
    cin >> toFind;

    int cnt = count_if(crate.begin(), crate.end(), [toFind](Apples a){
        // compares each apple's weight to the input
        return a.weight > toFind;
    });
    /*
    int cnt = 0;
    for(auto it = crate.cbegin(); it != crate.cend(); ++it) 
        if(it->weight > toFind) ++cnt;
    */
    cout << "There are " << cnt << " apples heavier than " 
	     << toFind << " oz" <<  endl;

    cout << "at positions ";
    // finds first apple meeting weight limit
    auto it = find_if(crate.begin(), crate.end(), [toFind](Apples a){
        // compares each apple's weight to the input
        return a.weight > toFind;
    });
    // finds the rest of apples meeting weight limit
    while(it != crate.end()) {
        cout << it - crate.begin() << ", ";
        it = find_if(it + 1, crate.end(), [toFind](Apples a){
            return a.weight > toFind;
        });
    }
    cout << endl;
    /*
    cout << "at positions ";
    for(int i=0; i < size; ++i)
        if(crate[i].weight > toFind)
	        cout << i << ", ";
    cout << endl;
    */
    // finds heaviest using comparison of lhs apple to rhs apple's weight
    auto heaviest = max_element(crate.begin(), crate.end(), 
                                  [](const Apples& lhs, const Apples& rhs){
                                  return lhs.weight < rhs.weight; });
    if (!crate.empty()) {
        cout << "Heaviest apple weighs: " << heaviest->weight << " oz" << endl;
    } else {
        cout << "Crate empty" << endl;
    }
    /*
    double heaviest = crate[0].weight;
    for(int i=1; i < size; ++i)
        if(crate[i].weight > heaviest) heaviest = crate[i].weight; 
    cout << "Heaviest apple weighs: " << heaviest << " oz" << endl;
    */

    // for_each() or accumulate()

    double sum = accumulate(crate.begin(), crate.end(), 0.0, 
                            [](double tSum, const Apples& a){
                                    // returns sum of weight
                                    return tSum + a.weight; });
    /*
    double sum = 0;
    for(int i=0; i < size; ++i)
        sum += crate[i].weight;*/
    cout << "Total apple weight is: " << sum << " oz" << endl;

    // transform();
    cout << "How much should they grow: ";
    double toGrow;
    cin >> toGrow;
    // increases the weight of each apple by input value
    transform(crate.begin(), crate.end(), crate.begin(), 
                                    [toGrow](Apples a){
        Apples temp;
        temp.color = a.color;
        temp.weight = a.weight + toGrow;
        return temp;
    });
    /*
    for(int i=0; i < crate.size(); ++i)
        crate[i].weight += toGrow;
    */

    // remove_if()
    cout << "Input minimum acceptable weight: ";
    double minAccept;
    cin >> minAccept;
    crate.erase(remove_if(crate.begin(), crate.end(), [minAccept](const Apples& a){
        // removing when the apple's weight is less than the given minimum
        return a.weight < minAccept;
    }), crate.end());
    // removing small apples
    // nested loops, replace with a single loop modification idiom
    /*
    bool removed;
    do{
        removed = false;
        for(auto it = crate.begin(); it != crate.end(); ++it)
	    if(it->weight < minAccept){
	        crate.erase(it);
	        removed = true;
	        break;
        }
    }while(removed);*/
    cout << "removed " << size - crate.size() << " elements" << endl;


    // bubble sort, replace with sort()
    // sort will use lambda function to compare each apple
    sort(crate.begin(), crate.end(), [](const Apples& a1, const Apples& a2){
        return a1.weight < a2.weight;
    });
    /*
    bool swapped;
    do{
        swapped = false;
        for(int i=0; i < crate.size()-1; ++i)
	        if(crate[i].weight > crate[i+1].weight){
	            std::swap(crate[i], crate[i+1]);
	            swapped = true;
	        }
    }while(swapped);
    */

    // prints apples from final crate
    for_each(crate.begin(), crate.end(), [](Apples a) {
        a.print();
    });
    // for_each() possibly
    /*
    cout << "sorted remaining apples"<< endl;
    for(const auto &e: crate) {
        e.print();
    }
    */
}
