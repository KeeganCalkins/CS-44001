// Keegan Calkins

#include <iostream>
#include <cstdlib>

using std::cout; using std::endl; using std::cin;

// abstract body 
class Fill{
public:
   Fill(char borderChar, char internalChar): borderChar_(borderChar), internalChar_(internalChar) {}
   virtual char getBorder()=0;
   virtual char getInternal()=0;
   virtual ~Fill() {}
protected:
   char borderChar_;
   char internalChar_;
};

// concrete body
class Hollow: public Fill{
public:
   // takes internalChar when constructing and passes ' ' as borderChar and internalChar
   Hollow(char borderChar):Fill(borderChar, ' '){}
   char getBorder() override {return borderChar_;}
   char getInternal() override {return internalChar_;}
   ~Hollow() override {}
};


// another concrete body
class Filled: public Fill {
public:
   // takes borderChar and passes it as both parameters when constructing
   Filled(char borderChar):Fill(borderChar, borderChar){}
   char getBorder() override {return borderChar_;}
   char getInternal() override {return borderChar_;}
   ~Filled() override {}
};

class FullyFilled: public Fill {
public:
   // takes and passes internalChar as border and borderChar as internal when constructing
   FullyFilled(char internalChar, char borderChar):Fill(internalChar, borderChar){}
   char getBorder() override {return internalChar_;}
   char getInternal() override {return borderChar_;}
   ~FullyFilled() override {}
};
class RandomFilled: public Fill {
public:
   // takes and passes internalChar and borderChar when constructing and randomly
   // selecting either to be printed for each border or internal character
   RandomFilled(char internalChar, char borderChar):Fill(internalChar, borderChar){}
   char getBorder() override {return rand() % 2 == 0 ? internalChar_ : borderChar_;}
   char getInternal() override {return rand() % 2 == 0 ? internalChar_ : borderChar_;}
   ~RandomFilled() override {}
};

// abstract handle
class Figure {
public:
   Figure(int size, Fill* fill): size_(size), fill_(fill){}
   virtual void draw() =0;
   virtual ~Figure(){}
protected:
   int size_;
   Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;

};

void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
	 if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	    cout << fill_ -> getBorder();
	 else
	    cout << fill_ -> getInternal();
      cout << endl;
   }
}

int main(){
   srand(time(nullptr));
  
   Fill* hollowPaintAmpersand = new Hollow('&');   // & is border
   Fill* filledPaintAt = new Filled('@');          // @ is internal and border
   Fill* fullyPaintMod = new FullyFilled('*','%'); // * is internal, % is border
   Fill* randomPaint = new RandomFilled('<', '='); // < or = is random for internal and border

   
   Figure *smallBox = new Square(6, hollowPaintAmpersand);
   Figure *bigBox = new Square(15, filledPaintAt);
   Figure *smallerBox = new Square(5, fullyPaintMod);
   Figure *biggerBox = new Square(17, randomPaint);
   
   cout << "Hollow:\n";
   smallBox->draw();
   cout << "\nFilled:\n";
   bigBox -> draw();
   cout << "\nFully Filled:\n";
   smallerBox->draw();
   cout << "\nRandom:\n";
   biggerBox -> draw();
   
   
   /*
   // ask user for figure parameters
   cout << "Enter fill character: "; 
            char fchar; cin >> fchar;
   cout << "Filled or hollow? [f/h] "; 
           char ifFilled; cin >> ifFilled;
   cout << "Enter size: "; int size; cin >> size;
   */
   /*
   Figure *userBox = new Square(size, ifFilled == 'f'? 
	       static_cast<Fill *>(new Filled(fchar)):
	       static_cast<Fill *>(new Hollow(fchar))
	       ); 
   */
      
   /*
   Figure *userBox = ifFilled == 'f'?
      new Square(size, new Filled(fchar)):
      new Square(size, new Hollow(fchar));
   
   
   userBox -> draw();
   cout << endl;
   */
}