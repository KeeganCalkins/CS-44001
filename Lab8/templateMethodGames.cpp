// Keegan Calkins

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl;
using std::cin;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
    Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

    // template method
    void playGame(const int playersCount = 0) {
        playersCount_ = playersCount;
        movesCount_=0;

        initializeGame();

        for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
	    makeMove(i);
	    if (i==playersCount_-1) 
	        ++movesCount_; 
        }
        printWinner();
    }

    virtual ~Game(){}

protected:
    // primitive operations
    virtual void initializeGame() = 0;
    virtual void makeMove(int player) = 0;
    virtual void printWinner() = 0;
    virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
    static const int noWinner=-1;

    int playersCount_;
    int movesCount_;
    int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
    // implementing concrete methods
    void initializeGame(){
        playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
    }

    void makeMove(int player) {
        if (movesCount_ > minMoves_) { 
	        const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
	        if (chance < movesCount_) playerWon_= player;
        }
   }

   void printWinner(){
        cout << "Monopoly, player "<< playerWon_<< " won in "
	    << movesCount_<< " moves." << endl;
   }

private:
    static const int numPlayers_ = 8; // max number of players
    static const int minMoves_ = 20; // nobody wins before minMoves_
    static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
    void initializeGame(){
        playersCount_ = numPlayers_; // initalize players
        for(int i=0; i < numPlayers_; ++i) 
	        experience_[i] = rand() % maxExperience_ + 1 ; 
    }

    void makeMove(int player){
        if (movesCount_ > minMoves_){
	        const int chance = (rand() % maxMoves_) / experience_[player];
	        if (chance < movesCount_) playerWon_= player;
        }
    }

    void printWinner(){
        cout << "Chess, player " << playerWon_ 
	    << " with experience " << experience_[playerWon_]
	    << " won in "<< movesCount_ << " moves over"
	    << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
            << endl;
    }

private:
    static const int numPlayers_ = 2;
    static const int minMoves_ = 5; // nobody wins before minMoves_
    static const int maxMoves_ = 100; // somebody wins before maxMoves_
    static const int maxExperience_ = 5; // player's experience
                              // the higher, the greater probability of winning
    int experience_[numPlayers_]; 
};

// Dice - another game implementing
// primitive operations
class Dice: public Game {
public:
    void initializeGame(){
        playersCount_ = numPlayers_;    // initalize players 
        for (auto& player : passArr) {  // initialize bool arr for passing
            player = false;
        }
    }

    void makeMove(int player) {
        int currentScore = 0;
        // when game is over decide winner
        if (movesCount_ == maxMoves_) {
            playerWon_ = scoreArr[0] > scoreArr[1] ? 0 : 1;
            // reset scores after each game
            for (auto& player : scoreArr) {
                player = 0;
            }
        } else {
            if (player == 1) {
                cout << "You rolled: ";
            } else 
                cout << "\nRound " << movesCount_ + 1 << ": " << "Computer rolled: ";
            // when current player does not pass
            if (!passArr[player]) {
                int currentRoll = 0;
                // output the roll and add it to round's total score
                for(int i = 0; i < numRolls_; ++i) {
                    currentRoll = rand() % 6 + 1;
                    currentScore += currentRoll;
                    
                    cout << currentRoll;
                    if (i != numRolls_-1) {cout << ' ';}
                }
                // when the current round's score is higher than the high score,
                // set players high score as round score
                if (scoreArr[player] < currentScore) {
                    scoreArr[player] = currentScore;
                }
                cout << ", ";
            } else  // denote player passed and reset pass value
                cout << "passed, ";
                // passArr[player] = false;
            if (player == 1) {
                cout << "your score = " << scoreArr[player] << "\n";
            } else {
                cout << "computer's score = " << scoreArr[player] << "\n";
            }
            // when real player's turn, ask if they want to pass
            if (!passArr[player] && player == 1 && movesCount_ < maxMoves_ - 1) {
                cout << "Roll again? [y/n] ";
                char passInp;
                cin >> passInp;
                if (passInp == 'n') {
                    passArr[player] = true;
                } else if ( passInp != 'y') {
                    cout << "Input invalid character, rolling again.";
                }
                // cout << "\n";
            }
            // computer player will randomly pass on any round
            if (!passArr[player] && player == 0 && movesCount_ < maxMoves_) {
                passArr[player] = rand() % 2;
            }
        }
    }

    void printWinner() {
        if (playerWon_ != 0) {
            cout << "You Win\n\n";
        } else 
            cout << "You Lose\n\n";
    }

private:
    static const int numPlayers_ = 2;
    static const int minMoves_ = 1; // nobody wins before minMoves_
    static const int maxMoves_ = 3; // somebody wins before maxMoves_
    static const int numRolls_ = 5;
    static const int maxRoll_ = 6;
    int scoreArr[numPlayers_];
    bool passArr[numPlayers_];
};

int main() {
    srand(time(nullptr));

    Game* gp = nullptr;

    // play chess 7 times
    for (int i = 0; i < 7; ++i){ 
        gp = new Chess;
        gp -> playGame(); 
        delete gp;
    }
      

   // play monopoly 7 times
    for (int i = 0; i < 7; ++i){
        gp = new Monopoly;
        gp -> playGame(); 
        delete gp;
    }
    // play Dice 7 times
    for (int i = 0; i < 7; ++i){ 
        gp = new Dice;
        gp -> playGame(); 
        delete gp;
    }
}