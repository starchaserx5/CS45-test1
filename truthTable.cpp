#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>

using namespace std;

bool getInput(string &what);

void stringCutter(string &command, string &restOfString, string &what);

bool stringCompare(vector <string> predetermindedVector, string &command, int &pos);

void addToMultiVector(string &restOfString, vector<vector<string> > &regAndRpn, string rpn);

void capitalize(string &restOfString);

void removeSpaces(string &restOfString);

void printMultiDimensionalVector(vector <vector <string>> &regAndRpn);

bool deleteExpression(vector <vector <string>> &regAndRpn, string &restOfString);

bool edit(vector <vector <string>> &regAndRpn, string &restOfString);

int whoIsFirst(const string &incoming);

bool illegalSet(string restOfString);

bool precedence(const string &incoming, const string &tos);

bool convertToRPN(string restOfString, string &output);

void process(string rpn, int sets[]);

unsigned int unionOfTwoSets(string x, string y, string &result);

unsigned int intersectionOfTwoSets(string x, string y, string &result);

unsigned int differenceOfTwoSets(string x, string y, string &result);

unsigned int setCompliment(string x, string &result);

bool store(vector <vector <string>> &regAndRpn, string &restOfString);

bool question(string title);

void checkFileName(string restOfString);

int main()
{
    string command, restOfString, what, output, rpn, filename;
    string blank("");
    bool pleaseWork = true;
    int pos, tempPos;
    int sets[26];
    vector <vector <string>> regAndRpn;
    vector <string> predetermindedVector = {"NEW", "DELETE", "TABLE", "LIST", "STORE",
                                           "LOAD", "EDIT", "EXIT", "QUIT", "WEXIT",
                                           "WQUIT", "HELP", "IS"};

    while(getInput(what))
    {
        stringCutter(command, restOfString, what);
        capitalize(command);
        removeSpaces(command);
        removeSpaces(restOfString);

        if(stringCompare(predetermindedVector, command, pos))
        {
            removeSpaces(restOfString);

            if(pos == 1) //NEW
            {
                capitalize(restOfString);

                if(convertToRPN(restOfString, output))
                {
                    process(output, sets);
                    addToMultiVector(restOfString, regAndRpn, output);
                }
                else
                {
                    cout << "Illegal expression!" << endl;
                }
            }
            else if(pos == 2) //DELETE
            {
                deleteExpression(regAndRpn, restOfString);
            }
            else if(pos == 3) //TABLE
            {

            }
            else if(pos == 4) //LIST
            {
                printMultiDimensionalVector(regAndRpn);
            }
            else if(pos == 5) //STORE
            {
                store(regAndRpn, restOfString);
            }
            else if(pos == 6) //LOAD
            {

            }
            else if(pos == 7) //EDIT
            {
                edit(regAndRpn, restOfString);
            }
            else if(pos == 8 || pos == 9) //EXIT //QUIT
            {
                bool itsBeenStored = store(regAndRpn, blank);
                //wanna get "true" for store function

                //if(true equals true)
                if(pleaseWork == itsBeenStored)
                {
                    exit(1);
                }
                else
                {
                    cout << "Store before exiting" << endl;
                }


                /*(store(regAndRpn, blank))
                {
                    cout << "It's been stored";
                }*/


               /* bool itsBeenStored = store(regAndRpn, blank);

                cout << itsBeenStored << "HELLO" << endl;

                do
                {
                    itsBeenStored = store(regAndRpn, blank);
                    cout << itsBeenStored << endl;
                    cout << "Please save all expressions before exiting." << endl;

                }while(itsBeenStored);*/
            }
            else if(pos == 10) //WEXIT
            {

            }
            else if(pos == 11) //WQUIT
            {

            }
            else if(pos == 12) //HELP
            {

            }
            else if(pos == 13) //IS
            {

            }
        }
    }

    return 0;
}

bool getInput(string &what)
{
    stringstream ss("");

    cout << "INPUT: ";
    getline(cin, what);

    return !what.empty();
}

