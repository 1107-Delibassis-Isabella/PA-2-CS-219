#include "opcode.h"
void opcode::arithmeticAndLogicalOperation(string operationCode, vector<string>& operands) {
    //printCode();
    if (operands.size() != 3) {
        cout << "Invalid Instruction. Invalid Operand Count." << endl;
        return;
    } else {
        int registerDestination, op1; 
        uint32_t op2;
        if (!checkRegister(operands[0], registerDestination)) {
            cout << "Invalid Instruction" << endl;
            return;
        }
        if (!checkRegister(operands[1], op1)) {
            cout << "Invalid Instruction" << endl;
            return;
        } 
        
        if (!checkOperand(operands[2], op2)) {
            //there is something wrong with this if statement
            cout << "Invalid Instruction" << endl;
            return;
        } 


            uint16_t r1 = registerArray[op1];
            uint16_t r2 = registerArray[op2];
            uint16_t result = 0;
            if (operationCode == "ADD") {
                result = r1+r2;
                //return result;
            } else if (operationCode == "SUB") {
                result = r1 - r2;
                //return result;
            } else if (operationCode == "AND") {
                result = r1 & r2;
                //return result;
            } else if (operationCode == "OR") {
                result = r1 | r2;
            } else if (operationCode == "XOR") {
                result = r1 ^ r2;
            }
        
        printCode();
    }
}

void opcode::CMP(vector<string> operands) {
    if (operands.size() != 2) {
        return;
    }
    int op1, op2;
    if ((checkRegister(operands[0], op1) == false) || (checkRegister(operands[1], op2) == false) ) {
        cout << "Invalid Instruction" << endl;
        return;
    }
    uint16_t r1 = registerArray[op1];
    uint16_t r2 = registerArray[op2];
    uint16_t result = r1 - r2;
    if (result == 0) {
        z = 1;
    } else {
        z = 0;
    }
    printCode();
}
void opcode::MOV(const vector<string>& operands) {
    if (operands.size() != 2) {
        //cout << "TESTING" << endl;
        return;
    }
    int registerDestination;
    uint32_t op1;
    if (checkRegister(operands[0], registerDestination) == false) {
        cout << "Invalid Instruction" << endl;
        return;
    }
    
    if (checkOperand(operands[1], op1) == false)  {
        cout << "Invalid Instruction for MOV" << endl;
        return;
    }
    uint16_t r1 = registerArray[op1];
    registerArray[registerDestination] = r1;
    printCode();
    
}


void opcode::branch(string operationCode, vector<string> name) {
    if(name.size() != 1) {
        cout << "Invalid Instruction. Invalid Operand Count." << endl;
        return;
    } else {
        if (operationCode == "BEQ") {
            if (z == 1) {
                cout << "The branch to " << name[0] << " is taken." << endl;
            } else if (z == 0) {
                cout << "The branch to " << name[0] << " is not taken." << endl;
            }
        } else if (operationCode == "BNE") {
            if (z == 0) {
                cout << "The branch to " << name[0] << " is taken." << endl;
            } else if (z == 1) {
                cout << "The branch to " << name[0] << " is not taken." << endl;
            }
        } else if (operationCode == "BAL") {
            cout << "Always branch to " << name[0] << endl;
        }
    }
    
}

void opcode::dataTransfer(string operation, vector<string>& operands) {
    if (operands.size() != 2) {
        cout << "invalid Instruction." << endl;
        return;
    } else {
        int registerDestination;
        uint32_t memoryAddress;
        if ((checkRegister(operands[0], registerDestination) == false) || (checkOperand(operands[1], memoryAddress) == false) ) {
            cout << "Invalid Instruction." << endl;
            return;
        }
        int index = getMemoryIndex(memoryAddress);
        if (operation == "LOAD") {
            registerArray[registerDestination] = memoryArray[index];
            printCode();
        } if (operation == "STORE") {
            memoryArray[index] = registerArray[registerDestination];
            printCode();
        }
    }
}
int opcode::getMemoryIndex(uint32_t address) {
    if (address < beginningAddress || address > endingAddress) {
        return -1;
    } 
    return static_cast<int>((address-beginningAddress)/4);
}


void opcode::printCode() {
    cout << "Register array: " << endl;
    for (int i = 0; i < numRegisters; i++) {
        cout << "R" << i << " =0x" << std::hex << registerArray[i] << " ";
    }
    cout << endl;
    cout << "Memory array: " << endl;
    for (int i = 0; i < memorySize; i++) {
        if (memoryArray[i]) {
            cout << "0x" << std::hex << memoryArray[i];
        } else {
            cout << "___";
        }
        if (i < memorySize - 1) {
            cout << ", ";
        }
    }
    cout << endl;

}

bool opcode::checkRegister(const string& s, int& numRegister) const{ //this might be incorrect
    if (s.empty() || (s[0] != 'R' && s[0] != 'r')){
        return false;
    }
    else {
        size_t index;
        int val = stoi(s.substr(1), &index);
        if (index != s.length() - 1 || val < 0 || val >= static_cast<int>(numRegisters)) {
            return false;
        }
        numRegister = val;
        return true;
    }
}


bool opcode::checkOperand(const string& s, uint32_t& value) {
    if (s.empty() == true) {
        return false;
    }  
    int reg;
    if (checkRegister(s, reg)) { //this might be incorrect
        value = registerArray[reg];
        return true;
    }

    string clean = s;
    if (clean[0] == '#') {
        clean = clean.substr(1);
    }

    size_t index;
    unsigned long val = stoul(clean, &index, 0);
    if (index == clean.length()) {
        value = static_cast<uint16_t>(val);
        return true;
    }

    return false;
}

/*string opcode::removeWhiteSpace(const string& str) const {
    size_t start = 0;
    while (start < str.length() && (str[start] == ' ' || str[start] == '\t' || str[start] == '\r' || str[start] == '\n')) {
        start++;
    }

    size_t end = str.length();
    while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t' || str[end - 1] == '\r' || str[end - 1] == '\n')) {
        end--;
    }

    return str.substr(start, end - start);
}*/