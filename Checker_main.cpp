#include "genStack.h"
#include <fstream>

int stackSize = 100;

int main(int argc, char **argv)
{
  bool cont = true;
  bool failedTest = false;

  string fileName;
  string line;
  char toCheck;

  while (cont)
  {
    genStack<char> *stack = new genStack<char>(stackSize);
    int lineNum = 0;
    ifstream inFS;
    cout << "Welcome to Syntax Checker! What is the name or path of the file you want analyzed?" << endl;
    cin >> fileName;

    inFS.open(fileName);
    if (!inFS.is_open())
    {
      cout << "Could not open file." << endl;
      cout << "please enter a correct file name and try again." << endl;
    }

    while (!inFS.eof() && !failedTest)
    {
      inFS >> line;
      lineNum++;
      if(!inFS.fail() && !failedTest)
      {
        for (int i = 0; i < line.length(); ++i)
        {
          if (line[i] == '(' || line[i] == '[' || line[i] =='{')
          {
            stack -> push(line[i]);
          }

          if (line[i] == ')')
          {
            char toCheck = stack -> pop();
            if (toCheck != '(')
            {
              cout << "Error at line " << lineNum << "! Expected ( !" << endl;
              failedTest = true;
              break;
            }
          }

          if (line[i] == ']')
          {
            char toCheck = stack -> pop();
            if (toCheck != '[')
            {
              cout << "Error at line " << lineNum << "! Expected [ !" << endl;
              failedTest = true;
              break;
            }
          }

          if (line[i] == '}')
          {
            char toCheck = stack -> pop();
            if (toCheck != '{')
            {
              cout << "Error at line " << lineNum << "! Expected { !" << endl;
              failedTest = true;
              break;
            }
          }
        }
      }
    }
    if (stack -> isEmpty() == false)
    {
      cout << "Error at line " << lineNum << "! Unclosed (, [, or { !" << endl;
    }
    cout << "File done! Would you like to test another file? (true = 1/false = 0)" << endl;
    cin >> cont;
  }
  cout << "Thank you for using the Syntax Checker! Exiting..." << endl;
}