void stringCutter(string &command, string &restOfString, string &what)
{
    if(what.find(' ') != string::npos)
    {
        unsigned int position;
        position = what.find(' ');
        command = what.substr(0,position);
        restOfString = what.substr(position);
    }
    else
    {
        command = what;
    }
}

bool stringCompare(vector <string> predetermindedVector, string &command, int &pos)
{
    for(unsigned int i = 0; i < predetermindedVector.size(); ++i)
    {
        if(predetermindedVector[i] == command)
        {
            pos = i+1;      //position of where command was found in vector predeterminedVector
            return true;
        }
    }
    return false;
}

void addToMultiVector(string &restOfString, vector <vector <string>> &regAndRpn, string rpn)
{
    unsigned int size = regAndRpn.size();

    for(int i = 0; i < 1; i++)
    {
        vector<string>temp;
        for(int j = 0; j < 1; ++j)
        {
            temp.push_back(restOfString);
            temp.push_back(rpn);
        }
        regAndRpn.push_back(temp);
    }

    cout << "EXPRESSION " << size+1 << ": " << regAndRpn[size][0] << endl;
}

void capitalize(string &restOfString)
{
    for(unsigned int i = 0; i < restOfString.length(); ++i)
    {
        restOfString[i] = toupper(restOfString[i]);
    }
}

void removeSpaces(string &restOfString)
{
    for(unsigned int i = 0; i < restOfString.length(); ++i)
    {
        if(restOfString[i] == ' ')
        {
            restOfString.erase(i,1);
        }
    }
}

void printMultiDimensionalVector(vector <vector <string>> &regAndRpn)
{
    for(unsigned int i = 0; i < regAndRpn.size(); ++i)
    {
        for(unsigned int j = 0; j < regAndRpn[i].size()-1; ++j)
        {
            cout << "EXPRESSION " << i+1 << ": " << regAndRpn[i][j];
            //cout << "regAndRpn[" << i << "][" << j << "] = " << regAndRpn[i][j] << "    ";
        }
        cout << endl;
    }
}

bool deleteExpression(vector <vector <string>> &regAndRpn, string &restOfString)
{
    int temp;

    if(restOfString.size() > 1)
    {
        cout << "Invalid input. Try again.111" << endl;
        return false;
    }

    temp = stoi(restOfString);
    if(temp < 0)
    {
        cout << "Invalid input. Cannot be negative." << endl;
        return false;
    }
    else if(temp > regAndRpn.size())
    {
        cout << "Invalid input. Expression doesn't exist." << endl;
        return false;
    }

    regAndRpn[temp-1][0].erase();
    cout << regAndRpn[0].size() << endl;
    return true;
}

bool edit(vector <vector <string>> &regAndRpn, string &restOfString)
{
    int temp;
    string what;

    if(restOfString.size() > 1)
    {
        cout << "Invalid input. Try again." << endl;
        return false;
    }

    temp = stoi(restOfString);
    if(temp > regAndRpn.size())
    {
        cout << "Invalid input. Expression doesn't exist." << endl;
        return false;
    }
    else if(temp <= 0)
    {
        cout << "Invalid input. Cannot be negative." << endl;
        return false;
    }

    getInput(what);
    removeSpaces(what);
    regAndRpn[temp-1][0].erase();
    regAndRpn[temp-1][0].insert(0, what);

    return true;
}

int whoIsFirst(const string &incoming) //Convert operator to its precedence value
{
    int value = 0;
    switch(incoming[0])
    {
        case '!' : value = 3;          //Compliment is the highest
                   break;
        case '*' : value = 2;
                   break;
        case '+' :
        case '\\' : value = 1;          //Union and set difference are the lowest
    }
    return value;
}

bool illegalSet(string restOfString)          //See if the user entered a double comma or something
{                                      //like {, or ;}
    unsigned int pos, size = restOfString.size();
    while((pos = restOfString.find(' ')) < size) //Find spaces
        restOfString.erase(pos,1);
    return (restOfString.find(",,") < size ||
            restOfString.find("{,")  < size ||
            restOfString.find(",}") < size ||
            restOfString.find_first_not_of("0123456789{,}") < size);
}

