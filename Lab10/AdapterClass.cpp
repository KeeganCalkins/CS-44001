// Keegan Calkins

#include <iostream>

using std::cout; using std::endl;
using std::cin;

// target interface
class Square {
public:
    virtual void draw() const = 0;
    virtual void resize(int) = 0;
    virtual ~Square(){}
};

// adaptee/implementer
class LegacyRectangle{
public:
    LegacyRectangle(int topLeftX, 
		   int topLeftY, 
		   int bottomRightX, 
		   int bottomRightY): 
        topLeftX_(topLeftX), 
        topLeftY_(topLeftY), 
        bottomRightX_(bottomRightX), 
        bottomRightY_(bottomRightY){}

    void oldDraw() const {
        for(int i=0; i < bottomRightY_; ++i){
	        for(int j=0; j < bottomRightX_; ++j)
	            if(i >= topLeftY_  && j >= topLeftX_ )
	                cout << '*';
	            else
	                cout << ' ';
	    cout << endl;
        }
    }

    void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
        topLeftX_ = topLeftX;
        topLeftY_ = topLeftY;
        bottomRightX_ = bottomRightX;
        bottomRightY_ = bottomRightY;
    }

    int getTopLeftX() {
        return topLeftX_;
    }
  
    int getTopLeftY() {
        return topLeftY_;
    }
  
    int getBottomRightX() {
        return bottomRightX_;
    } 

    int getBottomRightY() {
        return bottomRightY_;
    }

// defining top/left and bottom/right coordinates 
private: 
    int topLeftX_;
    int topLeftY_;
    int bottomRightX_;
    int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter: public Square, 
	        private LegacyRectangle {
public:
    SquareAdapter(int size): LegacyRectangle(0,0,size,size){};
    void draw() const override {
        oldDraw();
    }

    // returns size since implementation would make this
    // return size - 0
    int size() {
        return (getBottomRightX() - getTopLeftX());
    }
    // resizes in the same style as delegated constructor using new move
    void resize(int newSize) {
        move(0, 0, newSize, newSize);
    }
};


int main(){
    int userSquareSize;
    cout << "Enter an integer to be the size of the square: ";
    cin >> userSquareSize;

    Square *square = new SquareAdapter(userSquareSize);
    square->draw();

    cout << "Enter an integer to resize the square: ";
    cin >> userSquareSize;

    square->resize(userSquareSize);
    square->draw();

}