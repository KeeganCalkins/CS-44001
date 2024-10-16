// Keegan Calkins

#include <iostream>
#include <string>
#include <fstream>

using std::cout; using std::endl;
using std::string;
using std::ofstream; using std::fstream;

class Logger {
public:
    // one instance of Logger object's address returned
    static Logger& instance() {
        static Logger logger;
        return logger;
    }
    void report(const string& txt) {
        fo_ << txt << endl;
    }

private:
    // prevents Logger copy and creation
    Logger();
    Logger(const Logger&) {}
    Logger & operator=(const Logger&) {}

    static void closeLog();
    ofstream fo_;
};

// open file for appending
Logger::Logger() {
    fo_.open("out.txt", fstream::out | fstream::app);
    atexit(closeLog);
}

void Logger::closeLog() {
    Logger::instance().fo_.close();
    // cout << "closed\n";
}

void func1() {
  Logger::instance().report("func1 Report");  
}
void func2() {
  Logger::instance().report("func2 Report");  
}

int main() {
    Logger& logger1 = Logger::instance();
    Logger& logger2 = Logger::instance();
    logger1.report("Report 1 Logger 1");
    logger2.report("Report 1 Logger 2");

    func1();
    func2();
}