bool precedence(const string &incoming, const string &tos) //Return TRUE is incoming operator
{
     return whoIsFirst(incoming) < whoIsFirst(tos);  //is less than what is on the top of the operator stack
}

bool convertToRPN(string restOfString, string &output)
{
      vector<string>operatorStack;                //Holds operators
      string  op, operand, parens;                          //Holds the current operator and operand
      output = "";                                  //Initialize output to empty
      unsigned int pos, pos2;                       //Used to find position of substrings within a string

      while(restOfString.size() > 0)                       //As long as there is still input
      {
          if(restOfString[0]>='A' && restOfString[0] <= 'Z')      //Did we read the name of a set?
          {                                         //If so, move it directly to the output
              operand = restOfString[0];
              output += operand + " ";
              restOfString.erase(0,1);                     //Remove the operand from the input
          }
          else                                      //Otherwise
          {
            switch(restOfString[0])                        //See what the operator "could" be
            {
                case ' ' : restOfString.erase(0,1);        //Dump any space that has been read from the input
                           break;
                case '{' : pos = restOfString.find('}');   //If it is a open curly brace, we have an unnamed set
                           pos2 = restOfString.find('{', pos + 1);  //So see if it is a valid unnamed set
                           if(pos > restOfString.size() || pos2 < pos)
                               return false;        //If not, signify that an invalid unnamed set was read in
                           parens = (restOfString.substr(0,pos + 1)) + " "; //It is is valid, pull it out of the input
                           if(illegalSet(parens))   //Did they enter a double comma?
                               return false;
                           output += parens;        //Bad input!!
                           restOfString.erase(0,pos + 1);  //and remove it from the input
                           break;

                case '*' :                          //If it is any valid operator
                case '\\' :                         //we either immediately push it onto the operand stack
                case '+' :                          //or push higher precedence operators currently in the stack
                case '!' : op = restOfString[0];           //onto the output
                           while((operatorStack.size() > 0) && precedence(op, operatorStack[operatorStack.size()-1]))
                           {
                                output += operatorStack.back() + " ";
                                operatorStack.pop_back();
                           }
                           operatorStack.push_back(op); //Insert current operator onto operator stack
                           restOfString.erase(0,1);            //Remove the current operator from input
                           break;
                case '(' : operatorStack.push_back("("); //Parenthesis are a "special case"
                           restOfString.erase(0,1);             //Push the opening onto the operand stack and wait till
                           break;                        //a closing parentheses is found
                case ')' : while(operatorStack.size() > 0 && operatorStack.back() != "(")
                           {                             //Once found, keep pushing operators onto output
                              output += operatorStack.back() + " ";
                              operatorStack.pop_back();  //Until we either empty the stack or find a opening paren
                           }
                           if(operatorStack.size() == 0)
                               return false;
                           else
                               operatorStack.pop_back();
                           restOfString.erase(0,1);
                           break;
                default  : return false;
            }
          }
        }
        while(operatorStack.size() > 0)  //If there are any additional operators left on the stack
        {                                //we push them onto output unless we find a mis-matched paren
            string op = operatorStack.back();
            if(op[0] == '(')
                return false;
            output += op + " ";
            operatorStack.pop_back();
        }
        return true;                      //Signify a successful conversion to RPN
}

