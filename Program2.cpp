//============================================================================
// Name        : problemSolving.cpp
// Authors     : Neema Badihian & Joseph Darani
// Version     : 1.0
// Description : Tracing input and checking for mistakes
//============================================================================

#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void printStack(stack<string> parseStack) {
    stack<string> tempStack;
    while (parseStack.size() > 0) {
        tempStack.push(parseStack.top());
        parseStack.pop();
    }
    cout << "Stack: " << flush;
    while (tempStack.size() > 0) {
        cout << tempStack.top() << "|||" << flush;
        tempStack.pop();
    }
    cout << endl;
}

string readFromFile(fstream &file, string filePath) {
    string result = "";

    file.open(filePath, ios::in);

    char character;

    while (!file.eof()) {
        file.get(character);
        result += character;
    }
    file.close();
    return result;
}

void buildTable(map < pair<string , string> , string>  &parseTable){
    //each equation fills a cell in the parsing table
    string equations[] = { "program <id> <;> var <dec-list> begin <stat-list> end", "<letter> <alphaNum>", "<letter> <alphaNum>", //0 - 2
        "<digit> <alphaNum>", "lambda", "<dec> : <type> <;>", //3 - 5
        "<id> <moreDec>", ", <dec>", "integer", //6 - 8
        "<stat> <moreStat>", "<stat-list>", "<write>", //9 - 11
        "<assign>", "show <(> <id> <)> <;>", "<id> = <expr> <;>", //12 - 14
        "<term> <exprPrime>", "+ <term> <exprPrime>", "- <term> <exprPrime>", //15 - 17
        "lambda", "<factor> <termPrime>", "* <factor> <termPrime>", //18 - 20
        "/ <factor> <termPrime>", "lambda", "<id>", //21 - 23
        "<number>", "<(> <expr> <)>", "<digit> <moreDigits>", //24 - 26
        "<sign> <digit> <moreDigits>", "<digit> <moreDigits>", "lambda", //27 - 29
        "+", "-", "0", //30 - 32
        "1", "2", "3", //33 - 35
        "4", "5", "6", //36 - 38
        "7", "8", "9", //39 - 41
        "a", "b", "c", //42 - 44
        "d", "e", ";", //45 - 47
        "(", ")" }; //48 - 49

    //all the values of the parsing tables are below
    parseTable[make_pair("<prog>", "program")] = equations[0];
    parseTable[make_pair("<id>", "a")] = equations[1];
    parseTable[make_pair("<id>", "b")] = equations[1];
    parseTable[make_pair("<id>", "c")] = equations[1];
    parseTable[make_pair("<id>", "d")] = equations[1];
    parseTable[make_pair("<id>", "e")] = equations[1];
    parseTable[make_pair("<alphaNum>", ":")] = "lambda";
    parseTable[make_pair("<alphaNum>", ",")] = "lambda";
    parseTable[make_pair("<alphaNum>", "=")] = "lambda";
    parseTable[make_pair("<alphaNum>", "+")] = "lambda";
    parseTable[make_pair("<alphaNum>", "-")] = "lambda";
    parseTable[make_pair("<alphaNum>", "*")] = "lambda";
    parseTable[make_pair("<alphaNum>", "/")] = "lambda";
    parseTable[make_pair("<alphaNum>", "0")] = equations[3];
    parseTable[make_pair("<alphaNum>", "1")] = equations[3];
    parseTable[make_pair("<alphaNum>", "2")] = equations[3];
    parseTable[make_pair("<alphaNum>", "3")] = equations[3];
    parseTable[make_pair("<alphaNum>", "4")] = equations[3];
    parseTable[make_pair("<alphaNum>", "5")] = equations[3];
    parseTable[make_pair("<alphaNum>", "6")] = equations[3];
    parseTable[make_pair("<alphaNum>", "7")] = equations[3];
    parseTable[make_pair("<alphaNum>", "8")] = equations[3];
    parseTable[make_pair("<alphaNum>", "9")] = equations[3];
    parseTable[make_pair("<alphaNum>", "a")] = equations[2];
    parseTable[make_pair("<alphaNum>", "b")] = equations[2];
    parseTable[make_pair("<alphaNum>", "c")] = equations[2];
    parseTable[make_pair("<alphaNum>", "d")] = equations[2];
    parseTable[make_pair("<alphaNum>", "e")] = equations[2];
    parseTable[make_pair("<alphaNum>", ";")] = "lambda";
    parseTable[make_pair("<alphaNum>", ")")] = "lambda";
    parseTable[make_pair("<dec-list>", "a")] = equations[5];
    parseTable[make_pair("<dec-list>", "b")] = equations[5];
    parseTable[make_pair("<dec-list>", "c")] = equations[5];
    parseTable[make_pair("<dec-list>", "d")] = equations[5];
    parseTable[make_pair("<dec-list>", "e")] = equations[5];
    parseTable[make_pair("<dec>", "a")] = equations[6];
    parseTable[make_pair("<dec>", "b")] = equations[6];
    parseTable[make_pair("<dec>", "c")] = equations[6];
    parseTable[make_pair("<dec>", "d")] = equations[6];
    parseTable[make_pair("<dec>", "e")] = equations[6];
    parseTable[make_pair("<moreDec>", ":")] = "lambda";
    parseTable[make_pair("<moreDec>", ",")] = equations[7];
    parseTable[make_pair("<type>", "integer")] = equations[8];
    parseTable[make_pair("<stat-list>", "show")] = equations[9];
    parseTable[make_pair("<stat-list>", "a")] = equations[9];
    parseTable[make_pair("<stat-list>", "b")] = equations[9];
    parseTable[make_pair("<stat-list>", "c")] = equations[9];
    parseTable[make_pair("<stat-list>", "d")] = equations[9];
    parseTable[make_pair("<stat-list>", "e")] = equations[9];
    parseTable[make_pair("<moreStat>", "end")] = "lambda";
    parseTable[make_pair("<moreStat>", "show")] = equations[10];
    parseTable[make_pair("<moreStat>", "a")] = equations[10];
    parseTable[make_pair("<moreStat>", "b")] = equations[10];
    parseTable[make_pair("<moreStat>", "c")] = equations[10];
    parseTable[make_pair("<moreStat>", "d")] = equations[10];
    parseTable[make_pair("<moreStat>", "e")] = equations[10];
    parseTable[make_pair("<stat>", "show")] = equations[11];
    parseTable[make_pair("<stat>", "a")] = equations[12];
    parseTable[make_pair("<stat>", "b")] = equations[12];
    parseTable[make_pair("<stat>", "c")] = equations[12];
    parseTable[make_pair("<stat>", "d")] = equations[12];
    parseTable[make_pair("<stat>", "e")] = equations[12];
    parseTable[make_pair("<write>", "show")] = equations[13];
    parseTable[make_pair("<assign>", "a")] = equations[14];
    parseTable[make_pair("<assign>", "b")] = equations[14];
    parseTable[make_pair("<assign>", "c")] = equations[14];
    parseTable[make_pair("<assign>", "d")] = equations[14];
    parseTable[make_pair("<assign>", "e")] = equations[14];
    parseTable[make_pair("<expr>", "+")] = equations[15];
    parseTable[make_pair("<expr>", "-")] = equations[15];
    parseTable[make_pair("<expr>", "0")] = equations[15];
    parseTable[make_pair("<expr>", "1")] = equations[15];
    parseTable[make_pair("<expr>", "2")] = equations[15];
    parseTable[make_pair("<expr>", "3")] = equations[15];
    parseTable[make_pair("<expr>", "4")] = equations[15];
    parseTable[make_pair("<expr>", "5")] = equations[15];
    parseTable[make_pair("<expr>", "6")] = equations[15];
    parseTable[make_pair("<expr>", "7")] = equations[15];
    parseTable[make_pair("<expr>", "8")] = equations[15];
    parseTable[make_pair("<expr>", "9")] = equations[15];
    parseTable[make_pair("<expr>", "a")] = equations[15];
    parseTable[make_pair("<expr>", "b")] = equations[15];
    parseTable[make_pair("<expr>", "c")] = equations[15];
    parseTable[make_pair("<expr>", "d")] = equations[15];
    parseTable[make_pair("<expr>", "e")] = equations[15];
    parseTable[make_pair("<expr>", "(")] = equations[15];
    parseTable[make_pair("<exprPrime>", "+")] = equations[16];
    parseTable[make_pair("<exprPrime>", "-")] = equations[17];
    parseTable[make_pair("<exprPrime>", ";")] = "lambda";
    parseTable[make_pair("<exprPrime>", ")")] = "lambda";
    parseTable[make_pair("<term>", "+")] = equations[19];
    parseTable[make_pair("<term>", "-")] = equations[19];
    parseTable[make_pair("<term>", "0")] = equations[19];
    parseTable[make_pair("<term>", "1")] = equations[19];
    parseTable[make_pair("<term>", "2")] = equations[19];
    parseTable[make_pair("<term>", "3")] = equations[19];
    parseTable[make_pair("<term>", "4")] = equations[19];
    parseTable[make_pair("<term>", "5")] = equations[19];
    parseTable[make_pair("<term>", "6")] = equations[19];
    parseTable[make_pair("<term>", "7")] = equations[19];
    parseTable[make_pair("<term>", "8")] = equations[19];
    parseTable[make_pair("<term>", "9")] = equations[19];
    parseTable[make_pair("<term>", "a")] = equations[19];
    parseTable[make_pair("<term>", "b")] = equations[19];
    parseTable[make_pair("<term>", "c")] = equations[19];
    parseTable[make_pair("<term>", "d")] = equations[19];
    parseTable[make_pair("<term>", "e")] = equations[19];
    parseTable[make_pair("<term>", "(")] = equations[19];
    parseTable[make_pair("<termPrime>", "+")] = "lambda";
    parseTable[make_pair("<termPrime>", "-")] = "lambda";
    parseTable[make_pair("<termPrime>", "*")] = equations[20];
    parseTable[make_pair("<termPrime>", "/")] = equations[21];
    parseTable[make_pair("<termPrime>", ";")] = "lambda";
    parseTable[make_pair("<termPrime>", ")")] = "lambda";
    parseTable[make_pair("<factor>", "+")] = equations[24];
    parseTable[make_pair("<factor>", "-")] = equations[24];
    parseTable[make_pair("<factor>", "0")] = equations[24];
    parseTable[make_pair("<factor>", "1")] = equations[24];
    parseTable[make_pair("<factor>", "2")] = equations[24];
    parseTable[make_pair("<factor>", "3")] = equations[24];
    parseTable[make_pair("<factor>", "4")] = equations[24];
    parseTable[make_pair("<factor>", "5")] = equations[24];
    parseTable[make_pair("<factor>", "6")] = equations[24];
    parseTable[make_pair("<factor>", "7")] = equations[24];
    parseTable[make_pair("<factor>", "8")] = equations[24];
    parseTable[make_pair("<factor>", "9")] = equations[24];
    parseTable[make_pair("<factor>", "a")] = equations[23];
    parseTable[make_pair("<factor>", "b")] = equations[23];
    parseTable[make_pair("<factor>", "c")] = equations[23];
    parseTable[make_pair("<factor>", "d")] = equations[23];
    parseTable[make_pair("<factor>", "e")] = equations[23];
    parseTable[make_pair("<factor>", "(")] = equations[25];
    parseTable[make_pair("<number>", "+")] = equations[27];
    parseTable[make_pair("<number>", "-")] = equations[27];
    parseTable[make_pair("<number>", "0")] = equations[26];
    parseTable[make_pair("<number>", "1")] = equations[26];
    parseTable[make_pair("<number>", "2")] = equations[26];
    parseTable[make_pair("<number>", "3")] = equations[26];
    parseTable[make_pair("<number>", "4")] = equations[26];
    parseTable[make_pair("<number>", "5")] = equations[26];
    parseTable[make_pair("<number>", "6")] = equations[26];
    parseTable[make_pair("<number>", "7")] = equations[26];
    parseTable[make_pair("<number>", "8")] = equations[26];
    parseTable[make_pair("<number>", "9")] = equations[26];
    parseTable[make_pair("<moreDigits>", "0")] = equations[28];
    parseTable[make_pair("<moreDigits>", "1")] = equations[28];
    parseTable[make_pair("<moreDigits>", "2")] = equations[28];
    parseTable[make_pair("<moreDigits>", "3")] = equations[28];
    parseTable[make_pair("<moreDigits>", "4")] = equations[28];
    parseTable[make_pair("<moreDigits>", "5")] = equations[28];
    parseTable[make_pair("<moreDigits>", "6")] = equations[28];
    parseTable[make_pair("<moreDigits>", "7")] = equations[28];
    parseTable[make_pair("<moreDigits>", "8")] = equations[28];
    parseTable[make_pair("<moreDigits>", "9")] = equations[28];
    parseTable[make_pair("<moreDigits>", "+")] = "lambda";
    parseTable[make_pair("<moreDigits>", "-")] = "lambda";
    parseTable[make_pair("<moreDigits>", "*")] = "lambda";
    parseTable[make_pair("<moreDigits>", "/")] = "lambda";
    parseTable[make_pair("<moreDigits>", ";")] = "lambda";
    parseTable[make_pair("<moreDigits>", ")")] = "lambda";
    parseTable[make_pair("<sign>", "+")] = equations[30];
    parseTable[make_pair("<sign>", "-")] = equations[31];
    parseTable[make_pair("<digit>", "0")] = equations[32];
    parseTable[make_pair("<digit>", "1")] = equations[33];
    parseTable[make_pair("<digit>", "2")] = equations[34];
    parseTable[make_pair("<digit>", "3")] = equations[35];
    parseTable[make_pair("<digit>", "4")] = equations[36];
    parseTable[make_pair("<digit>", "5")] = equations[37];
    parseTable[make_pair("<digit>", "6")] = equations[38];
    parseTable[make_pair("<digit>", "7")] = equations[39];
    parseTable[make_pair("<digit>", "8")] = equations[40];
    parseTable[make_pair("<digit>", "9")] = equations[41];
    parseTable[make_pair("<letter>", "a")] = equations[42];
    parseTable[make_pair("<letter>", "b")] = equations[43];
    parseTable[make_pair("<letter>", "c")] = equations[44];
    parseTable[make_pair("<letter>", "d")] = equations[45];
    parseTable[make_pair("<letter>", "e")] = equations[46];
    parseTable[make_pair("<;>", ";")] = equations[47];
    parseTable[make_pair("<(>", "(")] = equations[48];
    parseTable[make_pair("<)>", ")")] = equations[49];

    return ;
}

