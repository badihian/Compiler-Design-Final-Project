//============================================================================
// Name        : problemSolving.cpp
// Authors     : Neema Badihian & Joseph Darani
// Version     : 1.0
// Description : Converting to a High-level Language (C++ & Python)
//============================================================================

#include<iostream>
#include <fstream>
#include<string.h>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;

/* Reading the code from file */
string readFromFile(fstream &file, string filePath){
    
    string result = ""; // Where we will store the whole text
    
    file.open(filePath, ios::in); // open file for reading
    
    char character;
    
    while(!file.eof()){
        
        file.get(character);
        result += character; // add readed charachters to the result string
    }
    file.close();
    return result;  // return the resul string
}

/* Tokenizing different strings*/
vector<string> tokenize(string file){
    
    int len = file.length();
    vector<string> result;
    
    for(int i = 0; i < len; i++){
        
        if(file[i]!='\n' && file[i]!=' '){ // if the character if not white space
            string token = "";
            while(file[i]!='\n' && file[i]!=' ' && i < len){
                token += file[i]; // create a token
                i++;
            }
            result.push_back(token); // add the token to result vector
        }
    }
    return result; // return result vector
}

void ConvertToCPlusPlus(fstream &file, string filePath, vector<string> tokens){
    
    bool foundVar = false; // to mark when we find the word "var"
    
    file.open(filePath, ios::out);
    
    /* add the following code to the c++ file:
     #include<iostream>
     using namespace std; */
    file << "#include<iostream>\nusing namespace std;\n";
    
    for(int i = 0; i <  tokens.size(); i++){ //iterate throught the tokens
        
        if(foundVar){ // We only start adding code after finding "var"
            
            if(tokens[i] == "integer"){
                file << "int"; // replace "integer" with "int"
            }
            else if(tokens[i] == "begin"){
                file << "int main()\n{\n"; // replace "begin" with "int main() {"
            }
            else if(tokens[i] == "show"){
                file << "cout<< "; // replace "show()" with "cout<<"
                file << tokens[i+2]; // skip '('
                i += 3; // skip the ')'
            }
            else if(tokens[i] == "end"){
                file << "}"; // replace "end" with "}"
            }
            else if(tokens[i] == ";"){
                file<< ';' << '\n'; // add a new line after every ';'
            }
            else{ // if the token is not one of the above, add it as it is;
                file << tokens[i];
            }
            file<<' '; // add spaces between tokens
        }
        if(tokens[i] == "var")foundVar = true;
    }
    file.close(); // close file
    return ;
}

void ConvertToPython(fstream &file, string filePath, vector<string> tokens){
    
    bool foundBegin = false; // to mark when we find the word "begin"
    
    file.open(filePath, ios::out);
    
    for(int i = 0; i <  tokens.size(); i++){ //iterate through the tokens
        
        if(foundBegin){ // We only start adding code after finding "begin"
            // because we don't declare variables in python
            
            
            if(tokens[i] == "show"){
                file << "print"; // replace "show" with "print"
            }
            else if(tokens[i] == "end"){
                file << "\nmain()"; // remove "end" and run the program
            }
            else if(tokens[i] == ";"){
                file << '\n' << '\t'; // add a new line and indent after instead of ';'
            }
            else{ // if the token is not one of the above, add it as it is
                file << tokens[i] << ' '; //add spaces between tokens
            }
        }
        if(tokens[i] == "begin"){ // create a function called "main()" that will hold
            // the whole program
            foundBegin = true;
            file << "def main():\n\t";
        }
    }
    file.close(); // close file
    return ;
}

int main() {
    
    fstream file2, fileCpp, filePy;
    string file2Path = "/Users/joseph/Desktop/finalp2.txt"; // for the second file
    string fileCppPath = "/Users/joseph/Desktop/finalp3.cpp"; // for the C++ file
    string filePyPath = "/Users/joseph/Desktop/textPy.py"; // for the Python file
    string cPlusPlusOrPython;
    
    string formattedCode = readFromFile(file2, file2Path); // storing the code in a string
    formattedCode.pop_back(); // remove the last letter because it is EOF
    
    vector<string> tokens = tokenize(formattedCode); // tokenizing the code
    
    while(true) {
        cout << "\nWould you like to translate to C++ or Python (c/p)? " << endl;
        cin >> cPlusPlusOrPython;
        if(tolower(cPlusPlusOrPython[0]) == 'c') {
            ConvertToCPlusPlus(fileCpp, fileCppPath, tokens);
            break;
        }
        else if(tolower(cPlusPlusOrPython[0]) == 'p'){
            ConvertToPython(filePy, filePyPath, tokens);
            break;
        }
        else{
            cout << "You entered an invalid choice." << endl;
        }
    }
    return 0;
}


