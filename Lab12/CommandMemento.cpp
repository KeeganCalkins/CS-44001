// Keegan Calkins

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;

// receiver
class Document {
public:

   Document(const vector <string> & lines={}): lines_(lines){}

   // actions
   void insert(int line, const string &str) {
      const int index = line-1;
      if (index <= lines_.size()) {
	      lines_.insert(lines_.begin()+index, str); 
         successful_ = true;
      }
      else
	      cout << "line out of range" << endl; 
   }

   const string remove(int line) {
      const int index = line-1;
      string deletedLine="";
      if(index < lines_.size()) {
	      deletedLine = *(lines_.begin()+index); 
	      lines_.erase(lines_.begin() + index);
         successful_ = true;
      } else
	      cout << "line out of range" << endl;
   
      return deletedLine;
   } 

   void show() const {
      for(int i = 0; i < lines_.size(); ++i)
	      cout << i + 1 << ". " << *(lines_.begin()+i) << endl; 
   }

   bool isSuccessful() {
      return successful_;
   }
   void resetFlag() {
      successful_ = false;
   }

   class Memento *checkpoint() const;  
   void rollback(const class Memento *); 
private:
   vector<string> lines_; 
   bool successful_ = false;
}; 

class Memento {
public:
   Memento(const Document& doc): doc_(doc) {}
   const Document& getState() const {return doc_;}  
private:
   const Document doc_;
};
 
Memento *Document::checkpoint() const {
   return new Memento(*this); // copying the Document itself
}

void Document::rollback(const Memento *mem){
   *this = mem->getState();  // copying back
}

// abstract command
class Command{
public:
   Command(Document *doc) : doc_(doc){}
   virtual void execute() = 0; 
   virtual void unexecute() = 0; 
   virtual ~Command(){}
   virtual void history() = 0;

   virtual Command* clone() = 0;
protected:
   Document *doc_; 
}; 

// two concrete commands
class InsertCommand : public Command {
public:
   InsertCommand(Document *doc, int line, const string &str): 
                 Command(doc), line_(line),  str_(str) {}
   void execute() override { doc_->insert(line_, str_);}
   void unexecute() override {doc_->remove(line_);}
   void history() override { std::cout << "insert " << str_ << " at line " << line_ << std::endl; }

   Command* clone() override {
      return new InsertCommand(doc_, line_, str_);
   }
private:
   int line_; 
   string str_; 
}; 


class EraseCommand : public Command {
public:
   EraseCommand(Document *doc, int line): 
                Command(doc), line_(line), str_("") {}
   void execute() override {str_ = doc_->remove(line_);}
   void unexecute() override {doc_->insert(line_, str_);}
   void history() override { std::cout << "erase " << " at line " << line_ << std::endl; }

   Command* clone() override {
      return new EraseCommand(doc_, line_);
   }
private:
   int line_;
   string str_;
};

// client ?
class DocumentWithHistory{
public:
   DocumentWithHistory(const vector<string> & doc={}) : doc_(doc){}

   void insert(int line, const string & str) {
      Command *com = new InsertCommand(&doc_, line, str); 
      com->execute(); 
      if (doc_.isSuccessful()) {
         doneCommands_.push(com);
         doc_.resetFlag();
      }
   }

   void erase(int line){
      Command *com = new EraseCommand(&doc_, line);
      com->execute();
      if (doc_.isSuccessful()) {
         doneCommands_.push(com);
         doc_.resetFlag();
      }
   }

   void undo() {
      if(!doneCommands_.empty()) {
         // if undo is on insert, then remove
         // if undo is on remove, then insert
	      Command *com = doneCommands_.top(); 
	      doneCommands_.pop();
	      com->unexecute();
	      delete com; // don't forget to delete command
      } else
	      cout << "no commands to undo" << endl;
   }

   void commandHistory() {
      int i = 1;
      std::stack<Command*> tempCommands = doneCommands_, reverseTemp;

      // need to print stack of commands in reverse as otherwise
      // it will display them in an incorrect order
      while(!tempCommands.empty()) { 
         reverseTemp.push(tempCommands.top()); 
         tempCommands.pop();
      }
      while (!reverseTemp.empty()) {
         Command* tempCommand = reverseTemp.top();
         reverseTemp.pop();
         cout << i << ". ";
         tempCommand->history();
         ++i;
      }
   }

   void redo(int historyNum) {
      int numOfCommands = doneCommands_.size();
      if (historyNum > numOfCommands) {
         cout << "Command does not exist\n";
         return;
      }

      // pop commands from copied stack until the desired command is reached
      std::stack<Command*> tempCommands = doneCommands_;
      for (int i = historyNum; i != numOfCommands; ++i) {
         tempCommands.pop();
      }
      Command* requestedCommand = tempCommands.top()->clone();

      requestedCommand->execute();
      doneCommands_.push(requestedCommand);
   }

   void show() const {doc_.show();}

   Document& getDocument() { return doc_; }

   void resetHistory() { 
      while (!doneCommands_.empty()) {
         doneCommands_.pop(); 
      }
   }

private:
   Document doc_;
   std::stack<Command*> doneCommands_; 
}; 

// invoker
int main() {
   Memento* checkpoint = nullptr;
   Document tempDocument;

   DocumentWithHistory his({
	 "Lorem Ipsum is simply dummy text of the printing and typesetting",
	 "industry. Lorem Ipsum has been the industry's standard dummy text",
	 "ever since the 1500s, when an unknown printer took a galley of",
	 "type and scrambled it to make a type specimen book. It has",
	 "survived five centuries."}); 

   tempDocument = his.getDocument();
   checkpoint = tempDocument.checkpoint();

   char option;
   int redoCommand;

   do{
      cout << "Enter option (i)nsert line (e)rase line (u)undo last command (c)heckpoint roll(b)ack (h)history (r)edo command:\n";
      his.show(); 
      cin >> option;

      
      int line; string str;
      switch(option) {
         case 'i':
            cout << "line number to insert: ";
            // ensures input is an integer
            while (!(cin >> line)) { 
               cout << "Enter valid line number: "; 
               cin.clear();
               cin.ignore(50, '\n');
            }
            cout << "line to insert: "; 
            cin.get(); // removes end-of-line character so getline() works correctly
            getline(cin, str); 
            his.insert(line, str); 
            break;
   
         case 'e':
            cout << "line number to remove: ";
            // ensures input is an integer
            while (!(cin >> line)) { 
               cout << "Enter valid line number: "; 
               cin.clear();
               cin.ignore(50, '\n');
            }
            his.erase(line);
            break;

         case 'u':
            his.undo(); 
            break; 

         case 'c':
            tempDocument = his.getDocument();
            checkpoint = tempDocument.checkpoint();
            his.resetHistory();
            break;

         case 'b':
            // set document to the caretaker's state most
            // recently saved through memento
            if (checkpoint != nullptr) {
               his.getDocument().rollback(checkpoint);
            }
            break;
         case 'h':
            his.commandHistory();
            break;

         case 'r':
            his.commandHistory();
            std::cout << "Redo which command number: ";
            // ensures input is an integer
            while (!(cin >> redoCommand)) { 
               cout << "Enter valid line number: "; 
               cin.clear();
               cin.ignore(50, '\n');
            }
            his.redo(redoCommand);
            break;
      }
      cout << "\n";
   } while(option == 'i' || option == 'e' || option == 'u' || option == 'r' || option == 'c' || option == 'h' || option == 'b');
}