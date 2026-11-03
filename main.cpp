//Author: Isabella Delibassis
//CS 219 Computer Organization

#include <sstream>
#include <fstream>
#include "opcode.h"

 


int main() {
    string op1, op2, op3;
    string operationCode;
    int count = 0;
    opcode i;
    
    ifstream openFile("input.txt");
    if (!openFile.is_open()) {
        cout << "Could not open the file" << endl; 
    } else {
        string initialLine;
         while (getline(openFile, initialLine)) {
            int opCount = 0;
            stringstream ss(initialLine);
                if (initialLine.empty() == false) {
                    cout << ss.str() << endl;
                    string line = initialLine;
    


    //line = i.removeWhiteSpace(line);
    /*if (line.empty()) {
        
    }*/
    stringstream ss1(line);
    string opcode;
    ss >> opcode;

    string operandsStr;
    getline(ss1, operandsStr);

    vector<string> ss2;
    stringstream opSS(operandsStr);
    string s;
    while (getline(opSS, s, ',')) {
        string updatedS = s;
        //string updatedS = i.removeWhiteSpace(s);
        if (!updatedS.empty()) {
            ss2.push_back(updatedS); //will add each operand into the operand list and determine which operation to use later
        }
    }

    if (opcode == "ADD" || opcode == "SUB" || opcode == "AND" || opcode == "OR" || opcode == "XOR") {
        i.arithmeticAndLogicalOperation(opcode, ss2); //requires three operands
    } else if (opcode == "MOV") {
        i.MOV(ss2); //requires two operands
    } else if (opcode == "CMP") {
        i.CMP(ss2); //requires two operands
    } else if (opcode == "LOAD" || opcode == "STORE") {
        i.dataTransfer(opcode, ss2); //requires two operands
    } else if (opcode == "BEQ" || opcode == "BNE" || opcode == "BAL") {
        i.branch(opcode, ss2); //will only print out something
    } else {
        cout << "Invalid Opcode.\n" << endl;
    }

                }
                
         }

    }




    openFile.close();


    return 0;
}