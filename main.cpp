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
        string rawLine;
         while (getline(openFile, rawLine)) {
            int opCount = 0;
            stringstream ss(rawLine);
                if (rawLine.empty() == false) {
                    cout << ss.str() << endl;
                    string line = rawLine;
    size_t comment_pos = line.find(';');
    if (comment_pos != string::npos) {
        line = line.substr(0, comment_pos);
    }

    line = i.removeWhiteSpace(line);
    if (line.empty()) {
        
    }
    stringstream ss(line);
    string opcode;
    ss >> opcode;

    string operandsStr;
    getline(ss, operandsStr);

    vector<string> ss1;
    stringstream opSS(operandsStr);
    string s;
    while (getline(opSS, s, ',')) {
        string updatedS = i.removeWhiteSpace(s);
        if (!updatedS.empty()) {
            ss1.push_back(updatedS);
        }
    }

    if (opcode == "ADD" || opcode == "SUB" || opcode == "AND" || opcode == "OR" || opcode == "XOR") {
        i.arithmeticAndLogicalOperation(opcode, ss1);
    } else if (opcode == "MOV") {
        i.MOV(ss1);
    } else if (opcode == "CMP") {
        i.CMP(ss1);
    } else if (opcode == "LOAD" || opcode == "STORE") {
        i.dataTransfer(opcode, ss1);
    } else if (opcode == "BEQ" || opcode == "BNE" || opcode == "BAL") {
        i.branch(opcode, ss1);
    } else {
        cout << "Invalid Opcode.\n" << endl;
    }

                }
                
         }

    }




    openFile.close();


    return 0;
}