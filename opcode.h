#ifndef OPCODE_H
#define OPCODE_H
#include <iostream>
#include <cstdint>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class opcode {
    private:
        static constexpr int numRegisters = 8;
        static constexpr int memorySize = 5;
        static constexpr uint32_t beginningAddress = 0x100;
        static constexpr uint32_t endingAddress = 0x110;
        uint16_t register1, register2;
        uint16_t registerArray[numRegisters] = {0, 0, 0, 0, 0, 0, 0, 0};
        uint16_t memoryArray[memorySize];
        int z;
        
    public:
    void arithmeticAndLogicalOperation(string operationCode, vector<string>& operands);
    void twoOperandOperation(string operationCode, vector<string>& operands);
    void CMP(vector<string> operands);
    void MOV(const vector<string>& operands);

    void branch(string operationCode, vector<string> name);

    void dataTransfer(string operation, vector<string>& operands);
    int getMemoryIndex(uint32_t address);


    void printCode();
    
    bool checkRegister(const string& token, int& reg_num) const;
    bool checkOperand(const string& s, uint32_t& value);

    string removeWhiteSpace(const string& str) const;

};

#endif