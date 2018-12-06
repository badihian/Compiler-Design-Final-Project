    //============================================================================
    // Name        : problemSolving.cpp
    // Authors     : Neema Badihian & Joseph Darani
    // Version     : 1.0
    // Description : Formatting and Removing White Space
    //============================================================================
    
    #include<iostream>
    #include <fstream>
    #include<string.h>
    #include<algorithm>
    #include<vector>
    #include<iomanip>
    #include<cmath>
    #include<set>
    #include<map>
    #include<stack>
    #include<queue>
    #include<bitset>
    #include <numeric>

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

/* Removing comments */ 
string removeComments(string file){
    
    int n = file.length(); 
    string result = "";
    
    for(int i = 0; i < n-1; i++){
        
        if(file[i] == '/' && file[i+1] == '/'){ // a one-line comment started
            while(file[i] != '\n') i++; // skip everything in the line        
            result += '\n'; // add a new line       
        }
        else if(file[i] == '/' && file[i+1] == '*'){// a multi-line comment is started
            
            while(1){i += 1;   
            if(file[i] == '*' && file[i+1] == '/')break; // the end of the comment
            } // skip everything in the line
            
            i++; // to skip the last "/"
            result += '\n'; // add a new line
        }
        else result += file[i]; // add character to the result string     
    }
    return result; // return the result string
}

/* Read the code from file */ 
string removeWhiteSpace(string file){ // to remove extra spaces and lines
    
    int len = file.length();
    string result = "";
    
    for(int i = 0; i < len; i++){
        
        if(file[i] == ' '){ // if we find a space
            result += ' '; // add the first space only
            while(file[i]==' ') i++; // skip the spaces after the first
        }
        if(file[i] == '\n'){// if we find a line
            result += '\n'; // add the first line only
            while(file[i]=='\n' || file[i] == ' ') i++; // skip the lines after the first           
        }
        
        if(i<len) result += file[i]; // add the rest of the code           
    }
    return result; 
}

 /* Writing the formatted code on the second file */ 
void writeToSecondFile(fstream &file, string filePath, string formattedCode){
    
    file.open(filePath, ios::out); // open file for writing
    
    int len = formattedCode.length();
    
    for(int i = 0; i < len; i++){
        file.put(formattedCode[i]);// write each character on the second file
    }
    file.close();
    return; 
}
    
    int main() {
  
        fstream file;
        string filePath = "/Users/joseph/Desktop/finalp1.txt"; // for the first file
        string file2Path = "/Users/joseph/Desktop/finalp2.txt";// for the second file

         string formattedCode = readFromFile(file, filePath);
         cout<<formattedCode<<endl;
         cout<<"-------------------------------"<<endl;
         formattedCode = removeComments(formattedCode);
         cout<< formattedCode<<endl;
         cout<<"-------------------------------"<<endl;
         formattedCode = removeWhiteSpace(formattedCode);
         cout<< formattedCode<<endl;
         cout<<"-------------------------------"<<endl;

         writeToSecondFile(file, file2Path, formattedCode);
        
       return 0;
    }