string errorMessage(string error){ // handeling the error messages depending on the traced input
    
    if(error == "termPrime" || error == "exprPrime" || error == "moreDigits" || error == "alphaNum" || error == ";") return ";";
    if(error == "term" || error == "factor" || error == "expr") return "Legal Expression";
    if(error == "(") return "(";
    if(error == ")") return ")";
    if(error == "moreStat") return "a statement";
    return error;
}
bool traceErrors(string userInput){
    
    /* Expected words program, var, integer, begin, end */
    string expected[] = {"program", "var", "integer", "begin", "end" };
    for(int i = 0; i < 5 ; i++){
        
            if(userInput.find(expected[i]) == string::npos){
            cout<<expected[i]<<" is expected"<<endl;
            return false;
        }
    }
     
    /* Tokenize */
    int len = userInput.length();
    vector<string> tokens;

    for(int i = 0; i < len; i++){
        
        if(userInput[i]!='\n' && userInput[i]!=' '){ // if the character if not white space
            string token = "";
            while(userInput[i]!='\n' && userInput[i]!=' ' && i < len){
                token += userInput[i]; // create a token
                i++;
            }
                tokens.push_back(token); // add the token to result vector          
        }   
    }
    /* ; before end*/
    int size = tokens.size();
    if(tokens[size-2] != ";"){
        cout<<"; is missing"<<endl;
        return false;
    }
    
    /* Commas */
    bool okComma = false;
    
    for(int i = 0; i < size ; i++){
        if(tokens[i] == "var") { okComma = true; i++; }
        if(tokens[i] == ":") okComma = false;
        if(okComma){ // we are in the range
        
            if(tokens[i] != "," && tokens[i+1] != ":" && tokens[i+1] != ","){
                cout << ", is missing"<<endl;
                cout<< tokens[i]<<endl;
                return false;
            }
        }
    }
    return true;
}
void traceInput(map < pair<string , string> , string>  parseTable){
    //these are the key words and characters that should be read as strings
    //all other words from the user's input should be read as a series of characters
    vector<string> resWords;
    resWords.push_back("program");
    resWords.push_back("var");
    resWords.push_back("integer");
    resWords.push_back("begin");
    resWords.push_back("end");
    resWords.push_back("show");
    resWords.push_back(",");
    resWords.push_back(":");
    resWords.push_back(";");
    resWords.push_back("(");
    resWords.push_back(")");
    resWords.push_back("+");
    resWords.push_back("-");
    resWords.push_back("*");
    resWords.push_back("/");
    resWords.push_back("=");

    vector<string> declaredIDs;

    string userInput; //this will be read from a file
    stack<string> parseStack; //the stack we will pop for tracing
    string poppedStr; //the string popped from parseStack will be placed here
    string userToken = ""; //this will hold each word from the file
    std::string previousToken;
    vector<string> userVect; //this variable allows us to iterate through the
    //characters in a word when the word is a variable
    string missingToken = "";
    string missingID = "";
    string tableStr; //this will hold the value of any given cell, depending on what
    //is popped from the stack and what word we are on in the userInput
    bool breakBool = false; //this will let us know if we need to exit because the input is invalid
    bool beginBool = false;
    bool undeclaredBool = false;
    bool isID = false;




    fstream file;
    string filePath = "/Users/joseph/Desktop/finalp2.txt";
    userInput = readFromFile(file, filePath);
    userInput.pop_back();
    parseStack.push("$");
    parseStack.push("<prog>");
    cout << userInput << endl;
    cout << endl;
    
    if(!traceErrors(userInput)) return; // check for some errors before tracing

    for (int i = 0; i < userInput.length(); i++) { //iterate through the entire userInput
        if (!isspace(userInput[i])) {
            userToken += userInput[i]; //as long as the character we are on is NOT a space character, add it to the token

        }
        else {
            //check if the word is a reserved word
            bool wordExists = find(resWords.begin(), resWords.end(), userToken) != resWords.end();
            if (wordExists) {
                //if it is a reserved word, push the whole thing as a single string into userVect
                userVect.push_back(userToken);
                //if the reserved word is 'begin', set the boolean beginBool to true
                //to let the program know that no more variables can be declared
                if (userToken == "begin"){
                    beginBool = true;
                }

            }
            else {
                //if it is NOT a reserved word, push each character one at a time into userVect
            	//and add the token to the declared IDs
            	if (beginBool == false){
                	declaredIDs.push_back(userToken);
            	}
            	else if(find(declaredIDs.begin(), declaredIDs.end(), userToken) == declaredIDs.end()) {
            		for (int i = 0; i < userToken.length(); i++){
            			if(isalpha(userToken[i])){
            				isID = true;
            			}
            		}
            		if(isID == true){
            			breakBool = true;
            			undeclaredBool = true;
            			missingID = userToken;
            		}

            	}
                for (int k = 0; k < userToken.length(); k++) {
                    userVect.push_back(string(1, userToken[k]));
                }
            }

            //iterate through the values of userVect
            for (vector<string>::iterator it = userVect.begin(); it != userVect.end(); it++) {
                userToken = *it; //set userToken to equal the current value of userVect we are on

                //pop the top of the stack and place it in poppedStr
                poppedStr = parseStack.top();
                parseStack.pop();

                while (poppedStr != userToken) { //do the following while poppedStr does not equal userToken i.e we don't have a match
                    if (parseTable.find(make_pair(poppedStr, userToken)) == parseTable.end()) {
                        //if the parsing table does not exist at [poppedStr, userToken], exit the program
                        if (missingToken == ";"){
                        	continue;
                        }
                        else if (poppedStr[0] == '<'){
                            for (int i = 1; i < poppedStr.length() - 1; i++) {
                                missingToken += poppedStr[i];
                            }
                        }
                        else {
                            missingToken = poppedStr;
                        }

                        breakBool = true;
                        break;
                    }
                    else {
                        //get the value of the table at [poppedStr, userToken] and place it in tableStr
                        tableStr = parseTable[make_pair(poppedStr, userToken)];
                        if (tableStr != "lambda") { //if tableStr does NOT equal lambda, do the following
                            string word = "";
                            stack<string> stackInput;

                            //this for loop separate all values in tableStr by spaces and pushes each one into stackInput
                            //when it's done pushing values, stackInput's values are pushed into parseStack
                            //this ensures that all values are pushed into our main stack in reverse order
                            for (int j = 0; j <= tableStr.length(); j++) {
                                if (j != tableStr.length() && !isspace(tableStr[j]) ) {
                                    word += tableStr[j];
                                }
                                else {
                                    if (word.length() > 0) {
                                        stackInput.push(word);
                                    }
                                    word = "";
                                }
                            }
                            stackInput.push(word);
                            while (stackInput.size() > 0) {
                                if (stackInput.top().length() > 0) {
                                    parseStack.push(stackInput.top());
                                }
                                stackInput.pop();
                            }
                        }
                        poppedStr = parseStack.top();
                        parseStack.pop();
                    }
                }
                if (breakBool == true) {
                    break;
                }
                
                previousToken = userToken;
                userToken = "";
            }
            userVect.clear();
        }
        if (breakBool == true) {
        	if (undeclaredBool == false){
        		cout << "You are missing " << errorMessage(missingToken) << endl;
        	}
        	else if (undeclaredBool == true){
        		cout << "You have an undeclared variable: " << missingID << endl;
        	}
            cout << "Your code has been rejected." << endl;
            break;
        }
    }
    if (breakBool == false) {
        cout << "Your code has been accepted." << endl;
    }
    return;
}
int main() {

    map<pair<string, string>, string>parseTable;
    buildTable(parseTable);
    traceInput(parseTable);
    cout << "Goodbye." << endl;
    return 0;
}
