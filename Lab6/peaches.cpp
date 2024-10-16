// Keegan Calkins

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::iterator;
using std::string;
using std::vector; using std::deque;
using std::generate; using std::for_each; 
using std::count_if; using std::max_element;
using std::transform; using std::remove_if;
using std::sort; using std::accumulate;
using std::bind; using namespace std::placeholders;


struct Peaches{
    double weight; // oz
    bool ripe;  // ripe or not
    void print() const { cout << (ripe?"ripe":"green") << ", " <<  weight << endl; }
};

class jamFunctor {
public:
    jamFunctor(double x) : weightToJam_(x) {}
    bool operator() (const Peaches& p) const { return p.weight < weightToJam_; }
private:
    double weightToJam_;
};



int main(){
    srand(time(nullptr));
    const double minWeight = 3.;
    const double maxWeight = 8.;

    cout << "Input basket size: ";
    int size;
    cin >> size;

    vector <Peaches> basket(size);

    // assign random weight and ripeness peaches in the basket
    // replace with generate()
    generate(basket.begin(), basket.end(), [=](){
        Peaches p;
        p.weight = minWeight + 
                   static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
        p.ripe = rand() % 2;
        return p;
    });

    /*
    for(auto it = basket.begin(); it != basket.end(); ++it){
        it->weight = minWeight + 
	           static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
        it->ripe = rand() % 2;
    }
    */
   
    // for_each() possibly
    cout << "all peaches"<< endl;
    for_each(basket.begin(), basket.end(), [](Peaches p){
        p.print();
    });

    /*
    cout << "all peaches"<< endl;
    for(const auto &e: basket) {
        e.print(); 
    }
    */

    // moving all the ripe peaches from basket to peck
    // remove_copy_if() with back_inserter()/front_inserter() or equivalents
    deque<Peaches> peck;
    // when the current peach is ripe, it is moved to the peck
    // and removed from the basket
    remove_copy_if(basket.begin(), basket.end(), 
            std::front_inserter(peck), [](Peaches& p){
        return !p.ripe;
    });


    /*
    for(auto it=basket.begin(); it != basket.end();)
        if(it->ripe){
	    peck.push_front(std::move(*it));
	    it=basket.erase(it);
    } else
	    ++it;

    // for_each() possibly
    cout << "peaches remaining in the basket"<< endl;
    for(const auto &e: basket) {
        e.print(); 
    }*/

    cout << endl;

    // for_each() possibly
    cout << "peaches moved to the peck"<< endl;
    for_each(peck.begin(), peck.end(), [](Peaches peck){
        peck.print();
    });

    /*
    for(const auto &e: peck) {
        e.print();
    }
    */

    // prints every "space" peach in the peck
    const int space=3; 
    cout << "\nevery " << space << "\'d peach in the peck"<< endl;

    // replace with advance()/next()/distance()
    auto it = peck.begin();
    // will advance once originally
    advance(it, space - 1);
    // when the current peach iterator is less that the end,
    // it will print its position and advance again
    while (it < peck.end()) {
        it->print();
        advance(it, space);
    }
    // no explicit iterator arithmetic 

    /*
    auto it=peck.cbegin(); int i = 1;   
    while(it != peck.cend()){
        if(i == space){
	        it->print();
	        i=0;
        }
        ++i; 
        ++it;
    }
    */

    // putting all small ripe peaches in a jam
    // use a binder to create a functor with configurable max weight
    // accumulate() or count_if() then remove_if()
    
    const double weightToJam = 10.0;
    double jamWeight = 0;
    // initialize functor and binder
    jamFunctor maxPeachWeight(weightToJam);
    auto jamBinder = bind(maxPeachWeight, _1);

    it = peck.begin();
    int i = 0;
    // once this loops as many times as count_if provides, 
    // each peach's weight is added to jamWeight
    while(count_if(peck.begin(), peck.end(), jamBinder) != i) {
        if (it->weight < weightToJam) {
            jamWeight += it->weight;
            ++i; ++it;
        }
    }
    // will remove the peaches that were added to the jam from the peck 
    remove_if(peck.begin(), peck.end(), jamBinder);

    /*
    double jamWeight = accumulate(peck.begin(), peck.end(), 0.0,
                            [weightToJam](double tSum, const Peaches& p, auto jamBinder){
                                // returns sum of weight
                                if (jamBinder(weightToJam)) {
                                    return tSum + p.weight;
                                }
                            });
                                
    */
    /*
    double jamWeight = 0;
    for(auto it=peck.begin(); it != peck.end();)
        if(it->weight < weightToJam){
	        jamWeight += it->weight;
	        it=peck.erase(it);
        } else
	    ++it;
    */
    cout << "Weight of jam is: " << jamWeight << endl;

}