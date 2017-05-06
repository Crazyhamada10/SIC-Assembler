/*
 * Phase2.cpp
 *
 *  Created on: May 1, 2017
 *      Author: crazyhamada10
 */

#include "Phase2.h"
#include "../Errors.h"
#include "../Instruction/Controller.h"
#include "../Instruction/Instruction.h"
#include <cstdlib>

Phase2* Phase2::instance = NULL;

Phase2::Phase2() {

}

Phase2::~Phase2() {

}

Phase2* Phase2::Instance() {
	if (instance == NULL) {
		instance = new Phase2();
	}
	return instance;
}

void Phase2::Release() {
    if (instance) {
        delete instance;
    }
    instance = NULL;
}

bool readLine(ifstream& input, Instruction*& ret) {
	string line;
	if (getline(input, line, '\n')) {
        ret = Controller::Instance()->reGetInstruction(line);
        return true;
	}
	return false;
}


bool isStart(Instruction* instruction, ofstream& output) {
	if (instruction != NULL && instruction->getOperation()->isStart()) {
		output << instruction->getObjectOutputLine();
		return true;
	}
	return false;
}


bool Phase2::run(ifstream& input, ofstream& output, vector<pair<string, string> >& addressObj) {
	bool reading = true;
	Instruction* instruction = NULL;
	if (readLine(input, instruction)) {
		if (isStart(instruction, output)){
			reading = readLine(input, instruction);
		}
		while (reading) {
			if (instruction == NULL) {
				reading = readLine(input, instruction);
				continue;
			}
			if (instruction->getOperation()->isEnd()) break;

			if (instruction->getOperation()->opTable()) {
				if (!instruction->getOperand()->checkOperPass2())
					output << Errors::undefinedSymbol(instruction->getOperand()->getValue());
			}
			output << instruction->getObjectOutputLine();
			addressObj.push_back(make_pair(instruction->getLabel()->getAddress(), instruction->generateOpcode()));
			reading = readLine(input, instruction);
		}
	}
	return !Errors::getFlag();
}

/*// PATH2
 * begin
 * 	read first input line (from intermediate file)
 * 	if (opcode == "START") {
 * 		write listing line
 * 		read next input line
 * 	}
 *	write header record to object program  			-----------
 *	initialize first text record
 * 	while (opcode != "END") {
 * 		if ("not a comment") {
 * 			if (opcode in OPTAB) {
 * 				if (there is a symbol in operand field) {
 * 					if (found in SYMTAB) {
 * 						store symbol value as operand address
 * 					} else {
 * 						store 0 as operand address
 * 						// ERROR undefined symbol
 * 					}
 * 				} else {
 * 					store 0 as operand address
 * 				}
 * 				assemble the object code instruction
 * 			} else if (opcode == "WORD" || opcode == "BYTE") {
 *				convert constant into object code
 *
 *				add object code to text record
 * 			}
 * 		}
 * 		write listing line
 * 		read next line
 * 	}
 * 	write last text record to object program
 * 	write end record to object program
 * 	write last listing line
 */
