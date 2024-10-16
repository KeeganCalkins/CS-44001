// check and display first difference between text files
// Keegan Calkins
// 8-21-2024

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using std::cout; using std::endl; using std::string; using std::ifstream;


int firstLineDiff(string fileOneLine, string fileTwoLine) {
    int lineOneSize = fileOneLine.length();
    int lineTwoSize = fileTwoLine.length();
    // for loop to return the index of the first difference between the lines
    // difference found if element of first and second file line are not equal
    for(int i = 0; i < lineOneSize || i < lineTwoSize; ++i) {
        if (fileOneLine[i] != fileTwoLine[i]) {
            return i;
        }
    }
    return -1; // if they are the same then return -1;
}
void compareLineOut(string fileOneName, string fileTwoName, int lineNum, 
                string fileOneLine, string fileTwoLine, bool endOfFiles) {
    int lineDiff = firstLineDiff(fileOneLine, fileTwoLine);
    // no difference will not output lines
    if(lineDiff == -1) { return; }

    // output input file's lines
    cout << fileOneName << ": " << lineNum << ": " << fileOneLine << endl;
    cout << fileTwoName << ": " << lineNum << ": " << fileTwoLine << endl;
    
    // stores number of digits of lineNum
    int lineItLen = int(log10(lineNum)+1);
    // stores number of spaces for label before each line
    int labelSpaceLen = fileOneName.length() + lineItLen + 4;
    
    // creates string of spaces of length before caret is displayed
    string spaceString(labelSpaceLen + lineDiff, ' ');
    // output spaceString and caret denoting the difference
    // does not output endline if end of both files
    if (endOfFiles) {
        cout << spaceString << '^';
    } else {
        cout << spaceString << '^' << endl;
    }
}

int main(int argc, char* argv[]) {
    // Gives user error if there are not exactly 3 arguments
    if (argc != 3) { cout << "ERROR: Needs 3 arguments!" << endl; return 0; }

    // initialize necessary variables
    string fileOneName = argv[1]; // first file
    string fileTwoName = argv[2]; // second file
    string fileOneLine;
    string fileTwoLine;
    int it = 1;                   // line number

    // assign and open text input files
    ifstream fileOneIn(fileOneName);
    ifstream fileTwoIn(fileTwoName);

    // use getline function to get the iterator count's line
    // and call compareLineOut function to output the comparison
    while(getline(fileOneIn, fileOneLine)) {
        if(getline(fileTwoIn, fileTwoLine)) { // line exists on both files
            compareLineOut(fileOneName, fileTwoName, it, 
                fileOneLine, fileTwoLine, fileOneIn.eof() && fileTwoIn.eof());
        }
        else {                                // line iteration exists only in first file
            compareLineOut(fileOneName, fileTwoName, it, 
                fileOneLine, "", fileOneIn.eof() && fileTwoIn.eof());
        }
        ++it;
    }
    // if file 2 has more lines then this will loop
    while(getline(fileTwoIn, fileTwoLine)) {  // line exists only in second file
        compareLineOut(fileOneName, fileTwoName, it, "", 
            fileTwoLine, fileOneIn.eof() && fileTwoIn.eof());
        ++it;
    }
    fileOneIn.close();
    fileTwoIn.close();

    return 0;
}