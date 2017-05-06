/*
 * Phase1.cpp
 *
 *  Created on: May 1, 2017
 *      Author: crazyhamada10
 */

#include "Phase1.h"
#include "../Instruction/Controller.h"
#include "../Instruction/Instruction.h"
#include "../Errors.h"
#include <cstdlib>

Phase1* Phase1::instance = NULL;

Phase1::Phase1() {

}

Phase1::~Phase1() {

}

Phase1* Phase1::Instance() {
	if (instance == NULL) {
		instance = new Phase1();
	}
	return instance;
}

void Phase1::Release() {
    if (instance) {
        delete instance;
    }
    instance = NULL;
}

bool readLine(ifstream& input, ofstream& output, Instruction*& ret) {
	string line;
	if (getline(input, line, '\n')) {
        try {
            ret = Controller::Instance()->getInstruction(line);
        } catch (string& msg) {
            output  << msg << line << '\n';
            ret = NULL;
        }
        return true;
	}
	return false;
}

bool isStart(Instruction* instruction, ofstream& output, int& locCounter) {
	if (instruction != NULL && instruction->getOperation()->isStart()) {
        if (instruction->getOperand()->checkStart()) {
            locCounter = instruction->getOperand()->getStartAddress();
        } else {
            locCounter = 0;
            output << Errors::unknownOperand();
        }
		instruction->setAddress(locCounter);
		output << instruction->getOutputLine();
		return true;
	}
	return false;
}

int checkOpcode(Instruction* instruction, ofstream& output) {
	int toIncrease = 3; string error = "";
	if (instruction->getOperation()->opTable()) {
        if ((instruction->getOperation()->noOperand() && !instruction->hasOperand())
            || (!instruction->getOperation()->noOperand() && instruction->getOperand()->checkOper())) {
        } else error = Errors::unknownOperand();
	} else if (instruction->getOperation()->isWord()) {
        if (instruction->getOperand()->checkNumber()) {
        } else error = Errors::unknownOperand();
	} else if (instruction->getOperation()->reservedWord()) {
		if (instruction->getOperand()->checkNumber()) {
			toIncrease *= instruction->getOperand()->getNumber();
		} else error = Errors::unknownOperand();
	} else if (instruction->getOperation()->reservedByte()) {
		if (instruction->getOperand()->checkNumber()) {
			toIncrease = instruction->getOperand()->getNumber();
		} else error = Errors::unknownOperand();
	} else if (instruction->getOperation()->isByte()) {
		if (instruction->getOperand()->checkByte()) {
			toIncrease = instruction->getOperand()->getLengthByte();
		} else error = Errors::unknownOperand();
	} else {
		error = Errors::unknownOpcode(instruction->getOperation()->getString());
	}
	if (error != "") {
        toIncrease = 0;
        output << error;
	}
	return toIncrease;
}

bool Phase1::run(ifstream& input, ofstream& output, string& progName, int& progLen, int& startAddress) {
	bool reading = true;
	int locCounter = 0;
	Instruction* instruction = NULL;
	if (readLine(input, output, instruction)) {
        while (instruction == NULL && reading )
        	reading = readLine(input, output, instruction);
		if (isStart(instruction, output, locCounter)){
			progName = instruction->getLabel()->getSymbol();
			reading = readLine(input, output, instruction);
		}
		startAddress = locCounter;
        while (reading) {
			if (instruction == NULL) {
                reading = readLine(input, output, instruction);
                continue;
			}
            if (instruction->getOperation()->isEnd()) break;
            instruction->setAddress(locCounter);
            if (instruction->hasLabel()) {
                if (!instruction->saveLabel()) {
                    output << Errors::LabelDefinition(instruction->getLabel()->getSymbol());
                }
            }
            locCounter += checkOpcode(instruction, output);
            output << instruction->getOutputLine();
            reading = readLine(input, output, instruction);
		}
		progLen = locCounter - startAddress;
	}
	return !Errors::getFlag();
}

/*// PATH1
 * begin
 * 	read first input line
 * 	if (opcode == "START") {
 * 		save #[OPERAND] as starting address
 * 		initialize LOCCTR to starting address
 * 		write line to intermediate file
 * 		read next input line
 * 	} else {
 * 		initialize  LOCCTR to 0
 * 	}
 * 	while (opcode != "END") {
 * 		if ("not a comment") {
 * 			if (!Label.empty()) {
 * 				if (found in SYMTAB) {
 * 					//ERROR repeated Label definition
 * 				} else {
 * 					insert (Label, LOCCTR) into SYMTAB;
 * 				}
 * 			}
 * 			if (opcode in OPTAB) {
 * 				add 3 to LOCCTR
 * 			} else if (opcode == "WORD") {
 *				add 3 to LOCCTR
 * 			} else if (opcode == "RESW") {
 * 				add 3 * #[OPERAND] to LOCCTR
 * 			} else if (opcode == "RESB") {
 * 				add #[OPERAND] to LOCCTR
 * 			} else if (opcode == "BYTE") {
 *				find length of constants in BYTES
 *				add Length to LOCCTR
 * 			} else {
 * 				//ERROR unknown opcode
 * 			}
 * 		}
 * 		write line to intermediate file
 * 		read next line
 * 	}
 * 	write last line to intermediate file
 *	save (LOCCTR - StartingAddress) as Program Length
 */