void process(string rpn, int sets[])    //Process the RPN on sets
{
    unsigned int result = 0, pos;       //Initialize result to 0 (or create a bitset to be your result holder)
    vector<string> operandStack;        //Create an operand and operator stack
    vector<char> operatorStack;
    string set, x, y, output;           //Create some temporary variables

    //cout<<"Translated to RPN: " << rpn << endl;

    while(rpn.size() > 0)               //As long as there are inputs available
    {
        if(rpn[0] >= 'A' && rpn[0] <= 'Z') //If a named set, push onto the operand stack
        {
            operandStack.push_back(output = rpn[0]);
            rpn.erase(0,1);
        }
        else                                //Otherwise
        {
            switch(rpn[0])                  //See what the operator is
            {
                case ' ' :  rpn.erase(0,1); //Get rid of spaces
                            break;
                case '{' :  pos = rpn.find('}');//If curly braces, get the unnamed set
                            set = (rpn.substr(0, pos + 1));
                            operandStack.push_back(set); //and push it onto the operand stack
                            rpn.erase(0, pos+1);         //Then remove it from the RPN input
                            break;
                case '!' :  x = operandStack.back();     //If compliment operator
                            operandStack.pop_back();     //Pop an operand and
                            result = setCompliment(x, output); //compliment it
                            operandStack.push_back(output); //Push the result back onto the operand stack
                            rpn.erase(0,1);
                            break;
                case '+' :  x = operandStack.back();    //If it is Union, two operands are required
                            operandStack.pop_back();    //Pop them, then perform the union
                            y = operandStack.back();
                            operandStack.pop_back();
                            result = unionOfTwoSets(x, y, output);
                            operandStack.push_back(output); //Then place the result onto the operand stack
                            rpn.erase(0,1);                 //Delete from input the operand
                            break;
                case '*' :  x = operandStack.back();        //If it is Intersection, two operands are required
                            operandStack.pop_back();        //Pop them, then perform the intersection
                            y = operandStack.back();
                            operandStack.pop_back();
                            result = intersectionOfTwoSets(x, y, output);//The place the result onto the operand stack
                            operandStack.push_back(output); //Then place the result onto the operand stack
                            rpn.erase(0,1);                 //Delete from input the operand
                            break;
               case '\\' :  x = operandStack.back();        //If it is Set Difference, two operands are required
                            operandStack.pop_back();        //Pop them, then perform the set difference
                            y = operandStack.back();
                            operandStack.pop_back();
                            result = differenceOfTwoSets(y, x, output);//The place the result onto the operand stack
                            operandStack.push_back(output); //Delete from input the operand
                            rpn.erase(0,1);
                            break;
            }
        }
    }
}

unsigned int unionOfTwoSets(string x, string y, string &result)
{

}

unsigned int intersectionOfTwoSets(string x, string y, string &result)
{

}

unsigned int differenceOfTwoSets(string x, string y, string &result)
{

}

unsigned int setCompliment(string x, string &result)
{

}

bool store(vector <vector <string>> &regAndRpn, string &restOfString)
{
    bool stored = false;
    ofstream outStream;
    string newFileName;
    string filename;

    checkFileName(restOfString);
    outStream.open(restOfString, ios_base::out | ios_base::in);

    if(outStream.is_open())
    {
        cout << "File already exists." << endl;

        if(question("Would you like to rename file?"))
        {
            cout << "Enter new file name: " << endl;
            getline(cin, newFileName);
            removeSpaces(newFileName);

            checkFileName(newFileName);
            rename(restOfString.c_str(), newFileName.c_str());
        }
        else if(question("Would you like to erase the current file?"))
        {
            remove(restOfString.c_str());
            cout << "File successfully erased." << endl;
        }
        stored = false;
    }
    else
    {
        outStream.clear();
        outStream.open(restOfString);

        ostream_iterator <string> output_iterator(outStream, "      ");
        for(unsigned int i = 0; i < regAndRpn.size(); ++i)
        {
            copy(regAndRpn.at(i).begin(), regAndRpn.at(i).end(), output_iterator);
            outStream << endl;
        }
        outStream.close();
        //store = false;
    }
    cout << "store function: " << stored << endl;

    return stored;
}

bool question(string title)
{
    string line;

    cout << title;
    getline(cin, line);

    return toupper(line[0] == 'Y');
}

void checkFileName(string restOfString)
{
    int found;

    /*if(restOfString.empty())
    {
        cout << "Empty file name. Enter valid file name." << endl;
    }*/

    found = restOfString.find(".txt");

    if(found == string::npos)
    {
        restOfString = restOfString + ".txt";
    }
}
